/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <sbelcher@student.42london.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:20:53 by sbelcher          #+#    #+#             */
/*   Updated: 2024/11/15 15:20:54 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct
{
	int token_id;
	const char *str;
} lt_entry;

lt_entry lt[12] = {
	{ .token_id = TOKEN_COMMAND,		.str = "TOKEN_COMMAND" },
	{ .token_id = TOKEN_WORD,			.str = "TOKEN_WORD" },
	{ .token_id = TOKEN_PIPE,			.str = "TOKEN_PIPE" },
	{ .token_id = TOKEN_REDIRECT_OUT,	.str = "TOKEN_REDIRECT_OUT" },
	{ .token_id = TOKEN_REDIRECT_IN,	.str = "TOKEN_REDIRECT_IN" },
	{ .token_id = TOKEN_HERE_DOC,		.str = "TOKEN_HERE_DOC" },
	{ .token_id = TOKEN_APPEND,			.str = "TOKEN_APPEND" },
	{ .token_id = TOKEN_STRING,			.str = "TOKEN_STRING" },
	{ .token_id = TOKEN_BLANK,			.str = "TOKEN_BLANK" },
	{ .token_id = TOKEN_VAR,			.str = "TOKEN_VAR" },
	{ .token_id = TOKEN_END,			.str = "TOKEN_END" }
};

t_token *create_token(t_token_type type, const char *value, t_lexer *lexer)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token) return NULL;
	token->type = type;
	token->value = strdup(value);
	lexer->token_count++;
	return (token);
}

void flush_buffer(t_lexer *lexer, t_token_type type)
{
	if (lexer->buf_index > 0)
	{
		lexer->buffer[lexer->buf_index] = '\0';
		lexer->tokens[lexer->token_count] = create_token(type, lexer->buffer, lexer);
		lexer->buf_index = 0;
	}
}

void	free_tokens(t_lexer *lexer)
{
	int	i;

	i = -1;
	while (++i < lexer->token_count)
	{
		free(lexer->tokens[i]->value);
		free(lexer->tokens[i]);
		lexer->token_count = 0;
	}
}

t_state	handle_initial(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == ' ' || lexer->line[lexer->i] == '\t')
	{
		lexer->tokens[lexer->token_count] = create_token(TOKEN_BLANK, " ", lexer);
	  return (READING_WHITESPACE);
	}
	else if (lexer->line[lexer->i] == '$')
	{
		lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
		return (VARIABLE);
	}
	else if (lexer->line[lexer->i] == '1')
	{
		lexer->i++;
		if (lexer->line[lexer->i] == '<')
			return (CHECK_HERE_DOC);
		else if (lexer->line[lexer->i] == '>')
			return (CHECK_APPEND);
		else
			lexer->i--;
		lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
		return (READING_WORD);
	}
	else if (lexer->line[lexer->i] == '2')
	{
		lexer->i++;
		if (lexer->line[lexer->i] == '<')
			return (CHECK_HERE_DOC);
		else if (lexer->line[lexer->i] == '>')
			return (CHECK_APPEND);
		else
			lexer->i--;
		lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
		return (READING_WORD);
	}
	else if (lexer->line[lexer->i] == '\'')
	  return (IN_SINGLE_QUOTE);
	else if (lexer->line[lexer->i] == '"')
	  return (IN_DOUBLE_QUOTE);
	else if (lexer->line[lexer->i] == '>')
	  return (CHECK_APPEND);
	else if (lexer->line[lexer->i] == '<')
	  return (CHECK_HERE_DOC);
	else if (lexer->line[lexer->i] == '|')
	{
	  lexer->tokens[lexer->token_count] = create_token(TOKEN_PIPE, "|", lexer);
	  return (INITIAL);
	}
	lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
	return (READING_WORD);
}

t_state	handle_reading_word(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == '$')
	{
		flush_buffer(lexer, TOKEN_WORD);
		lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
		return (VARIABLE);
	}
	else if (isspace(lexer->line[lexer->i]))
	{
		flush_buffer(lexer, TOKEN_WORD);
		lexer->tokens[lexer->token_count] = create_token(TOKEN_BLANK, " ", lexer);
		return (READING_WHITESPACE);
	}
	else if (lexer->line[lexer->i] == '\'')
	{
		flush_buffer(lexer, TOKEN_WORD);
		return (IN_SINGLE_QUOTE);
	}
	else if (lexer->line[lexer->i] == '"')
	{
		flush_buffer(lexer, TOKEN_WORD);
		return (IN_DOUBLE_QUOTE);
	}
	else if (lexer->line[lexer->i] == '>')
	{
		flush_buffer(lexer, TOKEN_WORD);
		return (CHECK_APPEND);
	}
	else if (lexer->line[lexer->i] == '<')
	{
		flush_buffer(lexer, TOKEN_WORD);
		return (CHECK_HERE_DOC);
	}
	else if (lexer->line[lexer->i] == '|')
	{
		flush_buffer(lexer, TOKEN_WORD);
		lexer->tokens[lexer->token_count] = create_token(TOKEN_PIPE, "|", lexer);
		return (INITIAL);
	}
	lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
	return (READING_WORD);
}

t_state	handle_in_single_quote(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == '\'')
	{
		flush_buffer(lexer, TOKEN_WORD);
		return (INITIAL);
	}
	lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
	return (IN_SINGLE_QUOTE);
}

t_state	handle_in_double_quote(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == '$')
	{
		lexer->curent_string = '"';
		flush_buffer(lexer, TOKEN_WORD);
		lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
		return (VARIABLE);
	}
	if (lexer->line[lexer->i] == '"')
	{
		
		flush_buffer(lexer, TOKEN_WORD);
		return (INITIAL);
	}
	lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
	return (IN_DOUBLE_QUOTE);
}

t_state	handle_check_append(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == '>')
	{
		lexer->tokens[lexer->token_count] = create_token(TOKEN_APPEND, ">>", lexer);
		return (INITIAL);
	}
	lexer->tokens[lexer->token_count] = create_token(TOKEN_REDIRECT_OUT, ">", lexer);
	return (handle_initial(lexer));
}

t_state	handle_check_here_doc(t_lexer *lexer)
{
	if (lexer->line[lexer->i] == '<')
	{
		lexer->tokens[lexer->token_count] = create_token(TOKEN_HERE_DOC, "<<", lexer);
		return (INITIAL);
	}
	lexer->tokens[lexer->token_count] = create_token(TOKEN_REDIRECT_IN, "<", lexer);
	return (handle_initial(lexer));
}

t_state	handle_reading_whitespace(t_lexer *lexer)
{
	if (!(lexer->line[lexer->i] == ' ') && !(lexer->line[lexer->i] == '\t'))
		return (handle_initial(lexer));
	else
		return READING_WHITESPACE;
}

t_state	handle_variable(t_lexer *lexer)
{
	if (lexer->buf_index == 1 && (ft_isalpha(lexer->line[lexer->i]) || lexer->line[lexer->i] == '_'))
	{
		lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
		return (VARIABLE);
	}
	else if (lexer->buf_index == 1 && !ft_isalpha(lexer->line[lexer->i]) && lexer->line[lexer->i] != '_')
	{
		flush_buffer(lexer, TOKEN_WORD);
		return (handle_initial(lexer));
	}
	else if ((lexer->buf_index > 1) && (ft_isalnum(lexer->line[lexer->i]) || lexer->line[lexer->i] == '_'))
	{
		lexer->buffer[lexer->buf_index++] = lexer->line[lexer->i];
		return (VARIABLE);
	}
	else
	{
		flush_buffer(lexer, TOKEN_VAR);
		if (lexer->curent_string == '"')
		{
			lexer->curent_string = '0';
			if (lexer->line[lexer->i] == '"')
				return (INITIAL);
			return (handle_in_double_quote(lexer));
		}
		return (handle_initial(lexer));
	}
}

const char *get_idstring(int token)
{
	int i;
	const char *str = NULL;

	i = -1;
	while (++i < 11)
	{
		if (lt[i].token_id == token)
		{
			str = lt[i].str;
			break ;
		}
	}
	return str;
}

int main(void)
{
	t_state current_state;
	t_lexer lexer = { .buf_index = 0, .token_count = 0 };
	char ps[1024];
	int	token_pos;
	lexer.line = NULL;

	sprintf(ps, "> ");
	lexer.line = readline(ps);
	while (lexer.line)
	{
		lexer.curent_string = '0';
		lexer.i = -1;
		current_state = INITIAL;
		while (lexer.line[++lexer.i] != '\0')
		{
			if (current_state == INITIAL)
				current_state = handle_initial(&lexer);
			else if (current_state == READING_WORD)
				current_state = handle_reading_word(&lexer);
			else if (current_state == IN_SINGLE_QUOTE)
				current_state = handle_in_single_quote(&lexer);
			else if (current_state == IN_DOUBLE_QUOTE)
				current_state = handle_in_double_quote(&lexer);
			else if (current_state == CHECK_APPEND)
				current_state = handle_check_append(&lexer);
			else if (current_state == CHECK_HERE_DOC)
				current_state = handle_check_here_doc(&lexer);
			else if (current_state == READING_WHITESPACE)
				current_state = handle_reading_whitespace(&lexer);
			else if (current_state == VARIABLE)
				current_state = handle_variable(&lexer);
		}
		if (current_state == VARIABLE)
			flush_buffer(&lexer, TOKEN_VAR);
		else if (lexer.buf_index != 0)
			flush_buffer(&lexer, TOKEN_WORD);
		lexer.tokens[lexer.token_count] = NULL;
		printf("\n\nTokens:\n");
		lexer.i = -1;
		while (lexer.tokens[++lexer.i] != NULL)
			printf("Token Type: \"%s\", Value: %s\n",
				   get_idstring(lexer.tokens[lexer.i]->type), lexer.tokens[lexer.i]->value);
		token_pos = 0;
		t_ast_node *ast = parse_pipeline(lexer.tokens, &token_pos);
		if (!ast)
		{
			ft_printf("Error: Failed to parse the command.\n");
			free_tokens(&lexer);
			free(lexer.line);
			lexer.line = readline(ps);
		}
		ft_printf("\n\nAbstract Syntax Tree:\n");
		print_ast(ast, 0);
		free_ast(ast);
		free_tokens(&lexer);
		free(lexer.line);
		lexer.line = readline(ps);
	}
	free(lexer.line);
	return (0);
}