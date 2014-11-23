#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/Support/raw_ostream.h"

#include "CodeGenerator.hpp"
#include "AST.hpp"
void CodeGenerator::generateIR(CRootAST& root)
{
   llvm::LLVMContext & context = llvm::getGlobalContext();
   llvm::IRBuilder<> builder(context);
   root.codeGenerate(*this);
   std::vector<llvm::Type*> putsArgs;
   putsArgs.push_back(builder.getInt8Ty()->getPointerTo());
   llvm::ArrayRef<llvm::Type*>  argsRef(putsArgs);

   llvm::FunctionType *putsType =
   llvm::FunctionType::get(builder.getInt32Ty(), argsRef, false);
   llvm::Constant *putsFunc = this->_module->getOrInsertFunction("puts", putsType);
   
   std::string ErrorInfo;
   OwningPtr<tool_output_file> Out(new tool_output_file("./test.bc", ErrorInfo, sys::fs::F_None));

   WriteBitcodeToFile(this->_module, Out->os());
   Out->keep(); 
   this->_module->dump();
   std::cout<<"Finish dump"<<std::endl;
}
