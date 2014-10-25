#include "CodeGenerator.hpp"
#include "AST.hpp"

GenericValue CodeGenerator::runCode()
{
    std::cout<<"Now.. Running Code"<<std::endl;
    ExistingModuleProvider *EMP = new ExistingModuleProvider(module);
    ExectionEngine *EE = ExectuionEngine::create(EMP, false);
    std::vector <GenericValue> gv_vec;
   
    GenericValue gv = EE->runFunction(this._mainFunc, gv_vec);

    return gv;        

}

CodeBlock*  CodeGenerator::popStack()
{
  CodeBlock* value = null;
  if(!this.block_stack.empty())
  {

     value = this.block_stack.pop();
  }

  return value;

}

void CodeGenerator::pushStack(CodeBlock *block)
{
    this.block_stack.push(block);
}

void CodeGenerator::GenerateCode()
{
     std::cout<<"Now Generatring Code...."<<std::endl;
     std::vector<const llvm::Type* argType;
     FunctionType *ftype = FuntionType::get(Type::getInt32Ty(this._globalContext), argType, false);
     this._mainFunc = llvm::Function::Create(this._globalContext, "main", this._module);
     llvm::BasicBlock *BB = BasicBlock::Create(this._globalContext, "EntryBlock", this._mainFunc);

     this.pushStack(BB);
     this.popStack();

     std::cout<<"Code is generated!!!"<<std::endl;
     llvm::PassManager pm;
     pm.add(createPrintModulePass(&outs));
     pm.run(*(this._module));
}

/**
 get함수의 마지막 인자를 FALSE로 바꾸면 unsigned값을 반환한다.
**/
llvm::Value* CInteger::generateCode(CodeGenerator& codegen)
{
   std::cout<<"Genereate Integer: "<<this.value<<std::endl;
 
   return ConstantInt::get(Type::getInt32Ty(getGlobalContext()), this.value, true);
}

llvm::Value* CDouble::generateCode(CodeGenerator& codegen)
{
  std::cout<<"Generate Double: "<< this.value << std::endl;
  return ConstantFP::get(Type::getDoubleTy(getGlobalContext()), this.value, true);
}

llvm::Value* CFloat::generateCode(CodeGenerator& codegen)
{
    std::cout<<"Generate Float" << this.value <<std::endl;
    return ConstantFP::get(Type::getFloatTy(getGlobalContext(), this.value, true);
}

llvm::Value* CIdentifier::generateCode(CodeGenerator& codegen)
{
     std::cout<<"Create Identifier: "<< this.name <<std::endl;
}

llvm::Value* CBlock::generateCode(CodeGeneratr& codegen)
{
     std::cout<<"Generate Code Block.."<<std::endl;
     auto iter = this.statement_list.begin();
     
     while(iter != this.statement_list.end())
     {
           iter++;
     }
}
