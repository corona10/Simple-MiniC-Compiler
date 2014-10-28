%{
   #include <iostream>
   extern int yylex();
   void yyerror(const char *s){} 
%}

%union
{
   int token;
}
%token TINT TFLOAT TIDENT
%token TLBRACE TRBRACE
%token TASSIGN TEQUAL TNOT TNEQUAL TLESS TLESSEQ TGREAT TGREATEQ
%token TPLUS TMINUS TMULTI TDIVIDE TMODULO
%token TSEMI
%left TPLUS TMINUS
%left TMUL TDIV
%right TEQUAL


%%

var_decl : ident ident TSEMI { std::cout<<"Variable with out Number"<<std::endl;}
         | ident ident TASSIGN number TSEMI {std::cout<<"Variable with Number!"<<std::endl;}
         ;

ident : TIDENT
      ;
number: TINT
      | TFLOAT
      ;
              
%%
