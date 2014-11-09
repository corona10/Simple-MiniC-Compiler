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

class  CodeBlock
{
    public:
    llvm::BasicBlock *block;
    std::map<std::string, llvm::Value*> block_map; //used as Value Symbol Table
};

class  CodeGenerator{

       public:
       
       //생성자 
       CodeGenerator()
       {
         this->_module = new Module("test", getGlobalContext()); 
       }
       
       void generateIR();

       llvm::BasicBlock* getCurrentBlock()
       {
             return this->_block_stack.top()->block;
       }

       void pushBasicBlock(CodeBlock* block)
       {
             this->_block_stack.push(block);
       }

       private:
       llvm::Module*   _module;
       std::stack< CodeBlock   *> _block_stack;
       

};


