%{
#include <stdio.h>
#include <stdlib.h>
extern int yylex();
extern FILE* yyin;
%}

/* Definitions of patterns and tokens */
letter          [a-zA-Z]
digit           [0-9]
datatype        "int"|"float"|"boolean"
id              {letter}({letter}|{digit})*
digits          {digit}+
num             {digits}|{digits}\.({digits}+|\L)
relop           (==|!=|>|>=|<|<=)
assign          =
if_else_while   "if"|"else"|"while"
punctuations    [;,\(\){}]

/* Define rules for tokens */
%%
{datatype}          { printf("%s\n", yytext); return 1; }
{num}               { printf("num\n"); return 1; }
{relop}             { printf("relop\n"); return 1; }
{assign}            { printf("assign\n"); return 1; }
{if_else_while}     { printf("%s\n", yytext); return 1; }
{id}                { printf("id\n"); return 1; }
{punctuations}      { printf("%s\n", yytext); return 1; }
[ \t\n]             ; /* Ignore whitespace */
.                   { printf("Error: invalid input\n"); return 1; }
%%

int main(int argc, char* argv[]) {
     if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "r");
    //yyin = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    //int token;
    //while((token = yylex(yyin)) != 0){}

    yyin = file;
    while(yylex() != 0){}
    
    fclose(file);
    return EXIT_SUCCESS;
}
