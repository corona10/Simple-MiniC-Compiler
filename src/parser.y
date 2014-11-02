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
%left TPLUS TMINUS
%left TMUL TDIV
%right TEQUAL

%start program

%%

program : definition
        ;
definition  : definition function_def
            | function_def
            ;
function_def : function_def_hd block_stmts { std::cout<<"function def"<<std::endl;}
             ;
function_def_hd : type ident TLSBRACE arg_list TRSBRACE
                | type ident TLSBRACE TRSBRACE
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
function_call : ident TLSBRACE para_list TRSBRACE
              | ident TLSBRACE TRSBRACE 
              ;


var_decl : type ident { std::cout<<"Variable with out Number"<<std::endl;}
         | type  ident TASSIGN number {std::cout<<"Variable with Number!"<<std::endl;}
         ;
         
para_list : para_list TCOMMA value
          | value
          ;
arg_list : arg_list TCOMMA type ident
         | type ident
         ;
ident : TIDENT
      ;

type  : TINT
      | TDOUBLE
      | TFLOAT
      ;
value : number
      | ident
      ;
number : TINT_VALUE
       | TFLOAT_VALUE
              
%%
