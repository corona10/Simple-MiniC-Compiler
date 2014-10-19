%{
   #include "AST.hpp"
   CBlock *programBlock;

   extern int yylex();
   void yyerror(const char* s);



%}

%type <stmt> stmt var_decl funcl_decl
%type <block> program stmts

%left TPLUS, TMINUS
%left TMUL, TDIV

%start program

%%

program : stmts { programBlock = $1 }
        ;

stmts   : stmt { $$ = new CBlock(); $$->statements.push_back($<stmt>1);}
        | stmts stmt {$1->statemets.push_back($<stmt>2);}
        ;

stmt    : var_decl
        | func_decl
        | expr { $$ = new CExpressionStatement(*$1);}
        ;
unary_operator:TASIGN
              |TEQUAL
              |TNOT
              |TNEQUAL
              |TPLUS
              |TMINUS
              |TMULTI
              |TDIVIDE
              |TMODULO
              ;

%%
