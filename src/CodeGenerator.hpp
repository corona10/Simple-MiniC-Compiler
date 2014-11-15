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
            block_stack.push(blk);
       }

       llvm::BasicBlock* getCurrentBlock()
       {
            return block_stack.top();
       }

       llvm::Module* getModule(){return this->_module;}
       private:
       llvm::Module*   _module;
       std::stack<BasicBlock*> block_stack;
       

};


