#pragma once

#include <array>
#include <optional>
#include <expected>

#include "instructions.hpp"
#include "error.hpp"

namespace analyzer_mod {

    using SemErr = error::SemanticError;

    using Opt = std::optional<instruction_mod::TokenOpt>;
    using Fmt = std::array<Opt, instruction_mod::Inst::INST_SIZE - 1>; // 3 by default

    using InstructionFmt = std::unordered_map<instruction_mod::OpCode, Fmt>;
    extern const InstructionFmt instruction_fmt;    

    class Analyzer {

        private:
            bool error_detected;

        public:

            Analyzer(bool err_detected);
            std::expected<void, SemErr> validate_token(const instruction_mod::Token& inst) const;
            std::expected<void, SemErr> validate_opcode(const instruction_mod::Inst& inst, instruction_mod::OpCode opcode) const;
            std::expected<void, SemErr> analyze(const instruction_mod::Inst& inst) const;

    };

}