#pragma once
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
#include <llvm/IR/IRBuilder.h>
// library list of std
#include <iostream>
#include <vector>
#include <stack>


using namespace llvm;

class CRootAST;
class  CodeGenerator{

       public:
       
       //생성자 
       CodeGenerator()
       {
         this->_module = new Module("test", getGlobalContext());
         this->_module->setTargetTriple("x86_64-pc-linux-gnu"); 
       }
       
       void generateIR(CRootAST& root);
       void pushBlock(llvm::BasicBlock* blk)
       {
            std::cout<<"Push Block..."<<std::endl;
            block_stack.push(blk);
       }
       void pushFunction(llvm::Function* func)
       {
             std::cout<<"Function Stack Size: "<<function_stack.size()<<std::endl;
             function_stack.push(func);
       }
       llvm::BasicBlock* getCurrentBlock()
       {
            return block_stack.top();
       }
       llvm::Function* getCurrentFunction()
       {
             std::cout<<"pop function_stack.."<<std::endl;
             Function* p_func = function_stack.top();
             function_stack.pop();
             return p_func;
       }
       llvm::Module* getModule(){return this->_module;}
       private:
       llvm::Module*   _module;

       std::stack<BasicBlock*> block_stack;
       std::stack<Function*> function_stack;  
       

};


