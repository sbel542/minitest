/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:42:48 by abelov            #+#    #+#             */
/*   Updated: 2024/11/17 22:42:49 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
#define SCANNER_H

enum yytokentype
{
	NOT_ACCEPTED_CHAR = 258,
	DOLLAR_SIGN = 259,
	UNEXPECTED_EOF = 260,
	CHARS_AFTER_EOL = 261,
	END_OF_FILE = 262,
	EOL = 263,
	BLANK = 264,
	REDIRECT_OE = 265,
	REDIRECT_O = 266,
	REDIRECT_E = 267,
	REDIRECT_IN = 268,
	REDIRECT_APPEND_E = 269,
	REDIRECT_APPEND_O = 270,
	WORD = 271,
	ENV_VAR = 272,
	SEQUENTIAL = 273,
	PARALLEL = 274,
	OR_LIST = 275,
	AND_LIST = 276,
	PIPE = 277,
	HEREDOC = 278
};

typedef struct
{
	int token_id;
	const char *str;
} lt_entry;

#endif //SCANNER_H
