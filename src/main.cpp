#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "assembler/assembler.h"

int main(int argc, char* argv[]) {

    std::string filepath{"../progs/demo.asm"};
    std::ifstream asm_prog(filepath);
    
    if (asm_prog) {
        std::stringstream buffer;
        buffer << asm_prog.rdbuf();

        //instruction pipeline
        assembler_mod::Assembler assembler{};
        std::vector<instruction_mod::Inst> inst_pipeline{};
        assembler.assemble_prog(inst_pipeline, buffer.str());
        assembler.dbg_display_parse_tokens(inst_pipeline);
        
    } else {
        std::cout << "Error: File not found!" << std::endl;
    }

    return 0;
}