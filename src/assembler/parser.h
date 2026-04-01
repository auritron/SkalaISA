#pragma once

#include <cctype>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "instructions.h"
#include "errorlist.h"

namespace parser_mod { 

    enum class State {
        Idn,    //identifier mode, transition state, can be pushed as variable or opcode
        Rgt,    //register transition state (when 'R' is detected)
        Reg,    //register
        Sep,    //seperator (,)
        Imt,    //immediate transition state (when '#' is detected)
        Imm,    //immediate
        Lbt,    //label transition (when '@' is detected)
        Lbl,    //label
        Zer,    //zero prefix, transition state
        Adt,    //address transition ('x' in '0x')
        Adr,    //address (eg. 0xDEADBEEF)
        Cmt,    //comment (;)
        Nil,    //none (whitespace type char)
        Err,    //error/unknown state
    };

    enum class StateType {
        Word,
        RTransition, // special variation of transition since its alphanumeric
        Transition,
        Separator, // mostly redundant with StateType::None, helps with readability though
        None,
    };

    extern const std::unordered_map<State, StateType> state_map; //defined in parser.cpp

    enum class Action {
        Push,   //push character to buffer
        Emit,   //emit token in buffer
        Idle,   //do nothing
    };

    class Parser {
        
        private:
            State cur_state;
            State prev_state;
            Action cur_action;
            std::string buffer;
            instruction_mod::Inst cur_inst;
            unsigned char cur_ch;
            size_t ch_count;    //characters counted from input
            size_t line_count;
            size_t col_count;
            
        public:

            Parser();
            void tokenize(assembler_mod::Assembler::Pipeline& pipeline); //!
            void set_state(); //:D
            void set_action(); //:D
            void execute(assembler_mod::Assembler::Pipeline& pipeline); //:D
            void raise_parsing_error(Error::ParsingError e); //!

    };

}

