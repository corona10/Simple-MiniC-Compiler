#include "CodeGenerator.hpp"

void CodeGenerator::generateIR()
{
   llvm::LLVMContext & context = llvm::getGlobalContext();
   llvm::IRBuilder<> builder(context);
   this->_module->dump();
}

