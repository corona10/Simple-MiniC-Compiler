%{
   #include <iostream>
   #include <string>
   #include "AST.hpp"
   extern int yylex();
   void yyerror(const char *s){} 
%}

%union
{
   int token;
   std::string *string;
   CFunctionDefine* func_define;
}
%token TINT_VALUE TFLOAT_VALUE TIDENT
%token TLBRACE TRBRACE TLSBRACE TRSBRACE
%token TASSIGN TEQUAL TNOT TNEQUAL TLESS TLESSEQ TGREAT TGREATEQ
%token TPLUS TMINUS TMULTI TDIVIDE TMODULO
%token TSEMI TCOMMA
%token TINT TDOUBLE TFLOAT TVOID

%type <string> TIDENT
%type <string> number TINT_VALUE TFLOAT_VALUE
%type <string> type TINT TFLOAT TDOUBLE TVOID
%type <func_define> function_def
%left TPLUS TMINUS
%left TMUL TDIV
%right TEQUAL

%start program

%%

program : definition
        ;
definition  : definition function_def
            | function_def
            | stmt
            ;
function_def : type TIDENT TLSBRACE arg_list TRSBRACE  block_stmts { std::cout<<"function def"<<std::endl;}
             | type TIDENT TLSBRACE TRSBRACE block_stmts { $$ = new CFunctionDefine(*$1, *$2); std::cout<<"function with out arg_list.. " <<std::endl;}
             ;
block_stmts : TLBRACE stmts TRBRACE  {std::cout<<"block stmts"<<std::endl;}
            | TLBRACE TRBRACE        {std::cout<<"block stmts"<<std::endl;}
            ;
stmts   : stmt
        | stmts stmt
        ;

stmt    : var_decl TSEMI
        | function_call TSEMI {std::cout<<"Function call!!"<<std::endl;}
        | TSEMI
        ;
function_call : TIDENT TLSBRACE para_list TRSBRACE
              | TIDENT TLSBRACE TRSBRACE 
              ;


var_decl : type  TIDENT  {std::cout<<"type: "<<*$1<<", val_name: "<<*$2<<std::endl;}
         | type  TIDENT TASSIGN number  {std::cout<<"type: "<<*$1<<", val_name: "<<*$2<<", value: "<<*$4 <<std::endl; delete $4;}
         ;
         
para_list : para_list TCOMMA value
          | value
          ;
arg_list : arg_list TCOMMA type TIDENT
         | type TIDENT
         ;
type  : TINT
      | TFLOAT
      | TDOUBLE
      ;
value : number
      | TIDENT
      ;
number : TINT_VALUE 
       | TFLOAT_VALUE

              
%%
