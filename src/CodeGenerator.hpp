/**
The MIT License (MIT)



Copyright (c) 2014-2015 Dong-hee,Na



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions:



The above copyright notice and this permission notice shall be included in

all copies or substantial portions of the Software.



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN

THE SOFTWARE
**/
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
#include <map>


using namespace llvm;

class CRootAST;
class  CodeGenerator{

       public:
       
       //생성자 
       CodeGenerator()
       {
         this->_module = new Module("test", getGlobalContext());
         //this->_module->setTargetTriple("x86_64-pc-linux-gnu"); 
       }

       CodeGenerator(std::string module_name)
       {
         this->_module = new Module(module_name.c_str(), getGlobalContext());
       }
      
       void generateIR(CRootAST& root);
       void pushBlock(llvm::BasicBlock* blk)
       {
            block_stack.push(blk);
       }

       void pushFunction(llvm::Function* func)
       {
             
             function_stack.push(func);
             //std::cout<<"InsertFunction..: "<<function_stack.size()<<std::endl;
       }

       void insertSymbol(std::string key, Value* val)
       {
             this->GLsymbol_table[key] = val;
       }
       
        void insertFunctionTable(std::string key, Value* val)
       {
             this->GLfunction_table[key] = val;
       }
       llvm::BasicBlock* getCurrentBlock()
       {
            return block_stack.top();
       }

       llvm::Function* getCurrentFunction()
       {
             Function* p_func = function_stack.top();
             //function_stack.pop();
             return p_func;
       }
       
       llvm::Value* getSymbolValue(std::string key)
       {
             return this->GLsymbol_table[key];
       }

       llvm::Value* getFunctionValue(std::string key)
       {
             return this->GLfunction_table[key];
       }
       llvm::Module* getModule(){return this->_module;}
       private:

       llvm::Module*   _module;
       std::stack<BasicBlock*> block_stack;
       std::stack<Function*> function_stack;
       
       std::map<std::string, llvm::Value*> GLfunction_table;
       std::map<std::string, llvm::Value*> GLsymbol_table;  
       //std::stack<CFunctionDefine*> function_stack;
};


