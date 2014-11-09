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

static llvm::FunctionType* getFuncTypeOf(std::string f_type)
{
       return llvm::FunctionType::get(getTypeOf(f_type), false); 
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
      AllocaInst* p_alloc = new AllocaInst(p_type, this->var_name.c_str(), codegen.getCurrentBlock());
 
      return NULL;
}

llvm::Value* CFunctionDefine::codeGenerate(CodeGenerator& codegen)
{
     llvm::FunctionType* p_ftype = getFuncTypeOf(this->type);
     llvm::Function* p_func = llvm::Function::Create(p_ftype, llvm::Function::ExternalLinkage, this->function_name, codegen.getModule());
     
     return p_func;
}

llvm::Value* CRootAST::codeGenerate(CodeGenerator& codegen)
{
      auto iter = AST_List.begin();
      while(iter != AST_List.end())
      {
          (*iter)->codeGenerate(codegen);
          iter++;

      }
}
