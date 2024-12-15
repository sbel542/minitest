/* https://www.lrde.epita.fr/~tiger/doc/gnuprog2/Advanced-Use-of-Bison.html */
%locations
%code requires {

#include "parser.h"

}

%union {
	command_t * command_un;
	const char * string_un;
	redirect_t redirect_un;
	simple_command_t * simple_command_un;
	word_t * exe_un;
	word_t * params_un;
	word_t * word_un;
}

%token NOT_ACCEPTED_CHAR INVALID_ENVIRONMENT_VAR UNEXPECTED_EOF CHARS_AFTER_EOL
%token END_OF_FILE END_OF_LINE BLANK
%token REDIRECT_OE REDIRECT_O REDIRECT_E INDIRECT
%token REDIRECT_APPEND_E REDIRECT_APPEND_O
%token <string_un> WORD
%token <string_un> ENV_VAR

%left SEQUENTIAL
%left PARALLEL
%left CONDITIONAL_NZERO CONDITIONAL_ZERO
%left PIPE

%type <command_un> command
%type <exe_un> exe_name
%type <params_un> params
%type <redirect_un> redirect
%type <simple_command_un> simple_command
%type <word_un> word

%start command_tree

%%
command_tree:
	command END_OF_LINE { command_root = $1; YYACCEPT; }
	| command END_OF_FILE { command_root = $1; YYACCEPT; }
	| END_OF_LINE { command_root = NULL; YYACCEPT; }
	| END_OF_FILE { command_root = NULL; YYACCEPT; }
	| BLANK END_OF_LINE { command_root = NULL; YYACCEPT; }
	| BLANK END_OF_FILE { command_root = NULL; YYACCEPT; }
	;

command:
	simple_command { $$ = new_command($1); }
	| command SEQUENTIAL command { $$ = bind_commands($1, $3, OP_SEQUENTIAL); }
	| command PARALLEL command { $$ = bind_commands($1, $3, OP_PARALLEL); }
	| command CONDITIONAL_ZERO command { $$ = bind_commands($1, $3, OP_CONDITIONAL_ZERO); }
	| command CONDITIONAL_NZERO command { $$ = bind_commands($1, $3, OP_CONDITIONAL_NZERO); }
	| command PIPE command { $$ = bind_commands($1, $3, OP_PIPE); }
	;

simple_command:
	exe_name BLANK params redirect { $$ = bind_parts($1, $3, $4); }
	| exe_name BLANK params BLANK redirect { $$ = bind_parts($1, $3, $5); }
	| exe_name redirect { $$ = bind_parts($1, NULL, $2); }
	| exe_name BLANK redirect { $$ = bind_parts($1, NULL, $3); }
	;

exe_name:
	word { $$ = $1; }
	| BLANK word { $$ = $2; }
	;

params:
	params BLANK word { $$ = add_word_to_list($3, $1); assert($$ == $1); }
	| word { $$ = $1; }
	;

redirect:
	{ /* empty */ $$.red_o = NULL; 	$$.red_i = NULL; 	$$.red_e = NULL; 	$$.red_flags = IO_REGULAR; }
	| redirect REDIRECT_OE word { 	$1.red_o = add_word_to_list($3, $1.red_o); 	$1.red_e = add_word_to_list($3, $1.red_e); 	$$ = $1; }
	| redirect REDIRECT_E word { 	$1.red_e = add_word_to_list($3, $1.red_e); 	$$ = $1; }
	| redirect REDIRECT_O word { 	$1.red_o = add_word_to_list($3, $1.red_o); 	$$ = $1; }
	| redirect REDIRECT_APPEND_E word { 	$1.red_e = add_word_to_list($3, $1.red_e); 	$1.red_flags |= IO_ERR_APPEND; 	$$ = $1; }
	| redirect REDIRECT_APPEND_O word { 	$1.red_o = add_word_to_list($3, $1.red_o); 	$1.red_flags |= IO_OUT_APPEND; 	$$ = $1; }
	| redirect INDIRECT word { 	$1.red_i = add_word_to_list($3, $1.red_i); 	$$ = $1; }
	| redirect REDIRECT_OE word BLANK { 	$1.red_o = add_word_to_list($3, $1.red_o); 	$1.red_e = add_word_to_list($3, $1.red_e); 	$$ = $1; }
	| redirect REDIRECT_E word BLANK { 	$1.red_e = add_word_to_list($3, $1.red_e); 	$$ = $1; }
	| redirect REDIRECT_O word BLANK { 	$1.red_o = add_word_to_list($3, $1.red_o); 	$$ = $1; }
	| redirect REDIRECT_APPEND_E word BLANK { 	$1.red_e = add_word_to_list($3, $1.red_e); 	$1.red_flags |= IO_ERR_APPEND; 	$$ = $1; }
	| redirect REDIRECT_APPEND_O word BLANK { 	$1.red_o = add_word_to_list($3, $1.red_o); 	$1.red_flags |= IO_OUT_APPEND; 	$$ = $1; }
	| redirect INDIRECT word BLANK { 	$1.red_i = add_word_to_list($3, $1.red_i); 	$$ = $1; }
	| redirect REDIRECT_OE BLANK word { 	$1.red_o = add_word_to_list($4, $1.red_o); 	$1.red_e = add_word_to_list($4, $1.red_e); 	$$ = $1; }
	| redirect REDIRECT_E BLANK word { 	$1.red_e = add_word_to_list($4, $1.red_e); 	$$ = $1; }
	| redirect REDIRECT_O BLANK word { 	$1.red_o = add_word_to_list($4, $1.red_o); 	$$ = $1; }
	| redirect REDIRECT_APPEND_E BLANK word { 	$1.red_e = add_word_to_list($4, $1.red_e); 	$1.red_flags |= IO_ERR_APPEND; 	$$ = $1; }
	| redirect REDIRECT_APPEND_O BLANK word { 	$1.red_o = add_word_to_list($4, $1.red_o); 	$1.red_flags |= IO_OUT_APPEND; 	$$ = $1; }
	| redirect INDIRECT BLANK word { 	$1.red_i = add_word_to_list($4, $1.red_i); 	$$ = $1; }
	| redirect REDIRECT_OE BLANK word BLANK { 	$1.red_o = add_word_to_list($4, $1.red_o); 	$1.red_e = add_word_to_list($4, $1.red_e); 	$$ = $1; }
	| redirect REDIRECT_E BLANK word BLANK { 	$1.red_e = add_word_to_list($4, $1.red_e); 	$$ = $1; }
	| redirect REDIRECT_O BLANK word BLANK { 	$1.red_o = add_word_to_list($4, $1.red_o); 	$$ = $1; }
	| redirect REDIRECT_APPEND_O BLANK word BLANK { 	$1.red_o = add_word_to_list($4, $1.red_o); 	$1.red_flags |= IO_OUT_APPEND; 	$$ = $1; }
	| redirect REDIRECT_APPEND_E BLANK word BLANK { 	$1.red_e = add_word_to_list($4, $1.red_e); 	$1.red_flags |= IO_ERR_APPEND; 	$$ = $1; }
	| redirect INDIRECT BLANK word BLANK { 	$1.red_i = add_word_to_list($4, $1.red_i); 	$$ = $1; }
	;

word:
	word WORD { $$ = add_part_to_word(new_word($2, false), $1); }
	| word ENV_VAR { $$ = add_part_to_word(new_word($2, true), $1); }
	| WORD { $$ = new_word($1, false); }
	| ENV_VAR { $$ = new_word($1, true); }
	;
%%
