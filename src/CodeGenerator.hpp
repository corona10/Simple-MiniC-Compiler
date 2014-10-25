/**
@author : Dong-hee , Na
@date   : 2014-10-17
**/

// library list of LLVM
#include <llvm/IR/Module.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/JIT.h>

// library list of std
#include <iostream>
#include <vector>

using namespace llvm;

class  CodeBlock
{
    public:
    llvm::BasicBlock *block;
    std::map<std::string, llvm::Value*> block_map;
};

class  CodeGenerator{

       public:
       
       std::stack<*CodeBlock> block_stack;
       CodeGenerator()
       {
          this._globalContext = getGlobalContext();
          this._module = new Module("main", this._globalContext);
          
       }
   
       llvm::GenericValue runCode();
       void GenerateCode();

       BasicBlock* getCurrentBlock()
       {
          BasicBlock* blk = this.block_stack.top()->block;
          return blk;
       }
       std::map<std::string, llvm::Value*>& getBlkmap()
       {
          return this.block_Stack.top()->block_map;
       }
       private:
       llvm::Function* _mainFunc;
       llvm::Module*   _module;
       llvm::LLVMContext   _globalContext; 
       
       CodeBlock* popStack();
       void pushStack(CodeBlock* block); 

};


