#include "analyzer.h"

using instruction_mod::OpCode;
using TT = instruction_mod::TokenType;

namespace analyzer_mod {

    inline Opt OPT(TT t) { return instruction_mod::TokenOpt{t}; }
    inline Opt OPT(std::initializer_list<TT> ts) { return instruction_mod::TokenOpt{ts}; }

    inline Fmt DefineFmt(Opt a, Opt b, Opt c) {
        return Fmt{ a, b, c };
    }

    //destination is (almost) always first
    inline Fmt Null() { return DefineFmt( std::nullopt, std::nullopt, std::nullopt ); }
    inline Fmt Reg() { return DefineFmt( OPT(TT::Register), std::nullopt, std::nullopt ); }
    inline Fmt RegAdr() { return DefineFmt( OPT(TT::Register), OPT({TT::Address, TT::Variable}), std::nullopt ); }
    inline Fmt AdrReg() { return DefineFmt( OPT({TT::Address, TT::Variable}), OPT(TT::Register), std::nullopt ); }
    inline Fmt RegReg() { return DefineFmt( OPT(TT::Register), OPT(TT::Register), std::nullopt ); }
    inline Fmt RegImm() { return DefineFmt( OPT(TT::Register), OPT(TT::Immediate), std::nullopt ); }
    inline Fmt RegRgI() { return DefineFmt( OPT(TT::Register), OPT({TT::Register, TT::Immediate}), std::nullopt); }
    inline Fmt RgIRgI() { return DefineFmt( OPT({TT::Register, TT::Immediate}), OPT({TT::Register, TT::Immediate}), std::nullopt); }
    inline Fmt RegRegRgI() { return DefineFmt( OPT(TT::Register), OPT(TT::Register), OPT({TT::Register, TT::Immediate}) ); }
    inline Fmt RegRgIRgI() { return DefineFmt( OPT(TT::Register), OPT({TT::Register, TT::Immediate}), OPT({TT::Register, TT::Immediate}) ); }
    inline Fmt Lbl() { return DefineFmt( OPT(TT::Label), std::nullopt, std::nullopt); }

    inline const InstructionFmt instruction_fmt {

        //  memory and registers
        { OpCode::LOAD, RegAdr() },
        { OpCode::SEND, AdrReg() },
        { OpCode::COPY, RegReg() },
        { OpCode::SET,  RegImm() },

        //  bitwise
        { OpCode::NOT,  RegRgI() },
        { OpCode::AND,  RegRgIRgI() },
        { OpCode::OR,   RegRgIRgI() },
        { OpCode::XOR,  RegRgIRgI() },

        //  shift and rotation
        { OpCode::STL,  RegRegRgI() },
        { OpCode::STR,  RegRegRgI() },
        { OpCode::RTL,  RegRegRgI() },
        { OpCode::RTR,  RegRegRgI() },

        //  arithmetic
        { OpCode::NEG,  RegRgI() },
        { OpCode::ADD,  RegRgIRgI() },
        { OpCode::SUB,  RegRgIRgI() },
        { OpCode::MUL,  RegRgIRgI() },
        { OpCode::DIV,  RegRgIRgI() },
        { OpCode::MOD,  RegRgIRgI() },

        // comparison and branching
        { OpCode::CMP,  RgIRgI() },
        { OpCode::GOTO, Lbl() },
        { OpCode::WEQ,  Lbl() },
        { OpCode::WLT,  Lbl() },
        { OpCode::WGT,  Lbl() },
        { OpCode::WCY,  Lbl() },
        { OpCode::WOV,  Lbl() },
        { OpCode::WDZ,  Lbl() },

        //  stacks and sub-routines
        { OpCode::CAL,  Lbl() },
        { OpCode::RET,  Null() },
        { OpCode::PUSH, Reg() },
        { OpCode::POP,  Reg() },

        //  misc. and debugging
        { OpCode::END,  Null() },
        { OpCode::CLR,  Null() },

        // i/o (VM only)
        { OpCode::PRINT,  Reg() },
        { OpCode::PRINTC, Reg() },

    };

}