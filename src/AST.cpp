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

llvm::Value* CIdent::codeGenerate(CodeGenerator& codegen)
{

     return NULL;
}

llvm::Value* CVarDeclare::codeGenerate(CodeGenerator& codegen)
{
      Type* p_type = getTypeOf(this->type);
     // AllocaInst* p_alloc = new AllocaInst(p_type, this.var_name.c_str(), codegen.getCurrentBlock());

 
      return NULL;
}
