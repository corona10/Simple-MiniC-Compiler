%{
#include <iostream>
#include <cstdlib>
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define  TOKEN(t) (yylval.token = t)
extern "C" int yywrap(){}
%}

%%
"int" return TOKEN(TINT);
"float" return TOKEN(TFLOAT);
"double" return TOKEN(TDOUBLE);
"="  return TOKEN(TASSIGN);
"==" return TOKEN(TEQUAL);
"!"  return TOKEN(TNOT);
"!=" return TOKEN(TNEQUAL);
"<"  return TOKEN(TLESS);
"<=" return TOKEN(TLESSEQ);
">"  return TOKEN(TGREAT);
">=" return TOKEN(TGREATEQ);
[a-zA-Z_][a-zA-Z0-9_]* SAVE_TOKEN; return TIDENT;
[1-9][0-9]*            SAVE_TOKEN; return TINT_VALUE;
[0-9]+\.[0-9]*         SAVE_TOKEN; return TFLOAT_VALUE;
"{"                    return TOKEN(TLBRACE);
"}"                    return TOKEN(TRBRACE);
"("                    return TOKEN(TLSBRACE);
")"                    return TOKEN(TRSBRACE);
"+"                    return TOKEN(TPLUS);
"-"                    return TOKEN(TMINUS);
"*"                    return TOKEN(TMUL);
"/"                    return TOKEN(TDIVIDE);
"%"                    return TOKEN(TMODULO);
";"                    return TOKEN(TSEMI);
","                    return TOKEN(TCOMMA);
[\t\n]                   ;
%%

