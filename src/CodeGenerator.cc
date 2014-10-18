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

     FunctionType *ftype = FuntionType::get(Type::getInt32Ty
     this._mainFunc = llvm::Function::Create(this._globalContext, "main", this._module);
     BasicBlock *BB = BasicBlock::Create(this._globalContext, "EntryBlock", this._mainFunc);

}
