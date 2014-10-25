%{
   #include "AST.hpp"
   CBlock *programBlock;

   extern int yylex();
   void yyerror(const char* s);



%}

%union
{
   CBlock* block;
   CIdentifier* ident;
   CFuntionCall* func_call;
   
   CInteger *tint;
   CFloat *tfloat;
   CDouble *tdoule;
   int token;  
   
}

%type <stmt> stmt var_decl funcl_decl
%type <block> program stmts

%left TPLUS, TMINUS
%left TMUL, TDIV
%right TEQUAL

%start program



%%

program : function
        | declaration
        ;
type    : TINT
        | TFLOAT
        | TDOUBLE
        | TVOID

stmts   : stmt { $$ = new CBlock(); $$->statements.push_back($<stmt>1);}
        | stmts stmt {$1->statemets.push_back($<stmt>2);}
        ;

stmt    : var_decl
        | func_decl
        | expr { $$ = new CExpressionStatement(*$1);}
        ;

var_decl : type ident ';'
         | type ident '=' number ';'
         ;

number   : TINTIEGER { $$ = new CInteger(stol($1)); delete $1;}
         : TFLOAT    { $$ = new CFloat(stof($1));  delete $1;}
         : TDOUBLE   { $$ = new CDouble(stof($1)); delete $1;}
         ;
unary_operator :TASIGN
               |TEQUAL
               |TNOT
               |TNEQUAL
               |TPLUS
               |TMINUS
               |TMULTI
               |TDIVIDE
               |TMODULO
               ;
block   : '{' stmts '}' { $$ = $2}
        | '{' '}' { $$ = new CBlock()}
        ;
ident   : TIDENT{ $$ = new CIdentifier(*$1); delete $1;}

%%
#include <iostream>

int main(int argc, char* argv[])
{
    yyin = fopen(argv[1] "r");
    
     if(yypare() == true)
        std::cout<<"Parsing Completed!!"<<std::endl;
     else
        std::cout<<"Parsing Failed!!"<<std::endl;

    fclose(yyin);

    return 0;
}
