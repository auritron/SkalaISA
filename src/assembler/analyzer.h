#pragma once

#include <array>
#include <optional>

#include "instructions.h"
#include "errorlist.h"

namespace analyzer_mod {

    using Opt = std::optional<instruction_mod::TokenOpt>;
    using Fmt = std::array<Opt, instruction_mod::Inst::INST_SIZE - 1>; // 3 by default

    using InstructionFmt = std::unordered_map<instruction_mod::OpCode, Fmt>;
    extern const InstructionFmt instruction_fmt;    

    class Analyzer {

        private:
            bool error_detected;

        public:

            Analyzer(bool err_detected);
            bool validate_opcode(const instruction_mod::Inst& inst, instruction_mod::OpCode opcode) const;
            bool analyze(const instruction_mod::Inst& inst) const;
            void raise_semantic_error(error::Error::SemanticError e) const; 

    };

}