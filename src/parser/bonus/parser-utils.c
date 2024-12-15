/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:16:17 by abelov            #+#    #+#             */
/*   Updated: 2024/11/19 00:16:17 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include "parser.tab.h"

GenericPointer * globalAllocMem = NULL;
size_t globalAllocCount = 0;
size_t globalAllocSize  = 0;
bool needsFree = false;
command_t * command_root = NULL;

simple_command_t * bind_parts(word_t * exe_name, word_t * params, redirect_t red)
{
	simple_command_t * s = (simple_command_t *) malloc(sizeof(simple_command_t));
	pointerToMallocMemory(s);

	memset(s, 0, sizeof(*s));
	assert(exe_name != NULL);
	assert(exe_name->next_word == NULL);
	s->verb = exe_name;
	s->params = params;
	s->in = red.red_i;
	s->out = red.red_o;
	s->err = red.red_e;
	s->io_flags = red.red_flags;
	s->up = NULL;
	s->aux = NULL;
	return s;
}

command_t * new_command(simple_command_t * scmd)
{
	command_t * c = (command_t *) malloc(sizeof(command_t));

	if (c == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	pointerToMallocMemory(c);

	memset(c, 0, sizeof(*c));
	c->up = c->cmd1 = c->cmd2 = NULL;
	c->op = OP_NONE;
	assert(scmd != NULL);
	c->scmd = scmd;
	scmd->up = c;
	c->aux = NULL;
	return c;
}

command_t * bind_commands(command_t * cmd1, command_t * cmd2, operator_t op)
{
	command_t * c = (command_t *) malloc(sizeof(command_t));
	pointerToMallocMemory(c);

	memset(c, 0, sizeof(*c));
	c->up = NULL;
	assert(cmd1 != NULL);
	assert(cmd1->up == NULL);
	c->cmd1 = cmd1;
	cmd1->up = c;
	assert(cmd2 != NULL);
	assert(cmd2->up == NULL);
	assert(cmd1 != cmd2);
	c->cmd2 = cmd2;
	cmd2->up = c;
	assert((op > OP_NONE) && (op < OP_DUMMY));
	c->op = op;
	c->scmd = NULL;
	c->aux = NULL;

	return c;
}

word_t * new_word(const char * str, bool expand)
{
	word_t * w = (word_t *) malloc(sizeof(word_t));
	pointerToMallocMemory(w);

	memset(w, 0, sizeof(*w));
	assert(str != NULL);
	w->string = str;
	w->expand = expand;
	w->next_part = NULL;
	w->next_word = NULL;

	return w;
}


word_t * add_part_to_word(word_t * w, word_t * lst)
{
	word_t * crt = lst;
	assert(lst != NULL);
	assert(w != NULL);

	/*
	 we could insert at the beginnig and then invert the list
	 but this would make the code a bit more complicated
	 thus, we assume we have small lists and O(n*n) is acceptable
	*/

	while (crt->next_part != NULL) {
		crt = crt->next_part;
		assert((crt == NULL) || (crt->next_word == NULL));
	}

	crt->next_part = w;
	assert(w->next_part == NULL);
	assert(w->next_word == NULL);

	return lst;
}


word_t * add_word_to_list(word_t * w, word_t * lst)
{
	word_t * crt = lst;
	assert(w != NULL);

	if (crt == NULL) {
		assert(w->next_word == NULL);
		return w;
	}
	assert(lst != NULL);

	/*
	 same as above
	*/
	while (crt->next_word != NULL) {
		crt = crt->next_word;
	}

	crt->next_word = w;
	assert(w->next_word == NULL);

	return lst;
}

void ensureSize(size_t newSize)
{
	GenericPointer * newPtr;
	assert(newSize > 0);

	if (globalAllocSize == 0) {
		assert(globalAllocMem == NULL);
		globalAllocSize = newSize;
		globalAllocMem = (GenericPointer *)malloc(sizeof(GenericPointer) * globalAllocSize);
		if (globalAllocMem == NULL) {
			fprintf(stderr, "malloc() failed\n");
			exit(EXIT_FAILURE);
		}

		return;
	}

	assert(globalAllocMem != NULL);
	if (globalAllocSize >= newSize) {
		return;
	}

	globalAllocSize += newSize;
	newPtr = (GenericPointer *)realloc((void *)globalAllocMem, sizeof(GenericPointer) * globalAllocSize);
	if (newPtr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}

	globalAllocMem = newPtr;
}

void pointerToMallocMemory(const void * ptr)
{
	if (ptr == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}

	ensureSize(globalAllocCount + 1);
	globalAllocMem[globalAllocCount++] = (GenericPointer)ptr;
}

bool parse_line(const char * line, command_t ** root)
{
	if (*root != NULL) {
		/* see the comment in parser.h */
		assert(false);
		return false;
	}

	if (line == NULL) {
		/* see the comment in parser.h */
		assert(false);
		return false;
	}

	free_parse_memory();
	globalParseAnotherString(line);
	needsFree = true;
	command_root = NULL;

	yylloc.first_line = yylloc.last_line = 1;
	yylloc.first_column = yylloc.last_column = 0;

	if (yyparse() != 0) {
		/* yyparse failed */
		return false;
	}

	*root = command_root;

	return true;
}


void free_parse_memory()
{
	if (needsFree) {
		globalEndParsing();
		while (globalAllocCount != 0) {
			globalAllocCount--;
			assert(globalAllocMem[globalAllocCount] != NULL);
			free(globalAllocMem[globalAllocCount]);
			globalAllocMem[globalAllocCount] = NULL;
		}

		if (globalAllocMem != NULL) {
			free((void *)globalAllocMem);
			globalAllocMem = NULL;
		}

		globalAllocSize = 0;
		needsFree = false;
	}
}

void yyerror(const char* str)
{
	parse_error(str, yylloc.first_column);
}
