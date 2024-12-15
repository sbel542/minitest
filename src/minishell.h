#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "libft/libft.h"

# define MAX_TOKENS 1024

typedef enum e_token_type {
	TOKEN_COMMAND,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_IN,
	TOKEN_HERE_DOC,
	TOKEN_APPEND,
	TOKEN_STRING,
	TOKEN_BLANK,
	TOKEN_END,
	TOKEN_VAR
} t_token_type;

typedef struct s_token {
	t_token_type type;
	char *value;
} t_token;

typedef enum e_state {
	INITIAL,
	READING_WORD,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
	CHECK_APPEND,
	CHECK_HERE_DOC,
	READING_WHITESPACE,
	END,
	VARIABLE
} t_state;

typedef struct s_lexer {
	char buffer[1024];
	int buf_index;
	char curent_string;
	char	*line;
	int		i;
	t_token *tokens[MAX_TOKENS];
	int token_count;
} t_lexer;

typedef enum e_node_type {
	NODE_COMMAND,
	NODE_ARGUMENT,
	NODE_PIPE,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_IN,
	NODE_HERE_DOC,
	NODE_FILENAME,
	NODE_CONTINUE,
	NODE_APPEND
} t_node_type;

typedef struct s_ast_node	t_ast_node;
struct s_ast_node
{
	char		*value;
	t_node_type	type;
	t_ast_node	*parent;
	t_ast_node	*arguments;
	t_ast_node	*redirects_in;
	t_ast_node	*redirects_out;
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*word_continue;
	bool		expand;
};
 
t_token     *create_token(t_token_type type, const char *value, t_lexer *lexer);
void        flush_buffer(t_lexer *lexer, t_token_type type);
void        free_tokens(t_lexer *lexer);
t_state     handle_initial(t_lexer *lexer);
t_state     handle_reading_word(t_lexer *lexer);
t_state     handle_in_single_quote(t_lexer *lexer);
t_state     handle_variable(t_lexer *lexer);
t_state     handle_in_double_quote(t_lexer *lexer);
t_state     handle_check_append(t_lexer *lexer);
t_state     handle_check_here_doc(t_lexer *lexer);
t_state     handle_reading_whitespace(t_lexer *lexer);
const char  *get_idstring(int token);
t_ast_node  *parse_redirection(t_token **tokens, int *token_pos, t_ast_node *parent);
t_ast_node  *parse_command(t_token **tokens, int *token_pos);
t_ast_node  *parse_pipeline(t_token **tokens, int *token_pos);
t_ast_node	*create_node(t_node_type type, const char *value, t_ast_node *parent, t_token_type token);
t_ast_node	*create_redirection_node(t_token_type type, char *value, t_ast_node *parent, t_token_type token);
void        print_ast(t_ast_node *node, int depth);
void        free_ast(t_ast_node *node);
void        parse_command_details(t_token **tokens, int *token_pos, t_ast_node *command_node);
void        print_arguments(t_ast_node *arg_node, int depth);
void        print_redirections(t_ast_node *redir_node, int depth);
void		skip_blanks(t_token **tokens, int *token_pos, t_ast_node *last);

#endif
