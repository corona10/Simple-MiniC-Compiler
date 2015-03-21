/**
The MIT License (MIT)



Copyright (c) 2014-2015 Dong-hee,Na



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions:



The above copyright notice and this permission notice shall be included in

all copies or substantial portions of the Software.



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN

THE SOFTWARE
**/
%{
#include "AST.hpp"
#include <iostream>
#include <cstdlib>
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define  TOKEN(t) (yylval.token = t)
extern "C" int yywrap(){}
%}

%%

int  SAVE_TOKEN; return TINT;
float SAVE_TOKEN; return TFLOAT;
double SAVE_TOKEN; return TDOUBLE;
void   SAVE_TOKEN; return TVOID;
return SAVE_TOKEN; return TRETURN;
"="  return TOKEN(TASSIGN);
"==" return TOKEN(TEQUAL);
"!"  return TOKEN(TNOT);
"!=" return TOKEN(TNEQUAL);
"<"  return TOKEN(TLESS);
"<=" return TOKEN(TLESSEQ);
">"  return TOKEN(TGREAT);
">=" return TOKEN(TGREATEQ);
[a-zA-Z_][a-zA-Z0-9_]* SAVE_TOKEN; return TIDENT;
[0-9][0-9]*            SAVE_TOKEN; return TINT_VALUE;
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

