#include <iostream>
extern int yyparse();
using namespace std;

int main()
{
    yyparse();
    std::cout<<"Now Running Mini C Comiler"<<std::endl;
    return 0;
}
