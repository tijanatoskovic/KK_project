#include "llvm/IR/PassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

namespace {

struct DeadCodeEliminationPass : public PassInfoMixin<DeadCodeEliminationPass> {
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
        bool changed = false;

        for (auto &BB : F) {
            for (auto it = BB.begin(); it != BB.end();) {
                Instruction *inst = &*it++;

                /* Preskacemo instrukcije koje:
                1. imaju upotrebu
                2. su terminatori (ret)
                3. imaju sporedne efekte */

                if (!inst->use_empty() || inst->isTerminator() || inst->mayHaveSideEffects())
                    continue;

                errs() << "Brisemo mrtvu instrukciju: " << *inst << "\n";
                inst->eraseFromParent();
                changed = true;
            }
        }

    return (changed ? PreservedAnalyses::none() : PreservedAnalyses::all());
};

}

} // namespace

llvm::PassPluginLibraryInfo getDeadCodeEliminationPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "dce-simple", LLVM_VERSION_STRING,
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "dce-simple") {
                        FPM.addPass(DeadCodeEliminationPass());
                        return true;
                    }
                    return false;
                });
        }
    };
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getDeadCodeEliminationPluginInfo();
}
