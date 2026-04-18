#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>

#include "assembler/assembler.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    fs::path source_dir = fs::path(__FILE__).parent_path();
    fs::path filepath = source_dir.parent_path() / "progs" / "demo.skasm";

    std::ifstream asm_prog(filepath);
    
    if (asm_prog) {
        std::cout << "File found: " << filepath.filename() << std::endl;

        std::stringstream buffer;
        buffer << asm_prog.rdbuf();

        assembler_mod::Assembler assembler{};
        std::vector<instruction_mod::Inst> inst_pipeline{};
        
        assembler.assemble_prog(inst_pipeline, buffer.str());
        assembler.dbg_display_tokens(inst_pipeline);
        
    } else {
        std::cout << "Error: File not found!" << std::endl;
        std::cout << "Path searched: " << fs::absolute(filepath) << std::endl;
    }

    std::cout << "Press any key to exit..." << std::endl;
    std::cin.get();

    return 0;
}