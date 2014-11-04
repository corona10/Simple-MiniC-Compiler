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

