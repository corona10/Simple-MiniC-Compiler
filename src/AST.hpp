/**
 Implements of AST with LLVM
 @author : Dong-hee,Na
 @date   : 2014-10-12
**/
#include <llvm/Value.h>
#include <stack>

class CBaseAST
{
      public:
        virtual ~CBaseAST(){}
        virtual llvm::Value* codeGenerate(CodeGenerator& codegen) = 0;
};

typedef CBaseAST CExpression;
typedef CBaseAST CStatement;

class CInteger : public CBaseAST
{
      public:
        int value;
        CInteger(int val)
                 : value(val)
        {
        }
        virtual llvm::Value* codeGenerate(CodeGenerator& codegen);
};

class CDouble : public CBaseAST
{
      public:
       double value;
       CDouble(double val)
              : value(val)
       {
       }
       virtual llvm::Value* codeGenerate(CodeGenerator& codegen);
};

class CFloat : public CBaseAST
{
      public:
       float value;
       CFloat(val)
             :value(val)
       {
       }
       virtual llvm::Value* codeGenerate(CodeGenerator& codegen);
};

class CIdentifier : public CBaseAST
{
      public:
        std::string ident_name;
        CIdentifier(const std::string& name)
                   : ident_name(name)
        {
        }
        virtual llvm::Value* codeGenerate(CodeGenerator& codegen);
};

class CBlock : public CBaseAST
{
      public:
      std::vector<CStatement> statement_list;

      CBlock()
      {
      }
      virtual llvm::Value* codeGenerate(CodeGenerator& codegen);

};

class CFunctionCall : public CBaseAST
{
      public:
      const CIdentifier& id;
      virtual llvm::Value* codeGenerate(CodeGenerator& codegen);

};

class CFunctionDeclare : public CBaseAST
{
      public:
      virtual llvm::Value* codeGenertate(CodeGenerator& codegen);
};

class CIdentifier : public CBaseAST
{
      public:
      std::string name;
      Cidentfier(std::string _val)
                :name(_val)
      {
      } 

      virtual llvm::Value* codeGenerate(CodeGenerator& codegen);
};

class CVarDeclareration : public CBaseAST
{
      public:
      CIdentifier ident& type;
      CIdentifier ident& var_id;
     
      CVarDeclareration()
      {
      }
 
      virtual llvm::Value* codeGenerate(CodeGenerator& codegen);
}
