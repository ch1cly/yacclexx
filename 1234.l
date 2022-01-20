%option yylineno
%option noyywrap
%{
#include <stdio.h>
#include "y.tab.h"
int position = 0;
int errorCount = 0;
%}

letter [A-Za-z]
digit [0-9]

%%
[Ee][Xx][Ii][Tt]                { position+=yyleng; printf("exit \n"); return yEXIT;}
[Ff][Oo][Rr]                    { position+=yyleng; printf("for ");  return yFOR;}
[Ee][Nn][Dd][Ff][Oo][Rr]        { position+=yyleng; printf("endfor \n"); return yENDFOR;}
[Ss][Tt][Ee][Pp]                { position+=yyleng; printf("step = "); return ySTEP;}
[Tt][Oo]                        { position+=yyleng; printf("to "); return yTO;}
[Ll][Oo][Oo][Pp]                { position+=yyleng; printf("loop\n"); return yLOOP;}
[Nn][Ee][Xx][Tt]                { position+=yyleng; printf("next\n"); return yNEXT;}
[Ee][Xx][Ee][Cc][Uu][Tt][Ee]    { position+=yyleng; printf("command(execute)\n"); return yEXECUTE;}
[Rr][Ee][Aa][Dd]                { position+=yyleng; printf("command(read)\n"); return yREAD;}
[Ww][Rr][Ii][Tt][Ee]            { position+=yyleng; printf("command(write) \n"); return yWRITE;}
(0|[1-9][0-9]*)          {
                            position+=yyleng;
                          printf("number ");
                          yylval.num = yytext[0]-'0';

                          for (int i = 1; i < yyleng; i++){
                              yylval.num = yylval.num * 10 + (yytext[i]-'0');
                           }
                           printf("%d ", yylval.num);
                         return yNUMBER;
                         
}


({letter}({letter}|{digit})*)    { position+=yyleng; yylval.str = strdup(yytext); printf(" varname "); return yVARNAME;}

;                              { position+=yyleng;  printf("SEMICOLON\n"); return ySEMICOLON;}
"="                             { position+=yyleng; printf("EQ "); return yEQ;}
"+"                             { position+=yyleng; printf("PLUS "); return yPLUS;}
"-"                             { position+=yyleng; printf("MINUS "); return yMINUS;}
"/"                             { position+=yyleng; printf("DIVIDE "); return yDIVIDE;}
"*"                             { position+=yyleng; printf("MULT "); return yMULT;}
[ \t]+                          { position+=yyleng;  }    ;
\n             /*return('\n')*/{ position = 0; };
.             /*return(yytext[0])*/ { position++; errorCount++;
                                            printf("at line %d, position %d : lexical error: unknown character '%c'\n", yylineno, position, yytext[0]);
}


