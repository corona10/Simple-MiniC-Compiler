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
