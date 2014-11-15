%{
   #include <iostream>
   #include <string>
   #include "AST.hpp"
   extern int yylex();
   void yyerror(const char *s){}
   
   CRootAST* pRoot; 
%}

%union
{
   int token;
   std::string *string;
   CFunctionDefine* func_define;
   CRootAST* root;
   CBlock*   block;
   CVarDeclare* var_declare;
}
%token TINT_VALUE TFLOAT_VALUE TIDENT
%token TLBRACE TRBRACE TLSBRACE TRSBRACE
%token TASSIGN TEQUAL TNOT TNEQUAL TLESS TLESSEQ TGREAT TGREATEQ
%token TPLUS TMINUS TMULTI TDIVIDE TMODULO
%token TSEMI TCOMMA
%token TINT TDOUBLE TFLOAT TVOID
%token TRETURN

%type <string> TIDENT
%type <string> number TINT_VALUE TFLOAT_VALUE
%type <string> type TINT TFLOAT TDOUBLE TVOID

%type <func_define> function_def
%type <root> definition
%type <block> stmts block_stmts 
%type <var_declare> var_decl stmt
%left TPLUS TMINUS
%left TMUL TDIV
%right TEQUAL

%start program

%%

program : definition { pRoot = $1;}
        ;
definition  : definition function_def {$1->AST_List.push_back($2);}
            | function_def {$$ = new CRootAST(); $$->AST_List.push_back($1);}
            | stmt {$$ = new CRootAST();}
            ;
function_def : type TIDENT TLSBRACE arg_list TRSBRACE  block_stmts { std::cout<<"function def"<<std::endl;}
             | type TIDENT TLSBRACE TRSBRACE block_stmts { $$ = new CFunctionDefine(*$1, *$2); $$->block_list.push_back($5);  std::cout<<"function with out arg_list.. " <<std::endl;}
             ;
block_stmts : TLBRACE stmts TRBRACE  {$$ = $2;}
            | TLBRACE TRBRACE        {$$ = new CBlock("entry");}
            ;
stmts   : stmt {$$ = new CBlock("entry"); $$->instruction_list.push_back($1);}
        | stmts stmt  {$1->instruction_list.push_back($2);}
        ;

stmt    : var_decl TSEMI { $$ = $1;}
        | function_call TSEMI {std::cout<<"Function call!!"<<std::endl;}
        | TSEMI
        ;
function_call : TIDENT TLSBRACE para_list TRSBRACE
              | TIDENT TLSBRACE TRSBRACE 
              ;


var_decl : type  TIDENT  { $$ = new CVarDeclare(*$1, *$2);}
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
       ;
              
%%
