/**
@author : Dong-hee , Na
@date   : 2014-10-17
**/

// library list of LLVM
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
// library list of std
#include <iostream>
#include <vector>
#include <stack>
using namespace llvm;

class  CodeBlock
{
    public:
    llvm::BasicBlock *block;
    std::map<std::string, llvm::Value*> block_map;
};

class  CodeGenerator{

       public:
       
       //생성자
       CodeGenerator()
       {   
       }
 
       CodeGenerator(std::string& programName)
       {
         this->_module = new Module(programName, getGlobalContext()); 
       }

       private:
       llvm::Module*   _module;
       

};


