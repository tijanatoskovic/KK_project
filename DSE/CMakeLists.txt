add_llvm_library(LLVMDeadStoreElim MODULE
        DSE.cpp
        DEPENDS
        intrinsics_gen
        PLUGIN_TOOL
        opt
)