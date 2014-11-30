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
    CodeGenerator codegen;
    codegen.generateIR(*pRoot);
    return 0;
}
