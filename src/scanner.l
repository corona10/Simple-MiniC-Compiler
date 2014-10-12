%{
#include <iostream>
#include <cstdlib>
#include "AST.hpp"
#include "parser.hpp"
using namespace std;
enum token_number = { TCONST, TIDEN, TINTEGER,TFLOAT, TASSIGN, TADD, TSEMICOL, TDOT, TOBRACE, TEBRACE, TERROR};

%}
%%
"const"   return(TCONST);
"="       return(ASGIN);
[1-9][0-9]* return(TINTEGER);
[0-9].[0-9]* return (TFLOAT);
"{"       return(OBRACE);
"}"       return(EBRACE);
%%

int main()
{
   cout<<"Start Of LEX"<<endl;
   return 0;
}
int yywrap()
{
   return 1;
}
