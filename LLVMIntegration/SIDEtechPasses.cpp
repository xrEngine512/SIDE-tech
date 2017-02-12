//
// Created by islam on 11.02.17.
//

#include <llvm/IR/Instructions.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>

using namespace llvm;
using namespace legacy;

namespace {
    struct SIDEtechFunctionPass : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid

        SIDEtechFunctionPass() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            auto& M = *F.getParent();
            auto& C = F.getContext();

            // types used
            auto char_ty = Type::getInt8PtrTy(C);

            auto hook_function = cast<Function>(M.getOrInsertFunction(
                    "on_function_call",     // function name
                    Type::getVoidTy(C),     // return type
                    char_ty,  // argument type
                    NULL      // <-- this is important!
            ));
            auto& instruction_list = F.getBasicBlockList().begin()->getInstList();

            // Constants
            auto constant = ConstantDataArray::getString(C, F.getName());

            // Instructions to be added
            auto ptr_constant = new AllocaInst(Type::getInt8Ty(C), ConstantInt::get(Type::getInt32Ty(C), F.getName().size() + 1));
            auto store = new StoreInst(constant, ptr_constant);
            auto function_call = CallInst::Create(hook_function, {ptr_constant});

            // Insertion of instructions (reversed order in fact)
            auto i = instruction_list.insert(instruction_list.begin(), function_call);
            i = instruction_list.insert(i, store);
            instruction_list.insert(i, ptr_constant);

            return true;
        }

        const char *getPassName() const override {
            return "SIDEtechFunctionPass";
        }
    };
}

char SIDEtechFunctionPass::ID = 0;

static void registerPass(const PassManagerBuilder &, PassManagerBase &PM) {
    PM.add(new SIDEtechFunctionPass());
}
static RegisterStandardPasses RegisterPass(PassManagerBuilder::EP_EarlyAsPossible, registerPass);
