#pragma once
/**
 Implements of AST with LLVM
 @author : Dong-hee,Na
 @date   : 2014-10-12
**/

#include "llvm/IR/Constants.h"
#include "llvm/IR/Instruction.h"
#include <llvm/IR/Value.h>
#include <stack>
#include <vector>
#include "CodeGenerator.hpp"

class CBaseAST;
class CBlock;

class CBaseAST
{
      public:
        virtual ~CBaseAST(){}
        virtual llvm::Value* codeGenerate(CodeGenerator& codegen) = 0;
};

class CRootAST
{   
      public:
       std::vector<CBaseAST*> AST_List;
       CRootAST(){}
      
       virtual llvm::Value* codeGenerate(CodeGenerator& codegen);
      
};

class CInt : public CBaseAST // type 체크해서 적절한 value 생성하는 객체
{
      public:
        int  value;
        CInt(int val)
                 : value(val)
        {
        }
        ~CInt()
        {
        }        
        virtual llvm::Value* codeGenerate(CodeGenerator& codegen);
};

class CIdent : public CBaseAST
{
    public:
       std::string ident_name;
       CIdent(std::string name)
             : ident_name(name)
       {
       }

       virtual llvm::Value* codeGenerate(CodeGenerator& codegen);

};

class CVarDeclare : public CBaseAST
{
     public:
      std::string type;
      std::string var_name;
      std::string value;
    
      CVarDeclare(std::string ty, std::string v_name, std::string val)
                 : type(ty), var_name(v_name), value(val)
      {
      }
      CVarDeclare(std::string ty, std::string v_name)
                  : type(ty), var_name(v_name), value("0")
      {
      }
      virtual llvm::Value* codeGenerate(CodeGenerator& codegen);

};
class CValue : public CBaseAST
{
    public:
     std::string type;
     std::string value;

     CValue(std::string ty, std::string val)
           : type(ty), value(val)
     {
     }

     virtual llvm::Value* codeGenerate(CodeGenerator& codegen);

};

class CFunctionDefine : public CBaseAST
{
     public:
      std::string type;
      std::string function_name;
      std::vector<CVarDeclare*> para_var;
      std::vector<CBlock*> block_list;
      
      std::map<std::string, Value*> function_symbol_table;
      CFunctionDefine(std::string f_type, std::string f_name)
                        : type(f_type), function_name(f_name)
      {
          
      }

      CFunctionDefine(std::string f_type, std::string f_name, std::vector<CVarDeclare*> var_vec)
                        : type(f_type), function_name(f_name), para_var(var_vec)
      {

      }
     virtual llvm::Value* codeGenerate(CodeGenerator& codegen);

};

class CFunctionCall : public CBaseAST
{
      public:
      std::vector<CValue*> parameter_list;
      std::string function_name;

      CFunctionCall(std::string name)
                   : function_name(name)
      {

      }
     
      CFunctionCall(std::string name, std::vector<CValue*> para_list)
                   : function_name(name), parameter_list(para_list)
     {
     
     }
     
      virtual llvm::Value* codeGenerate(CodeGenerator& codegen);

};
class CBlock : public CBaseAST
{
      public:
      std::vector<CBaseAST*> instruction_list;
      std::string block_name;
      BasicBlock* basicblock;
      std::map<std::string, llvm::Value*> symbol_table;

      CBlock(std::string name)
            : block_name(name)
      {
           basicblock = BasicBlock::Create(getGlobalContext(), name); 
      }
      BasicBlock* getBasicBlock(){ return this->basicblock;}
      virtual llvm::Value* codeGenerate(CodeGenerator& codegen);

};

class CReturn : public CBaseAST
{
   public:
   int  mode;
   std::string value;

   CReturn(int md, std::string val)
          :mode(md), value(val)
   {
   }
   virtual llvm::Value* codeGenerate(CodeGenerator& codegen);

};
