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
 
   std::cout<<"Add Embaded functions for smcc.."<<std::endl;
   this->insertFunctionTable("puts", putsFunc);
        
   std::string ErrorInfo;
   std::auto_ptr<tool_output_file> Out(new tool_output_file("./result/test.bc", ErrorInfo, llvm::sys::fs::OpenFlags::F_None));

   WriteBitcodeToFile(this->_module, Out->os());
   Out->keep(); 
   this->_module->dump();
   std::cout<<"Finish dump"<<std::endl;
   std::cout<<"This Compiler is based on LLVM 3.5"<<std::endl;
   delete this->_module;
}
