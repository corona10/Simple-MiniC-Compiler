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
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include "CodeGenerator.hpp"
#include "AST.hpp"
#include "parser.hpp"


extern FILE* yyin;
extern int yyparse();
extern CRootAST* pRoot;
using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
      std::cout<<"<Error> please excute SMCC, such as 'smcc <source file.mini> <ouput_name> "<<std::endl;
      std::cout<<"        SMCC is written by Dong-hee,Na (corona10@gmail.com)"<<std::endl;
      return -1;
    }else{

    yyin = fopen(argv[1], "r");
    yyparse();
    std::cout<<"\n<info> Syntatic parsing completed.."<<std::endl;
    fclose(yyin);
    }
    std::cout<<"<info> Generating LLVM IR Code..."<<std::endl;
    CodeGenerator codegen(argv[2]);
    codegen.generateIR(*pRoot);
    return 0;
}
