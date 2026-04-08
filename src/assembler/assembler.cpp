#include <iostream>
#include <magic_enum/magic_enum.hpp>

#include "assembler.h"
#include "../overload.hpp"

using namespace assembler_mod;

Assembler::Assembler() :
    instruction_pipeline{},
    error_detected{false},
    error_log{}
{ }

void Assembler::assemble_prog(instruction_mod::Pipeline& pipeline, const std::string& file) {
    auto parser = parser_mod::Parser();
    for (int pos{0}; pos < file.size(); pos++) {
        parser.tokenize(pipeline, file[pos], error_log);
        //debugging purpose only
        /*std::cout << magic_enum::enum_name(parser.cur_state) 
        << ", Ln: " << parser.line_count 
        << ", Cm: " << parser.col_count << std::endl;*/
    }
    parser.tokenize(pipeline, '\n', error_log); //add \n sentinel

    if (!pipeline.empty()) {
        auto analyzer = analyzer_mod::Analyzer(false);
        for (int inst_no{0}; inst_no < pipeline.size(); inst_no++) {
            analyzer.analyze(pipeline[inst_no]);
        }
    }
}

void Assembler::dbg_display_parse_tokens(const instruction_mod::Pipeline& pipeline) const {

    for (int i{0}; i < pipeline.size(); i++) {
        std::cout << "Instruction No. " << i + 1 << ": ";
        const auto& cur_inst{pipeline[i]};
        for (int j{0}; j < cur_inst.INST_SIZE; j++) {
            const auto& cur_token{cur_inst.token_arr[j]};
            if (cur_token.has_value()) {
                std::cout << magic_enum::enum_name(cur_token->token_type) << " : ";
                std::visit(overload {
                    [](instruction_mod::OpCode oc) { std::cout << magic_enum::enum_name(oc); }, //for opcode
                    [](auto a) { std::cout << a ;}, //for int and double
                }, cur_token->value);
            } else {
                std::cout << "No Token";
            }
            std::cout << " , ";
        }
        std::cout << '\n';
    }

}