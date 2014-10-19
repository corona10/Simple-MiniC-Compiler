%{
   #include "AST.hpp"
   CBlock *programBlock;

   extern int yylex();
   void yyerror(const char* s);



%}
