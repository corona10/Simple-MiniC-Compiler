/**
 Implements of AST with LLVM
 @author : Dong-hee,Na
 @date   : 2014-10-12
**/
#include <llvm/Value.h>

class CBaseAST
{
      public:
        virtual ~CBaseAST(){}
        virtual llvm::Value* codeGen(CodeGenContext& context){}
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
        virtual llvm::Value* codeGen(CodeGenContext& context);
};

class CDouble     : public CBaseAST
{
      public:
       double value;
       CDouble(double val)
              : value(val)
       {
       }
       virtual llvm::Value* codeGen(CodeGenContext& context);
};

class CFloat      : public CBaseAST
{
      public:
       float value;
       CFloat(val)
             :value(val)
       {
       }
       virtual llvm::Value* codeGen(CodeGenContext& context);
};
