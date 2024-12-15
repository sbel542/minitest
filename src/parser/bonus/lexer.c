/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:24:36 by abelov            #+#    #+#             */
/*   Updated: 2024/11/19 02:24:36 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.yy.h"
#include "parser.tab.h"

YY_BUFFER_STATE myState;
bool haveOneBufferState = false;

void globalEndParsing()
{
	if (haveOneBufferState) {
		yylex_destroy();
		haveOneBufferState = false;
	}
}
