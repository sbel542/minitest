/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:42:35 by sbelcher          #+#    #+#             */
/*   Updated: 2024/12/15 14:42:40 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_node(t_node_type type, const char *value, t_ast_node *parent, t_token_type token)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ast_node));
	node->type = type;
	if (value)
		node->value = strdup(value);
	else
		node->value = NULL;
	node->parent = parent;
	node->arguments = NULL;
	node->redirects_in = NULL;
	node->redirects_out = NULL;
	node->left = NULL;
	node->right = NULL;
	if (token == TOKEN_VAR)
		node->expand = true;
	else
		node->expand = false;
	return (node);
}

t_ast_node	*create_redirection_node(t_token_type type, char *value, t_ast_node *parent, t_token_type token)
{
	if (type == TOKEN_REDIRECT_OUT)
		return (create_node(NODE_REDIRECT_OUT, value, parent, token));
	else if (type == TOKEN_REDIRECT_IN)
		return (create_node(NODE_REDIRECT_IN, value, parent, token));
	else if (type == TOKEN_APPEND)
		return (create_node(NODE_APPEND, value, parent, token));
	else if (type == TOKEN_HERE_DOC)
		return (create_node(NODE_HERE_DOC, value, parent, token));
	else
		return (NULL);
}

t_ast_node	*parse_redirection(t_token **tokens, int *token_pos, t_ast_node *parent)
{
	t_ast_node	*redir_node;
	t_ast_node	*filename_node;

	redir_node = create_redirection_node(tokens[*token_pos]->type, tokens[*token_pos]->value, parent, tokens[*token_pos]->type);
	if (!redir_node)
		return (NULL);
	skip_blanks(tokens, token_pos, NULL);
	if (tokens[*token_pos] && (tokens[*token_pos]->type == TOKEN_WORD || tokens[*token_pos]->type == TOKEN_VAR))
	{
		filename_node = create_node(NODE_FILENAME, tokens[*token_pos]->value, redir_node, tokens[*token_pos]->type);
		if (!filename_node)
		{
			free_ast(redir_node);
			return (NULL);
		}
		redir_node->right = filename_node;
		skip_blanks(tokens, token_pos, filename_node);
	}
	else
	{
		ft_printf("Syntax error: Expected target after redirection\n");
		free_ast(redir_node);
		return (NULL);
	}
	if (redir_node->type == NODE_REDIRECT_IN || redir_node->type == NODE_HERE_DOC)
	{
		if (!parent->redirects_in)
			parent->redirects_in = redir_node;
		else
		{
			t_ast_node *current = parent->redirects_in;
			while (current->redirects_in)
				current = current->redirects_in;
			current->redirects_in = redir_node;
		}
	}
	else
	{
		if (!parent->redirects_out)
			parent->redirects_out = redir_node;
		else
		{
			t_ast_node *current = parent->redirects_out;
			while (current->redirects_out)
				current = current->redirects_out;
			current->redirects_out = redir_node;
		}
	}
	return (redir_node);
}

t_ast_node	*parse_command(t_token **tokens, int *token_pos)
{
	t_ast_node	*command_node;
	t_ast_node	*last_arg = NULL;
	t_ast_node	*redir_node = NULL;
	t_ast_node	*arg_node;

	if (!tokens[*token_pos] || (tokens[*token_pos]->type != TOKEN_WORD && tokens[*token_pos]->type != TOKEN_VAR))
		return (NULL);
	command_node = create_node(NODE_COMMAND, tokens[*token_pos]->value, NULL, tokens[*token_pos]->type);
	if (!command_node)
		return (NULL);
	skip_blanks(tokens, token_pos, command_node);
	while ((*token_pos) && tokens[*token_pos] != NULL) 
	{
		if (tokens[*token_pos]->type == TOKEN_WORD || tokens[*token_pos]->type == TOKEN_VAR)
		{
			arg_node = create_node(NODE_ARGUMENT, tokens[*token_pos]->value, command_node, tokens[*token_pos]->type);
			if (!arg_node)
			{
				free_ast(command_node);
				return (NULL);
			}
			if (command_node->arguments == NULL)
				command_node->arguments = arg_node;
			else
				last_arg->arguments = arg_node;
			last_arg = arg_node;
			skip_blanks(tokens, token_pos, arg_node);
		}
		else if (tokens[*token_pos]->type == TOKEN_REDIRECT_IN ||
				 tokens[*token_pos]->type == TOKEN_REDIRECT_OUT ||
				 tokens[*token_pos]->type == TOKEN_APPEND ||
				 tokens[*token_pos]->type == TOKEN_HERE_DOC)
		{
			redir_node = parse_redirection(tokens, token_pos, command_node);
			if (!redir_node)
			{
				free_ast(command_node);
				return (NULL);
			}
		}
		else
			break;
	}
	return (command_node);
}

void	skip_blanks(t_token **tokens, int *token_pos, t_ast_node *last)
{
	(*token_pos)++;
    if (tokens[*token_pos])
    {
		if (last != NULL)
		{
			while (tokens[*token_pos]->type == TOKEN_WORD || tokens[*token_pos]->type == TOKEN_VAR)
			{
				last->word_continue = create_node(NODE_CONTINUE, tokens[*token_pos]->value, NULL, tokens[*token_pos]->type);
				last = last->word_continue;
				(*token_pos)++;
				if (!tokens[*token_pos])
					break;
			}
		}
    }
	if (tokens[*token_pos])
	{
		if (tokens[*token_pos]->type == TOKEN_BLANK)
        		(*token_pos)++;
	}
}


t_ast_node	*parse_pipeline(t_token **tokens, int *token_pos)
{
	t_ast_node	*command_node;
	t_ast_node	*next_command;
	t_ast_node	*pipe_node;

	if (tokens[*token_pos]->type == TOKEN_BLANK)
		(*token_pos)++;
	command_node = parse_command(tokens, token_pos);
	if (!command_node)
		return (NULL);
	while (tokens[*token_pos] && tokens[*token_pos]->type == TOKEN_PIPE)
	{
		skip_blanks(tokens, token_pos, NULL);
		next_command = parse_command(tokens, token_pos);
		if (!next_command)
		{
			ft_printf("Syntax error: Expected command after '|'\n");
			free_ast(command_node);
			return (NULL);
		}
		pipe_node = create_node(NODE_PIPE, "|", NULL, TOKEN_PIPE);
		if (!pipe_node)
		{
			ft_printf("Error: Memory allocation failed.\n");
			free_ast(command_node);
			free_ast(next_command);
			return (NULL);
		}
		pipe_node->left = command_node;
		pipe_node->right = next_command;
		command_node->parent = pipe_node;
		next_command->parent = pipe_node;
		command_node = pipe_node;
	}
	return (command_node);
}

#define BUFF_SIZE 1024

void print_arguments(t_ast_node *arg_node, int depth)
{
	char buf[BUFF_SIZE];
	t_ast_node *node;

	while (arg_node)
	{
		*buf = '\0';
		for (int i = 0; i < depth; i++)
			ft_printf("  ");
		if (!arg_node->value)
			snprintf(buf, BUFF_SIZE, "NULL");
		else if (arg_node->value && arg_node->expand)
			snprintf(buf, BUFF_SIZE, "expand(%s)", arg_node->value);
		else
			snprintf(buf, BUFF_SIZE, "%s", arg_node->value);
		ft_printf("ARGUMENT: %s", buf);

		t_ast_node	*cont_node = arg_node; 
		while (cont_node->word_continue)
		{
			*buf = '\0';
			node = cont_node->word_continue;
			if (!node->value)
				snprintf(buf, BUFF_SIZE, "NULL");
			else if (node->value && node->expand)
				snprintf(buf, BUFF_SIZE, "expand(%s)", node->value);
			else
				snprintf(buf, 1024, "%s", node->value);
			ft_printf("; %s", buf);
			cont_node = cont_node->word_continue;
		}
		printf("\n");
		arg_node = arg_node->arguments;
	}
}

void	print_redirections(t_ast_node *redir_node, int depth)
{
	while (redir_node)
	{
		int	i;

		i = -1;
		while (++i < depth)
			ft_printf("  ");
		printf("Redirection Type: %s, Target: %s",
			   redir_node->type == NODE_REDIRECT_IN ? "INPUT" :
			   redir_node->type == NODE_REDIRECT_OUT ? "OUTPUT" :
			   redir_node->type == NODE_APPEND ? "APPEND" :
			   redir_node->type == NODE_HERE_DOC ? "HEREDOC" : "UNKNOWN",
			   redir_node->right && redir_node->right->value ? redir_node->right->value : "NULL");
		if (redir_node->right->expand == true)
			printf(" - TO EXPAND");
		t_ast_node	*file = redir_node->right;
		while (file->word_continue)
		{
			printf("; %s", file->word_continue->value ? file->word_continue->value : "NULL");
			if (file->word_continue->expand == true)
				printf(" - TO EXPAND");
			file = file->word_continue;
		}
		printf("\n");
		if (redir_node->type == NODE_REDIRECT_IN || redir_node->type == NODE_HERE_DOC)
			redir_node = redir_node->redirects_in;
		else if (redir_node->type == NODE_REDIRECT_OUT || redir_node->type == NODE_APPEND)
			redir_node = redir_node->redirects_out;
		else
			redir_node = NULL;
	}
}

void	print_ast(t_ast_node *node, int depth)
{
	int	i;
	i = -1;

	if (!node)
		return;
	while (++i < depth)
		ft_printf("  ");
	printf("%s: %s",
		   node->type == NODE_COMMAND ? "COMMAND" :
		   node->type == NODE_ARGUMENT ? "ARGUMENT" :
		   node->type == NODE_PIPE ? "PIPE" :
		   node->type == NODE_REDIRECT_OUT ? "REDIRECT_OUT" :
		   node->type == NODE_REDIRECT_IN ? "REDIRECT_IN" :
		   node->type == NODE_APPEND ? "APPEND" :
		   node->type == NODE_HERE_DOC ? "HERE_DOC" :
		   node->type == NODE_FILENAME ? "FILENAME" :
		   "UNKNOWN",
		   node->value ? node->value : "NULL");
	if (node->expand == true)
		printf(" - TO EXPAND");
	t_ast_node	*cont = node;
	while (cont->word_continue)
	{
		printf("; %s", cont->word_continue->value ? cont->word_continue->value : "NULL");
		if (cont->word_continue->expand == true)
			printf(" - TO EXPAND");
		cont = cont->word_continue;
	}
	printf("\n");   
	if (node->type == NODE_COMMAND)
	{
		if (node->arguments)
		{
			i = -1;
			while (++i < depth + 1)
				ft_printf("  ");
			ft_printf("Arguments:\n");
			print_arguments(node->arguments, depth + 2);
		}
		if (node->redirects_in)
		{
			i = -1;
			while (++i < depth + 1)
				ft_printf("  ");
			ft_printf("Input Redirections:\n");
			print_redirections(node->redirects_in, depth + 2);
		}
		if (node->redirects_out)
		{
			i = -1;
			while (++i < depth + 1)
				ft_printf("  ");
			ft_printf("Output Redirections:\n");
			print_redirections(node->redirects_out, depth + 2);
		}
	}
	else if (node->type == NODE_PIPE)
	{
		if (node->left)
		{
			i = -1;
			while (++i < depth + 1)
				ft_printf("  ");
			ft_printf("Left Command ->\n");
			print_ast(node->left, depth + 2);
		}
		if (node->right)
		{
			i = -1;
			while (++i < depth + 1)
				ft_printf("  ");
			ft_printf("Right Command ->\n");
			print_ast(node->right, depth + 2);
		}
	}
}

void	free_arguments(t_ast_node *arg_node)
{
	while (arg_node)
	{
		t_ast_node *temp = arg_node;
		free(arg_node->value);
		arg_node = arg_node->arguments;
		free(temp);
	}
}

void	free_redirections(t_ast_node *redir_node)
{
	while (redir_node)
	{
		t_ast_node	*temp;

		temp = redir_node;
		free(redir_node->value);
		if (redir_node->right)
			free_ast(redir_node->right);
		if (redir_node->type == NODE_REDIRECT_IN || redir_node->type == NODE_HERE_DOC)
			redir_node = redir_node->redirects_in;
		else if (redir_node->type == NODE_REDIRECT_OUT || redir_node->type == NODE_APPEND)
			redir_node = redir_node->redirects_out;
		else
			redir_node = NULL;
		free(temp);
	}
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return;
	free(node->value);
	if (node->arguments)
		free_arguments(node->arguments);
	if (node->redirects_in)
		free_redirections(node->redirects_in);
	if (node->redirects_out)
		free_redirections(node->redirects_out);
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	free(node);
}
