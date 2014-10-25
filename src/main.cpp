#include <iostream>
#include "CodeGenerator.hpp"
#include "AST.hpp"

using namespace std;

int main()
{
    yyparse();
    std::cout<<"Now Running Mini C Comiler"<<std::endl;
    CodeGenerator codegen;
    codegen.generateCode();

    //codegen.runCode();
    return 0;
}
