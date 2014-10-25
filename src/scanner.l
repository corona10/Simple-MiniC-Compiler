%{
#include <cstdlib>
#include "AST.hpp"
#include "parser.hpp"

%}
%%
"="       return(TASIGN);
"=="      return (TEQUAL);
"!"       return (TNOT);
"!="      return (TNEQUAL);
"<"       return (TLESS);
"<="      return (TLESSEQ);
">"       return (TGREAT);
">="      return (TGREATEQ);
[a-zA-Z_][a-zA-Z0-9_]* return (TIDENT);
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
"int"     return (TINT);
"float"   return (TFLOAT);
"double"  return (TDOUBLE);
"void"    return (TVOID);
%%

yywrap()
{
     return 1;
}


