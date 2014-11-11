#include <stdio.h>
#include <iostream>
#include <string>
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
    std::cout<<"구문분석 완료"<<std::endl;
    fclose(yyin);
    }
    std::cout<<"IR 코드 생성..."<<std::endl;
    CodeGenerator codegen;
    codegen.generateIR(*pRoot);
    std::cout<<"IR 코드 생성 완료..."<<std::endl;
    return 0;
}
