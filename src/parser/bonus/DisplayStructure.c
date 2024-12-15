// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"

#define INDENT 4

void parse_error(const char *str, int where) {
	fprintf(stderr, "Parse error near %d: %s\n", where, str);
}

static void displayWord(word_t *w) {
	assert(w != NULL);
	word_t *crt = w;

	while (crt != NULL) {
		if (crt->expand)
			printf("expand(");
		printf("'%s'", crt->string);
		if (crt->expand)
			printf(")");

		crt = crt->next_part;
		if (crt != NULL) {
			printf(";    ");
			assert(crt->next_word == NULL);
		}
	}

	printf("\n");
}

static void displayList(word_t *w, int level) {
	assert(w != NULL);
	word_t *crt = w;

	while (crt != NULL) {
		printf("%*s", 2 * INDENT * level, "");
		displayWord(crt);
		crt = crt->next_word;
	}
}

static void displaySimple(simple_command_t *s, int level, command_t *father) {
	assert(s != NULL);
	assert(father == s->up);

	printf("%*s", 2 * INDENT * level, "");
	printf("simple_command_t (\n");

	printf("%*s", 2 * INDENT * level + INDENT, "");
	printf("verb (\n");
	displayList(s->verb, level + 1);
	assert(s->verb->next_word == NULL);
	printf("%*s", 2 * INDENT * level + INDENT, "");
	printf(")\n");

	if (s->params != NULL) {
		printf("%*s", 2 * INDENT * level + INDENT, "");
		printf("params (\n");
		displayList(s->params, level + 1);
		printf("%*s", 2 * INDENT * level + INDENT, "");
		printf(")\n");
	}

	if (s->in != NULL) {
		printf("%*s", 2 * INDENT * level + INDENT, "");
		printf("in (\n");
		displayList(s->in, level + 1);
		printf("%*s", 2 * INDENT * level + INDENT, "");
		printf(")\n");
	}

	if (s->out != NULL) {
		printf("%*s", 2 * INDENT * level + INDENT, "");
		printf("out (\n");
		displayList(s->out, level + 1);
		if (s->io_flags & IO_OUT_APPEND)
			printf("%*sAPPEND\n", 2 * INDENT * (level + 1), "");
		printf("%*s", 2 * INDENT * level + INDENT, "");
		printf(")\n");
	}

	if (s->err != NULL) {
		printf("%*s", 2 * INDENT * level + INDENT, "");
		printf("err (\n");
		displayList(s->err, level + 1);
		if (s->io_flags & IO_ERR_APPEND)
			printf("%*sAPPEND\n", 2 * INDENT * (level + 1), "");
		printf("%*s", 2 * INDENT * level + INDENT, "");
		printf(")\n");
	}

	printf("%*s", 2 * INDENT * level, "");
	printf(")\n");
}

static void displayCommand(command_t *c, int level, command_t *father) {
	assert(c != NULL);
	assert(c->up == father);

	printf("%*s", 2 * INDENT * level, "");
	printf("command_t (\n");

	if (c->op == OP_NONE) {
		assert(c->cmd1 == NULL);
		assert(c->cmd2 == NULL);
		printf("%*sscmy (\n", 2 * INDENT * level + INDENT, "");
		displaySimple(c->scmd, level + 1, c);
		printf("%*s)\n", 2 * INDENT * level + INDENT, "");
	} else {
		assert(c->scmd == NULL);
		printf("%*sop == ", 2 * INDENT * level + INDENT, "");

		switch (c->op) {
			case OP_SEQUENTIAL:
				printf("OP_SEQUENTIAL");
				break;
			case OP_PARALLEL:
				printf("OP_PARALLEL");
				break;
			case OP_CONDITIONAL_ZERO:
				printf("OP_CONDITIONAL_ZERO");
				break;
			case OP_CONDITIONAL_NZERO:
				printf("OP_CONDITIONAL_NZERO");
				break;
			case OP_PIPE:
				printf("OP_PIPE");
				break;
			default:
				assert(0);
		}

		printf("\n");
		printf("%*scmd1 (\n", 2 * INDENT * level + INDENT, "");
		displayCommand(c->cmd1, level + 1, c);
		printf("%*s)\n", 2 * INDENT * level + INDENT, "");
		printf("%*scmd2 (\n", 2 * INDENT * level + INDENT, "");
		displayCommand(c->cmd2, level + 1, c);
		printf("%*s)\n", 2 * INDENT * level + INDENT, "");
	}

	printf("%*s)\n", 2 * INDENT * level, "");
}

int main(void) {
	char *line = NULL;
	size_t len = 0;

	for (;;) {
		printf("> ");
		fflush(stdout);

		if (getline(&line, &len, stdin) == -1) {
			// End of file
			fprintf(stderr, "End of file!\n");
			free(line);
			return EXIT_SUCCESS;
		}

		// Trim newline character from input
		line[strcspn(line, "\n")] = '\0';

		command_t *root = NULL;
		printf("%s\n", line);

		if (parse_line(line, &root)) {
			printf("Command successfully read!\n");
			if (root == NULL) {
				printf("Command is empty!\n");
			} else {
				// Root points to a valid command tree that we can use
				displayCommand(root, 0, NULL);
			}
		} else {
			// There was an error parsing the command
			printf("Error parsing!\n");
		}

		printf("\n\n");
		free_parse_memory();
	}

	free(line);
	return EXIT_SUCCESS;
}