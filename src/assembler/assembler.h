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
            bool error_detected;

        public:
            using Pipeline = std::vector<instruction_mod::Inst>;
            Pipeline instruction_pipeline;

            Assembler();
            void assemble_prog(Pipeline& pipeline, const std::string& file);
            void dbg_display_parse_tokens(const Pipeline& pipeline);

    };

}
