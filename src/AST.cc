#include "AST.hpp"

static const Type* getTypeOf(CIdent& ident_type)
{
       /**
        ident가 데이터 타입형 일 때 맞는 Type값을 받기 위하 코드
       **/
       std::string type = ident_type.ident_name;
       if(type == "int")
           return Type::getInt32Ty(getGlobalContext();
       else if(type == "void")
           return Type::getVoidTy(getGlobalContext());
       else if(type == "float")
            return Type::getFloatTy(getGlobalContext());
       else if(type == "double")
            return Type::getDoubleTy(getGlobalContext());
       else 
            return NULL;

}

llvm::Value* CIdentifier::codeGenerate(CodeGenerator& codegen)
{
   llvm::Value* value = NULL;
   Type* type  = getTypeOf(this.type);
   

   value = new AllocaInst(type, var_id.c_str(), codegen.currentBlock());
   return value;
}
