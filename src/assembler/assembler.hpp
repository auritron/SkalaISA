#pragma once

#include <vector>

#include "instructions.hpp"
#include "errorlist.hpp"
#include "parser.hpp"
#include "analyzer.hpp"
#include "codegen.hpp"

namespace assembler_mod {

    class Assembler {

        private:
            std::vector<error::Error> error_log;
            bool error_detected;

        public:
            instruction_mod::Pipeline instruction_pipeline;

            Assembler();
            void assemble_prog(instruction_mod::Pipeline& pipeline, const std::string& file);
            void dbg_display_parse_tokens(const instruction_mod::Pipeline& pipeline) const;

    };

}
