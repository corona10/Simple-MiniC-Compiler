#include <stdio.h>
#include <iostream>
extern FILE* yyin;
extern int yyparse();
using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
      std::cout<<"<Error> please Excute SMCC as 'SMCC <source file.mini> "<<std::endl;
      return -1;
    }else{

    yyin = fopen(argv[1], "r");
    yyparse();
    std::cout<<"Now Running Mini C Comiler"<<std::endl;
    fclose(yyin);
    }
    return 0;
}
