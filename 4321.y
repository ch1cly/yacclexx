%union
{
        int num;
        char *str;
}



%token yFOR ySTEP yENDFOR yNEXT yTO
%token yLOOP yEXIT yREAD yEXECUTE yWRITE
%token yPLUS yMINUS yMULT yDIVIDE yEQ yOP yCP
%token <str> yVARNAME
%token <num> yNUMBER
%token ySEMICOLON

%type <num> exp term
%type <str> declExp

%left yEQ
%left yPLUS yMINUS
%left yMULT yDIVIDE
%right UMINUS



%{
#include <stdio.h>
#include <stdlib.h>

#include "variables.h"



extern int position;
extern int yylineno;
extern int errorCount;

extern int yylex(void);
void yyerror(char *);
void runtime_error(char *str);

VariableContainerNode *root = NULL;

%}







%%
list:
                | list stat ySEMICOLON
                | list stat error { printf("semicolon is missing\n"); }
                | list error ySEMICOLON { printf("syntax error\n"); }
        ;

stat:            for
                | comm
                ;

                
                
                
for:           yFOR declExp yTO exp step forCommands endfornext {printf("for ended!\n");}
            |error declExp yTO exp step forCommands endfornext {printf("for is missing!\n");}
            |yFOR declExp error exp step forCommands endfornext {printf("to is missing!\n");}
            |yFOR declExp yTO error step forCommands endfornext {printf("final value is missing!\n");}
;

forCommands: commands
;
                

commands:
      list
    | commands exitloop
    ;

exitloop:
    yEXIT
    | yLOOP
    ;


step:
| ySTEP exp  ;
    

endfornext:      yENDFOR
            |yNEXT
    ;


    


comm: yREAD
    | yEXECUTE
    | yWRITE      
    | declExp
    ;
    
declExp: yVARNAME yEQ exp{
int num = $3;
char *variableName = $1;
printf("%s = %d\n", variableName, num);
assignVariable(root, variableName, num);
$$ = variableName;
}
|yVARNAME error{ yyerror("= is missing\n"); }
|yVARNAME yEQ error { yyerror("value of variable is missing\n"); }
    ;
    
    
    
    exp:              term
                     | exp yPLUS exp            { $$ = $1 + $3;   }
                     | exp yMINUS exp           { $$ = $1 - $3;   }
                     | exp yMULT exp        { $$ = $1 * $3;   }
                     | exp yDIVIDE exp {
                        if ($3 == 0) {
                            runtime_error("division by zero.");
                        } else {
                            $$ = $1 / $3;
                        }
                      }
                     | yMINUS exp %prec UMINUS  { $$ = -$2;       }
                     | yOP exp yCP              { $$ = $2;        }
                     ;

                     
                     
term:             yNUMBER                    { $$ = $1; }
                                      | yVARNAME                  {
                                          char *variableName = $1;
                                         Variable *variable = getVariableFromList(root, variableName);
                                         if (variable == NULL) {
                                             char msg[80];
                                             sprintf(msg, "unknown varname %s", $1);
                                             runtime_error(msg);
                                             //showAllVariables(root);
                                         } else {
                                             $$ = variable->value;
                                         }
                                       }
                                      ;

%%




int main(int argc, char **argv) {
    
    root = createVariableContainerNodeList();
    yyparse();
    deleteAllVariables(root);
    
    if (errorCount == 0) {
        printf("Parsed successfully.\n");
    } else {
        printf("Parsed with %d errors.\n", errorCount);
    }
}

    void yyerror(char *str) {
        if (strcmp(str, "syntax error")) { printf("at line %d, position %d : syntax error: %s\n", yylineno, position, str); errorCount++; }
    }

    void runtime_error(char *str) {
        printf("at line %d, position %d : runtime error: %s\n", yylineno, position, str); errorCount++;
    }
