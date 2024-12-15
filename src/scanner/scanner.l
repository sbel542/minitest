%top {
/* ===================================================================== */
/* Project: minishell                                                    */
/* Module : shell scanner                                                */
/* ===================================================================== */
}

/* option batch OU interactive */
%option nostdinit noyywrap nounput noinput reentrant

%{
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

/* Value type.  */
union YYSTYPE
{
	char *string_val;
} yylval;


%}

digit							[0-9]
letter							[a-zA-Z]
envVarName 						((_|{letter})(_|{letter}|{digit})*)
parameterValue 					(({letter}|{digit}|[\-\\+:._%?*~/,])+)
whitespace						[ \t]
newLine							(\n)
dollar							[$]
setValueCharacter				[=]
singleQuote						[']
allButSingleQuote				[^']
doubleQuote						["]
allButdoubleQuote				[^"$]
anyChar							(.|\n)
pipeChar						[|]
andChar							[&]
gtChar							[>]
gtgtChar						[>][>]
ltChar							[<]
semicolon						[;]

%s SQUOTED DQUOTED

%%
<INITIAL><<EOF>>				{ yylval.string_val = NULL; fprintf(yyout, "%s\n", "End of input"); yyterminate(); return END_OF_FILE; }
	 /* https://superuser.com/questions/895266/bind-a-key-to-newline-in-bash-without-submitting-command */
<INITIAL>{newLine}				{ yylval.string_val = NULL; return EOL; }
<INITIAL>{singleQuote}			{ yylval.string_val = NULL; BEGIN(SQUOTED); }
<INITIAL>{doubleQuote}			{ yylval.string_val = NULL; BEGIN(DQUOTED); }
<INITIAL>{pipeChar}{pipeChar}	{ yylval.string_val = NULL; return OR_LIST; }
<INITIAL>{pipeChar}				{ yylval.string_val = NULL; return PIPE; }
<INITIAL>{andChar}{andChar} 	{ yylval.string_val = NULL; return AND_LIST; }
<INITIAL>{andChar}{gtChar}		{ yylval.string_val = NULL; return REDIRECT_OE; }
<INITIAL>[2]{gtgtChar}			{ yylval.string_val = NULL; return REDIRECT_APPEND_E; }
<INITIAL>{gtgtChar}				{ yylval.string_val = NULL; return REDIRECT_APPEND_O; }
<INITIAL>[2]{gtChar}			{ yylval.string_val = NULL; return REDIRECT_E; }
<INITIAL>{gtChar}				{ yylval.string_val = NULL; return REDIRECT_O; }
<INITIAL>{ltChar}				{ yylval.string_val = NULL; return REDIRECT_IN; }
<INITIAL>{ltChar}{ltChar}		{ yylval.string_val = NULL; return HEREDOC; }
<INITIAL>{whitespace}+			{ yylval.string_val = NULL; return BLANK; }
<INITIAL>{setValueCharacter}	{ yylval.string_val = strdup(yytext); return WORD; }
<INITIAL>{dollar}{envVarName}	{ yylval.string_val = strdup(yytext + 1); return ENV_VAR; }
<INITIAL>{dollar}				{ yylval.string_val = NULL; return DOLLAR_SIGN; }
<INITIAL>{parameterValue}		{ yylval.string_val = strdup(yytext); return WORD; }

<SQUOTED><<EOF>>				{ yylval.string_val = NULL; BEGIN(INITIAL); return UNEXPECTED_EOF; }
<SQUOTED>{singleQuote}			{ yylval.string_val = NULL; BEGIN(INITIAL); }
<SQUOTED>{allButSingleQuote}* 	{ yylval.string_val = strdup(yytext); return WORD; }

<DQUOTED><<EOF>>				{ yylval.string_val = NULL; BEGIN(INITIAL); return UNEXPECTED_EOF; }
<DQUOTED>{doubleQuote}			{ yylval.string_val = NULL; BEGIN(INITIAL); }
<DQUOTED>{dollar}{envVarName} 	{ yylval.string_val = strdup(yytext + 1);  return ENV_VAR; }
<DQUOTED>{dollar}				{ yylval.string_val = NULL; return DOLLAR_SIGN; }
<DQUOTED>{allButdoubleQuote}*	{ yylval.string_val = strdup(yytext); return WORD; }

{anyChar}						{ yylval.string_val = NULL; return NOT_ACCEPTED_CHAR; }
%%
