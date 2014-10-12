%{
#include <cstdlib>
#include "AST.hpp"
#include "parser.hpp"

%}
%%
"const"   return(TCONST);
"="       return(TASGIN);
"=="      return (TEQUAL);
"!"       return (TNOT);
"!="      return (TNEQUAL);
[1-9][0-9]* return(TINTEGER);
[0-9].[0-9]* return (TFLOAT);
"{"       return(TOBRACE);
"}"       return(TEBRACE);
"+"       return (TPLUS);
"-"       return (TMINUS);
"*"       return (TMULTI);
"/"       return (TDIVIDE);
"%"       return (TMODULO);

%%
extern "C" int yywrap();

int main()
{
   cout<<"Start Of LEX"<<endl;
   return 0;
}

int yywrap()
{
   return 1;
}
