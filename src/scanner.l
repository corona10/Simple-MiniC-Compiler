D       [0-9]
L       [a-zA-Z_]
H       [a-fA-FO-9]

%{
#include <cstdlib>
#include "AST.hpp"
#include "parser.hpp"

%}
%%
"const"   return(TCONST);
"="       return(TASIGN);
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
"return"  return (TRETURN);

%%

yywrap()
{
     return 1;
}


