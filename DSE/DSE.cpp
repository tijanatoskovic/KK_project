#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include <unordered_set>
#include <vector>
#include <unordered_map>

using namespace llvm;

namespace {

struct DSE : public FunctionPass {
    static char ID;
    DSE() : FunctionPass(ID) {}

    std::unordered_map<Value*, Value*> VariablesMap;

    //pamtimo promenljive koje se ucitavaju iz mem
    void mapVariables(Function &F) {
        for (auto &BB : F) {
            for (auto &I : BB) {
                if (isa<LoadInst>(&I)) {
                    VariablesMap[&I] = I.getOperand(0);
                }
            }
        }
    }

    bool eliminateDeadStores(Function &F) {
        std::vector<Instruction*> ToRemove;
        std::unordered_set<Value*> DeadVars;

        for (auto BlockIt = F.end(); BlockIt != F.begin();) {
            --BlockIt;
            BasicBlock &BB = *BlockIt;
            for (auto InstIt = BB.rbegin(); InstIt != BB.rend(); ++InstIt) {
                Instruction &I = *InstIt;

                //naidjemo na load instr - preskacemo (nije mrtva jer koristi podatke iz mem)
                if (isa<LoadInst>(&I))
                    continue;

                //ako je store instr
                if (auto *Store = dyn_cast<StoreInst>(&I)) {
                    Value *Ptr = Store->getPointerOperand();
                    if (DeadVars.count(Ptr)) {  //ako je vec u DeadVars znaci da cemo je kasnije pregaziti, pa je ovo dead store
                        ToRemove.push_back(&I);
                    }
                    DeadVars.insert(Ptr);
                } else {
                    for (unsigned i = 0; i < I.getNumOperands(); ++i) {
                        Value *Op = I.getOperand(i);
                        if (VariablesMap.count(Op)) {
                            DeadVars.erase(VariablesMap[Op]);   //vise nije mrtva ako smo je sad procitali
                        }
                    }
                }
            }
        }

        bool Changed = !ToRemove.empty();
        for (Instruction *I : ToRemove) {
            errs() << "Removing dead store: " << *I << "\n";
            I->eraseFromParent();
        }
        return Changed;
    }

    bool runOnFunction(Function &F) override {
        mapVariables(F);
        return eliminateDeadStores(F);
    }
};

} // namespace

char DSE::ID = 0;
static RegisterPass<DSE> X("simple-dse-pass", "A simple Dead Store Elimination pass");