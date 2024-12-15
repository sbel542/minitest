# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 18:49:40 by abelov            #+#    #+#              #
#    Updated: 2024/11/15 18:49:40 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGRAM			:= scanner

CC				:= cc
INC_DIR			=  ./include
INCLUDE_FLAGS	:= -I. -I$(INC_DIR) -isystem /usr/include/readline
OPTIMIZE_FLAGS	:= -O0
DEBUG_FLAGS		:= -g3 -gdwarf-3
MANDATORY_FLAGS	:= -Wall -Wextra -Werror -Wimplicit
CFLAGS			= $(MANDATORY_FLAGS) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(INCLUDE_FLAGS)
LINK_FLAGS		:= -L/home/sbelcher/homebrew/opt/flex/lib -lfl -lreadline

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: lex.yy.c scanner

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -O

lex.yy.c: scanner.l
	flex -d --header-file=lex.yy.h $^

scanner: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LINK_FLAGS)

re: clean all

clean:
	rm -fv $(PROGRAM) $(OBJS) lex.yy.c

.PHONY: clean re
