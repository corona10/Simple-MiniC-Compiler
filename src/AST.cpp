#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "parser.hpp"
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
      std::cout<<"Code generate for Var decalre "<<std::endl;
      
      Type* p_type = getTypeOf(this->type);
      AllocaInst* p_alloc = new AllocaInst(p_type, this->var_name.c_str(), codegen.getCurrentBlock());
 
     return p_alloc;
}

llvm::Value* CFunctionDefine::codeGenerate(CodeGenerator& codegen)
{
     llvm::FunctionType* p_ftype = getFuncTypeOf(this->type);
     llvm::Function* p_func = llvm::Function::Create(p_ftype, llvm::Function::ExternalLinkage, this->function_name, codegen.getModule());
     std::cout<<"Function Define.. for "<< this->function_name <<std::endl;
   
     if(this->block_list.size() > 0)
     {
        std::cout<<"add block for entry of "<<function_name<<std::endl;
        
        auto iter = this->block_list.begin();
        while(iter != this->block_list.end())
        {
             std::cout<<"block insert.."<<std::endl; 
             p_func->getBasicBlockList().push_back((*iter)->getBasicBlock()); 
             (*iter)->codeGenerate(codegen); 
             iter++;           
        }
        
     }     
     return p_func;
}

llvm::Value* CRootAST::codeGenerate(CodeGenerator& codegen)
{
      auto iter = AST_List.begin();
      llvm::Value* p_value = nullptr;
      while(iter != AST_List.end())
      {
          std::cout<<"generate code.."<<std::endl;
          p_value = (*iter)->codeGenerate(codegen);
          iter++;
          
      }

     return p_value;
}

llvm::Value* CBlock::codeGenerate(CodeGenerator& codegen)
{
      llvm::Value* p_value = nullptr;
      codegen.pushBlock(this->basicblock);
      if(this->instruction_list.size()>0)
      {
            
            auto iter = this->instruction_list.begin();
            std::cout<<this->instruction_list.size()<<std::endl;
            while(iter != this->instruction_list.end())
            {
                std::cout<<"Has Instruction " <<std::endl;
                p_value = (*iter)->codeGenerate(codegen);
                iter++;
            }
      }
      
      return p_value;
}
