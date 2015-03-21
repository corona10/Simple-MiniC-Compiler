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
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include "CodeGenerator.hpp"
#include "AST.hpp"
void CodeGenerator::generateIR(CRootAST& root)
{
   llvm::LLVMContext & context = llvm::getGlobalContext();
   
   root.codeGenerate(*this);
   llvm::IRBuilder<> builder(context);
   std::vector<llvm::Type*> putsArgs;
   putsArgs.push_back(builder.getInt8Ty()->getPointerTo());
   llvm::ArrayRef<llvm::Type*>  argsRef(putsArgs);

   llvm::FunctionType *putsType = llvm::FunctionType::get(builder.getInt32Ty(), argsRef, false);
   llvm::Constant *putsFunc = this->_module->getOrInsertFunction("puts", putsType);
 
  // std::cout<<"Add Embaded functions for smcc.."<<std::endl;
   this->insertFunctionTable("puts", putsFunc);
   
   std::string ModuleId = this->_module->getModuleIdentifier();
   std::string ResultDir = "./result/";
   std::string BCfileName = ModuleId+".bc";

   const char* generateFile = (ResultDir+BCfileName).c_str();
   std::string ErrorInfo;
   std::auto_ptr<tool_output_file> Out(new tool_output_file(generateFile, ErrorInfo, llvm::sys::fs::OpenFlags::F_None));

   WriteBitcodeToFile(this->_module, Out->os());
   Out->keep(); 
   this->_module->dump();
   std::cout<<"Finish dump"<<std::endl;
   std::cout<<"This Compiler is based on LLVM 3.5"<<std::endl;
   delete this->_module;
}
