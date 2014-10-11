%option c++
%option noyywrap

%{
#include <iostream>
#include <cstdlib>
using namespace std;
enum token_number = { TCONST, IDEN, NUM, ASSIGN, ADD, SEMICOL, DOT, OBRACE, EBRACE, ERROR};

%}
%%
"const"   return(TCONST);
"="       return(ASGIN);
[1-9][0-9]* return(NUM);
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
