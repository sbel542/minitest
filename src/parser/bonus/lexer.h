/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:54:59 by abelov            #+#    #+#             */
/*   Updated: 2024/11/19 01:55:00 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#define UPD_LOCATION \
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng

#ifdef __cplusplus

#include <cstdio>
#include <cstring>
#include <cassert>

using namespace std;

#else

#include <stdio.h>
#include <string.h>
#include <assert.h>

#endif

#define __PARSER_H_INTERNAL_INCLUDE
#include "parser.h"
#include "parser.tab.h"

#endif //LEXER_H
