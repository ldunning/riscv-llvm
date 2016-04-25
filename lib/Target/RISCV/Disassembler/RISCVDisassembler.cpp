#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDisassembler.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;

namespace llvm {
    extern Target TheRISCVTarget;
    extern Target TheRISCV64Target;
}

class RISCVDisassembler : public MCDisassembler
{
    public:

    using MCDisassembler::MCDisassembler;

    MCDisassembler::DecodeStatus getInstruction( MCInst
            &Instr, uint64_t &Size, ArrayRef<uint8_t> Bytes, uint64_t Address,
            raw_ostream &VStream, raw_ostream &CStream) const {

        return Success;
    }
};

static MCDisassembler *createRISCVDisassembler(const Target &T,
                                             const MCSubtargetInfo &STI,
                                             MCContext &Ctx) {
  std::unique_ptr<const MCInstrInfo> MII(T.createMCInstrInfo());
  //return new RISCVDisassembler::RISCVDisassembler(STI, Ctx, std::move(MII));
  return new RISCVDisassembler::RISCVDisassembler(STI, Ctx);
}

extern "C" void LLVMInitializeRISCVDisassembler() {
  // Register the disassembler.
  TargetRegistry::RegisterMCDisassembler(TheRISCVTarget,
                                         createRISCVDisassembler);
  TargetRegistry::RegisterMCDisassembler(TheRISCV64Target,
                                         createRISCVDisassembler);
}
