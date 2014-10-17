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
class  CodeGenerator{
       public:
    
       CodeGenerator()
       {
          this._module = new Module("main", getGlobalContext());
       }
   
       GenericValue runCode();

       private:
       Function* _mainFunc;
       Module*   _module;

};


