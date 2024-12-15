/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:27:44 by abelov            #+#    #+#             */
/*   Updated: 2024/11/17 22:27:45 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline.h>
#include "scanner.h"
#include "lex.yy.c"

lt_entry lt[21] = {
		{ .token_id = NOT_ACCEPTED_CHAR, .str = "NOT_ACCEPTED_CHAR" },
		{ .token_id = DOLLAR_SIGN, .str = "DOLLAR_SIGN" },
		{ .token_id = UNEXPECTED_EOF, .str = "UNEXPECTED_EOF" },
		{ .token_id = CHARS_AFTER_EOL, .str = "CHARS_AFTER_EOL" },
		{ .token_id = END_OF_FILE, .str = "END_OF_FILE" },
		{ .token_id = EOL, .str = "EOL" },
		{ .token_id = BLANK, .str = "BLANK" },
		{ .token_id = REDIRECT_OE, .str = "REDIRECT_OE" },
		{ .token_id = REDIRECT_O, .str = "REDIRECT_O" },
		{ .token_id = REDIRECT_E, .str = "REDIRECT_E" },
		{ .token_id = REDIRECT_IN, .str = "REDIRECT_IN" },
		{ .token_id = REDIRECT_APPEND_E, .str = "REDIRECT_APPEND_E" },
		{ .token_id = REDIRECT_APPEND_O, .str = "REDIRECT_APPEND_O" },
		{ .token_id = WORD, .str = "WORD" },
		{ .token_id = ENV_VAR, .str = "ENV_VAR" },
		{ .token_id = SEQUENTIAL, .str = "SEQUENTIAL" },
		{ .token_id = PARALLEL, .str = "PARALLEL" },
		{ .token_id = OR_LIST, .str = "OR_LIST" },
		{ .token_id = AND_LIST, .str = "AND_LIST" },
		{ .token_id = PIPE, .str = "PIPE" },
		{ .token_id = HEREDOC, .str = "HEREDOC" },
};


const char *get_token_idstring(int token)
{
	int i;
	const char *str = NULL;

	i = -1;
	while (++i < 22)
	{
		if (lt[i].token_id == token)
		{
			str = lt[i].str;
			break ;
		}
	}
	return str;
}

int	main(void)
{
	yyscan_t scanner;
	YY_BUFFER_STATE buf;
	int tok;

	char	*line = NULL;
	char	ps[1024];
	sprintf(ps, "> ");

	line = readline(ps);
	while (line)
	{
		yylex_init(&scanner);
		buf = yy_scan_string(line, scanner);
		tok = yylex(scanner);
		while(tok)
		{
			if (yylval.string_val)
				printf("\"%s\": \"%s\"\n", get_token_idstring(tok), yylval.string_val);
			else
				printf("\"%s\"\n", get_token_idstring(tok));
			tok = yylex(scanner);
		}
		yy_delete_buffer(buf, scanner);
		yylex_destroy(scanner);
		sprintf(ps, "> ");
		line = readline(ps);
	}
	return (EXIT_SUCCESS);
}
