#include "analyzer.h"
#include "../overload.hpp"

using instruction_mod::OpCode;
using TT = instruction_mod::TokenType;
using SemErr = error::Error::SemanticError;

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

    Analyzer::Analyzer(bool err_detected) :
        error_detected{err_detected}
    { }

    bool Analyzer::validate_opcode(const instruction_mod::Inst& inst, instruction_mod::OpCode opcode) const {

        const auto opc_pattern = instruction_fmt.find(opcode);
        if (opc_pattern == instruction_fmt.end()) {
            std::abort(); //change this to a panic function with error message.
        } else { 
            for (int tkn{1}; tkn < instruction_mod::Inst::INST_SIZE; tkn++) {
                const auto& cur_token = inst.token_arr[tkn];
                const auto& cur_target = (opc_pattern->second)[tkn-1];
                if (cur_token.has_value() == cur_target.has_value()) {
                    if (cur_token.has_value() && !cur_target.value().token_type_exists(cur_token->token_type)) {
                        raise_semantic_error(SemErr::IncorrectOperandFmt);
                        return false;
                    }
                } else {
                    raise_semantic_error(SemErr::IncorrectOperandFmt);
                    return false;
                }
            }
        }
        return true;
        
    }

    bool Analyzer::analyze(const instruction_mod::Inst& inst) const {
        const auto& first_token = inst.token_arr[0];
        if (!first_token.has_value()) { //check if first token exists, should not happen ideally but still
            raise_semantic_error(SemErr::MissingOpCodeError);
        } else {
            switch(first_token->token_type) {
                case TT::OpCode: {
                    bool is_matched = std::visit(overload{
                        [this, inst](instruction_mod::OpCode oc) -> bool {
                            if (!validate_opcode(inst, oc)) return false;
                            return true;
                        },
                        [](auto a) { std::abort(); return false; }, //shouldn't happen
                    }, first_token->value);
                    if (!is_matched) return false;
                    break;
                }
                case TT::Label:
                    //label validation
                    break;
                default:
                    raise_semantic_error(SemErr::IncorrectFirstToken);
                    break;
            }
        }

        return true;
    };

    void Analyzer::raise_semantic_error(SemErr e) const {

    };

}