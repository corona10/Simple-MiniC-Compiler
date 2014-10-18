#inlcude "CodeGenerator.hpp"

using namespace llvm;

GenericValue CodeGenerator::runCode()
{
    std::cout<<"Now.. Running Code"<<std::endl;
    ExistingModuleProvider *EMP = new ExistingModuleProvider(module);
    ExectionEngine *EE = ExectuionEngine::create(EMP, false);
    std::vector <GenericValue> gv_vec;
   
    GenericValue gv = EE->runFunction(mainFunc, gv_vec);

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
