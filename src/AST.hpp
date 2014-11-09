/**
 Implements of AST with LLVM
 @author : Dong-hee,Na
 @date   : 2014-10-12
**/

#include "llvm/IR/Constants.h"
#include <llvm/IR/Value.h>
#include <stack>
#include "CodeGenerator.hpp"
class CBaseAST
{
      public:
        virtual ~CBaseAST(){}
        virtual llvm::Value* codeGenerate(CodeGenerator& codegen) = 0;
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
