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

   return nullptr;  
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

     return nullptr;
}

llvm::Value* CVarDeclare::codeGenerate(CodeGenerator& codegen)
{
      //std::cout<<"* add instruction for variable declaration..  "<<std::endl;
      
      Type* p_type = getTypeOf(this->type);
      AllocaInst* p_alloc = new AllocaInst(p_type, this->var_name.c_str(), codegen.getCurrentBlock());

      Value* varValue = nullptr;
      int align_size = 0;
      if(this->type == "int")
      {
         align_size = 4;
         p_alloc->setAlignment(align_size);
         varValue = ConstantInt::get(p_type, stoi(value), true);
      }else if(this->type == "float")
      {
         align_size = 4;
         p_alloc->setAlignment(align_size);
         varValue = ConstantFP::get(p_type, stod(value));
      }
      else if(this->type == "double")
      {
         align_size = 8;
         p_alloc->setAlignment(align_size);
         varValue = ConstantFP::get(p_type, stod(value));
      }
         StoreInst* p_store = new StoreInst(varValue, p_alloc, false, codegen.getCurrentBlock());
         p_store->setAlignment(align_size);
      std::cout<<"Insert Value: "<<value<<std::endl;
      codegen.insertSymbol(var_name, varValue);             
     return p_alloc;
}

llvm::Value* CFunctionDefine::codeGenerate(CodeGenerator& codegen)
{
     llvm::FunctionType* p_ftype = getFuncTypeOf(this->type);
     llvm::Function* p_func = llvm::Function::Create(p_ftype, llvm::Function::ExternalLinkage, this->function_name, codegen.getModule());
     std::cout<<"* add instruction for function defination.. : "<< this->function_name <<std::endl;
     codegen.pushFunction(p_func); 
     if(this->block_list.size() > 0)
     {
        auto iter = this->block_list.begin();
        while(iter != this->block_list.end())
        {
             p_func->getBasicBlockList().push_back((*iter)->getBasicBlock()); 
             (*iter)->codeGenerate(codegen); 
             iter++;           
        }
        
     }
     codegen.insertFunctionTable(this->function_name, p_func);    
     return p_func;
}

llvm::Value* CRootAST::codeGenerate(CodeGenerator& codegen)
{
      auto iter = AST_List.begin();
      llvm::Value* p_value = nullptr;
      while(iter != AST_List.end())
      {
          std::cout<<"- generating code.."<<std::endl;
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
            while(iter != this->instruction_list.end())
            {
                p_value = (*iter)->codeGenerate(codegen);
                iter++;
            }
      }
      
      return p_value;
}

llvm::Value* CReturn::codeGenerate(CodeGenerator& codegen)
{
   Type* type = codegen.getCurrentFunction()->getReturnType();
   Value* p_val = nullptr;
   if(this->mode == 0)
   {
      if(type->isIntegerTy())
        p_val = ConstantInt::get(type, stoi(value), true);
      else if(type->isFloatTy() || type->isDoubleTy())
        p_val = ConstantFP::get(type, stod(value));

      return llvm::ReturnInst::Create(getGlobalContext(), p_val, codegen.getCurrentBlock());
   }else if(this->mode == 1)
   {
     std::cout<<"find for ident: "<<value<<std::endl;
     p_val = codegen.getSymbolValue(value);
     //llvm::LoadInst* p_load = new llvm::LoadInst(p_val, "", false, codegen.getCurrentBlock());
     return llvm::ReturnInst::Create(getGlobalContext(), p_val, codegen.getCurrentBlock());
   }

   return nullptr;
}

llvm::Value* CFunctionCall::codeGenerate(CodeGenerator& codegen)
{
      /**
      std::vector<llvm::Type* > putsArgs;
      llvm::ArraryRef<llvm::Type*> argRef(putsArgs);
      **/
      return nullptr;
}
