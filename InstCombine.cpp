#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/PatternMatch.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;
using namespace llvm::PatternMatch;

namespace {

class InstCombineSimplePass : public PassInfoMixin<InstCombineSimplePass> {
public:
    PreservedAnalyses run(Function &function, FunctionAnalysisManager &) {
        bool changed = false;

        for (auto &block : function) {
            for (auto it = block.begin(); it != block.end();) {
                Instruction *inst = &*it++;
                
                // ako je sabiranje, probamo da preuredimo konstante
                if (auto *addInst = dyn_cast<BinaryOperator>(inst)) {
                    if (addInst->getOpcode() == Instruction::Add) {
                        if (isa<ConstantInt>(addInst->getOperand(0)) &&
                            !isa<ConstantInt>(addInst->getOperand(1))) {
                            addInst->swapOperands();
                            changed = true;
                        }
                    }
                }

                // kombinovanje izraza: (x + c1) + c2 => x + (c1 + c2)
                Value *x;
                ConstantInt *c1, *c2;
                if (match(inst, m_Add(m_Add(m_Value(x), m_ConstantInt(c1)), m_ConstantInt(c2)))) {
                    auto *combinedConst = ConstantInt::get(c1->getType(),
                                                           c1->getSExtValue() + c2->getSExtValue());
                    auto *newAdd = BinaryOperator::CreateAdd(x, combinedConst);
                    newAdd->insertAfter(inst);
                    inst->replaceAllUsesWith(newAdd);
                    inst->eraseFromParent();
                    changed = true;
                    continue;
                }

                // pretvaranje x * 2 u x << 1 (umesto mnozenja koristimo shiftovanje)
                if (match(inst, m_Mul(m_Value(x), m_ConstantInt(c1))) && c1->equalsInt(2)) {
                    auto *shiftLeft = BinaryOperator::CreateShl(
                        x, ConstantInt::get(c1->getType(), 1));

                    shiftLeft->insertAfter(inst);
                    inst->replaceAllUsesWith(shiftLeft);
                    inst->eraseFromParent();
                    changed = true;
                    continue;
                }
            }
        }

        return changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
    }
};

} // namespace


llvm::PassPluginLibraryInfo getInstCombineSimplePluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "instcombine-simple", LLVM_VERSION_STRING,
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (name == "instcombine-simple") {
                        FPM.addPass(InstCombineSimplePass());
                        return true;
                    }
                    return false;
                });
        }
    };
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getInstCombineSimplePluginInfo();
}
