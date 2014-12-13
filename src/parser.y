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
   std::vector<CVarDeclare*> *arg_vec;
   std::vector<CValue*> *para_vec;
   CFunctionDefine* func_define;
   CRootAST* root;
   CBlock*   block;
   CVarDeclare* var_declare;
   CReturn* return_inst;
   CBaseAST* base;
   CFunctionCall* func_call;
   CBinaryOperator* binary_op;
   CNumber* num;
   
}
%token TINT_VALUE TFLOAT_VALUE TIDENT
%token TLBRACE TRBRACE TLSBRACE TRSBRACE
%token TASSIGN TEQUAL TNOT TNEQUAL TLESS TLESSEQ TGREAT TGREATEQ
%token TPLUS TMINUS TMULTI TDIVIDE TMODULO
%token TSEMI TCOMMA
%token TINT TDOUBLE TFLOAT TVOID
%token TRETURN

%type <string> TIDENT 
%type <string>  TINT_VALUE TFLOAT_VALUE
%type <string> type TINT TFLOAT TDOUBLE TVOID TRETURN
%type <func_define> function_def
%type <arg_vec> arg_list
%type <para_vec> para_list
%type <root> definition
%type <base> stmt
%type <block> stmts block_stmts  
%type <var_declare> var_decl
%type <return_inst> return_inst
%type <func_call>  function_call
%type <binary_op> binary_ops
%type <num> number
%type <token> OP TPLUS TMINUS TMUL TDIVIDE TMODULO TASSIGN TEQUAL
%left TPLUS TMINUS
%left TMUL TDIV
%right TEQUAL

%start program

%%

program : definition { pRoot = $1;}
        ;
definition  : definition function_def 
               {
                 $1->AST_List.push_back($2);
               }
            | function_def
              {
               $$ = new CRootAST();
               $$->AST_List.push_back($1);
              }
            | stmt
              {
               $$ = new CRootAST();
              }
            ;
function_def : type TIDENT TLSBRACE arg_list TRSBRACE  block_stmts
               {
                 $$ = new CFunctionDefine(*$1, *$2, *$4);
                 $$->block_list.push_back($6);
               }
             | type TIDENT TLSBRACE TRSBRACE block_stmts 
               { 
                 $$ = new CFunctionDefine(*$1, *$2);
                 $$->block_list.push_back($5);
                }
             ;
block_stmts : TLBRACE stmts TRBRACE  {$$ = $2;}
            | TLBRACE TRBRACE        {$$ = new CBlock("entry");}
            ;
stmts   : stmt {$$ = new CBlock("entry"); $$->instruction_list.push_back($1);}
        | stmts stmt  {$1->instruction_list.push_back($2);}
        ;

stmt    : var_decl TSEMI { $$ = $1;}
        | function_call TSEMI { $$ = $1; }
        | return_inst TSEMI {$$ = $1;}
        | binary_ops TSEMI  {$$ = $1;}
        ;
function_call : TIDENT TLSBRACE para_list TRSBRACE { $$ = new CFunctionCall(*$1, *$3);}
              | TIDENT TLSBRACE TRSBRACE { $$ = new CFunctionCall(*$1);}
              ;

return_inst  : TRETURN TINT_VALUE {$$ = new CReturn(0, *$2);}
             | TRETURN TFLOAT_VALUE {$$ = new CReturn(0, *$2);}
             | TRETURN TIDENT {$$ = new CReturn(1, *$2);}
             ;
var_decl : type  TIDENT  { $$ = new CVarDeclare(*$1, *$2);}
         | type  TIDENT TASSIGN TINT_VALUE  {$$ = new CVarDeclare(*$1, *$2, *$4);}
         | type  TIDENT TASSIGN TFLOAT_VALUE  {$$ = new CVarDeclare(*$1, *$2, *$4);}
         ;
         
para_list : para_list TCOMMA TIDENT
            {
                 $$->push_back(new CValue("unknown", *$3));
            }
          | TIDENT
            {
               $$ = new std::vector<CValue*>();
               $$->push_back(new CValue("unknown", *$1));
            }
          ;
arg_list : arg_list TCOMMA type TIDENT
           {
              $$->push_back(new CVarDeclare(*$3, *$4));
           }
         | type TIDENT
           {
               $$ = new std::vector<CVarDeclare*>();
               $$->push_back(new CVarDeclare(*$1, *$2));
           }
         ;
OP : TPLUS | TEQUAL | TMINUS | TMUL | TDIVIDE | TMODULO | TASSIGN
   ;
binary_ops : number  OP  binary_ops
             {
                $$ = new CBinaryOperator(*$1, $2, *$3);
             }
            | TIDENT OP binary_ops
             {
                $$ = new CBinaryOperator(CValue("unknown", *$1), $2, *$3);
             }
            | number OP  number
             {
                $$ = new  CBinaryOperator(*$1, $2, *$3);
             }
            | TIDENT OP TIDENT
             {
               $$ = new CBinaryOperator(CValue("unknown", *$1), $2, CValue("unknwon", *$3));
             } 
           | TIDENT OP number
             {
              $$ = new CBinaryOperator(CValue("unknown", *$1), $2, *$3);
             }
          ;
type  : TINT
      | TFLOAT
      | TDOUBLE
      ;
number : TINT_VALUE
        {
           $$ = new CNumber("int", *$1);
        }
       | TFLOAT_VALUE
        {
          $$ = new CNumber("fp", *$1);
        }
       
       ;
              
%%
