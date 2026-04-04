#pragma once

#include <array>
#include <unordered_map>
#include <optional>

#include "instructions.h"
#include "errorlist.h"

namespace analyzer_mod {

    class TokenOpt {

        private:

            

    };

    using ValidationMap = std::unordered_map<instruction_mod::OpCode, std::array<std::optional<instruction_mod::TokenType>, instruction_mod::Inst::INST_SIZE - 1>>;
    extern const ValidationMap validation_map;

    class Analyzer {

        public:

            void analyze(const instruction_mod::Pipeline& pipeline);
            void raise_semantic_error(Error::SemanticError e);

    };

}