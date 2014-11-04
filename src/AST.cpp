#include "AST.hpp"

static Type* getTypeOf(std::string type)
{
   if(type == "int")
      return Type::getInt32Ty(getGlobalContext());
   else if (type == "float")
      return Type::getFloatTy(getGlobalContext());
   else if  (type == "double")
      return Type::getDoubleTy(getGlobalContext());
   else if  (type == "void")
      return Type::getVoidTy(getGlobalContext());

   return NULL;  
}
llvm::Value* CInt::codeGenerate(CodeGenerator& codegen)
{
     Type* type = getTypeOf("int");
      
     return ConstantInt::get(type, value, true);
}
