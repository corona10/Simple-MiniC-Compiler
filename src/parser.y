%{
   #include <iostream>
   extern int yylex();
   void yyerror(const char *s){} 
%}

%union
{
   int token;
   std::string *string;
}
%token TINT_VALUE TFLOAT_VALUE TIDENT
%token TLBRACE TRBRACE TLSBRACE TRSBRACE
%token TASSIGN TEQUAL TNOT TNEQUAL TLESS TLESSEQ TGREAT TGREATEQ
%token TPLUS TMINUS TMULTI TDIVIDE TMODULO
%token TSEMI TCOMMA
%token TINT TDOUBLE TFLOAT
%token TMAIN

%left TPLUS TMINUS
%left TMUL TDIV
%right TEQUAL

%start program

%%

program : stmts
        ;

stmts   : stmt
        | stmts stmt
        ;

stmt    : var_decl TSEMI
        | function_call TSEMI
        ;

function_call : ident TLSBRACE arg_list TRSBRACE {std::cout <<"Function call!!"<<std::endl;}
              | ident TLSBRACE TRSBRACE {std::cout << "Function Call!!" <<std::endl;}
             ;
var_decl : type ident { std::cout<<"Variable with out Number"<<std::endl;}
         | type  ident TASSIGN number {std::cout<<"Variable with Number!"<<std::endl;}
         ;
         
arg_list : arg_list TCOMMA number
         | number
         ;
ident : TIDENT
      ;

type  : TINT
      | TDOUBLE
      | TFLOAT
      ;
number: TINT_VALUE
      | TFLOAT_VALUE
      ;
              
%%
