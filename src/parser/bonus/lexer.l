%option nostdinit never-interactive nounput noinput
%{

#include "lexer.h"

#ifndef YY_SKIP_YYWRAP
#  define YY_SKIP_YYWRAP 1
#endif

int yywrap(void)
{
	return 1;
}

%}

digit							[0-9]
letter							[a-zA-Z]
envVarName 						((_|{letter})(_|{letter}|{digit})*)
parameterValue 					(({letter}|{digit}|[\-\\+:._%?*~/,])+)
whitespace						[ \t]
newLine							(\r?\n)
substitutionCharacter			[$]
setValueCharacter				[=]
charStateAny					[']
allButCharStateAny				[^']
charStateAnyAndExpansion		["]
allButCharStateAnyAndExpansion	[^"$]
anyChar							(.|\n)
pipeChar						[|]
andChar							[&]
gtChar							[>]
gtgtChar						[>][>]
ltChar							[<]
semicolon						[;]

%s ACCEPT_ANY ACCEPT_ANY_AND_EXPANSION

%%
<INITIAL><<EOF>> {
	return END_OF_FILE;
}
<INITIAL>{newLine}{anyChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return CHARS_AFTER_EOL;
}
<INITIAL>{newLine} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return END_OF_LINE;
}
<INITIAL>{charStateAny} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	BEGIN(ACCEPT_ANY);
}
<INITIAL>{charStateAnyAndExpansion} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	BEGIN(ACCEPT_ANY_AND_EXPANSION);
}
<INITIAL>{semicolon} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return SEQUENTIAL;
}
<INITIAL>{pipeChar}{pipeChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return CONDITIONAL_NZERO;
}
<INITIAL>{pipeChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return PIPE;
}
<INITIAL>{andChar}{andChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return CONDITIONAL_ZERO;
}
<INITIAL>{andChar}{gtChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return REDIRECT_OE;
}
<INITIAL>{andChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return PARALLEL;
}
<INITIAL>[2]{gtgtChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return REDIRECT_APPEND_E;
}
<INITIAL>{gtgtChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return REDIRECT_APPEND_O;
}
<INITIAL>[2]{gtChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return REDIRECT_E;
}
<INITIAL>{gtChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return REDIRECT_O;
}
<INITIAL>{ltChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return INDIRECT;
}
<INITIAL>{whitespace}+ {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return BLANK;
}
<INITIAL>{setValueCharacter} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	yylval.string_un = strdup(yytext);
	pointerToMallocMemory(yylval.string_un);
	return WORD;
}
<INITIAL>{substitutionCharacter}{envVarName} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	yylval.string_un = strdup(yytext + 1);
	pointerToMallocMemory(yylval.string_un);
	return ENV_VAR;
}
<INITIAL>{substitutionCharacter} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return INVALID_ENVIRONMENT_VAR;
}
<INITIAL>{parameterValue} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	yylval.string_un = strdup(yytext);
	pointerToMallocMemory(yylval.string_un);
	return WORD;
}
<ACCEPT_ANY><<EOF>> {
	return UNEXPECTED_EOF;
}
<ACCEPT_ANY>{charStateAny} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	BEGIN(INITIAL);
}
<ACCEPT_ANY>{allButCharStateAny}* {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	yylval.string_un = strdup(yytext);
	pointerToMallocMemory(yylval.string_un);
	return WORD;
}
<ACCEPT_ANY_AND_EXPANSION><<EOF>> {
	return UNEXPECTED_EOF;
}
<ACCEPT_ANY_AND_EXPANSION>{charStateAnyAndExpansion} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	BEGIN(INITIAL);
}
<ACCEPT_ANY_AND_EXPANSION>{substitutionCharacter}{envVarName} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	yylval.string_un = strdup(yytext + 1);
	pointerToMallocMemory(yylval.string_un);
	return ENV_VAR;
}
<ACCEPT_ANY_AND_EXPANSION>{substitutionCharacter} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return INVALID_ENVIRONMENT_VAR;
}
<ACCEPT_ANY_AND_EXPANSION>{allButCharStateAnyAndExpansion}* {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	yylval.string_un = strdup(yytext);
	pointerToMallocMemory(yylval.string_un);
	return WORD;
}
{anyChar} {
	yylloc.first_column = yylloc.last_column; yylloc.last_column += yyleng;
	return NOT_ACCEPTED_CHAR;
}
%%

extern YY_BUFFER_STATE myState;
extern bool haveOneBufferState;

void globalParseAnotherString(const char * str)
{
	globalEndParsing();
	myState = yy_scan_string(str);
	BEGIN(INITIAL);
	haveOneBufferState = true;
}
