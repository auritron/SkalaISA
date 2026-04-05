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

        public:

            void analyze(const instruction_mod::Pipeline& pipeline) const;
            void raise_semantic_error(Error::SemanticError e);

    };

}