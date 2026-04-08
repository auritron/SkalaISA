#pragma once

#include <vector>

#include "instructions.h"
#include "errorlist.h"
#include "parser.h"
#include "analyzer.h"
#include "codegen.h"

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
