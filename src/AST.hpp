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
        virtual llvm::Value* codeGenerate(CodeContext& context){}
};

class CExpression : public CBaseAST
{
};

class CStatement  : public CBaseAST
{
};

class CInteger    : public CBaseAST
{
      public:
        size_t value;
        CInteger(size_t val)
                 : value(val)
        {
        }
        virtual llvm::Value* codeGenerate(CodeContext& context);
};

class CDouble     : public CBaseAST
{
      public:
       double value;
       CDouble(double val)
              : value(val)
       {
       }
       virtual llvm::Value* codeGenerate(CodeContext& context);
};

class CFloat      : public CBaseAST
{
      public:
       float value;
       CFloat(val)
             :value(val)
       {
       }
       virtual llvm::Value* codeGenerate(CodeContext& context);
};

class CIdentifier : public CBaseAST
{
      public:
        std::string ident_name;
        CIdentifier(const std::string& name)
                   : iden_name(name)
        {
        }
        virtual llvm::Value* codeGenerate(CodeContext& context);
};
