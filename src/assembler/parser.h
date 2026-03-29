#pragma once

#include <cctype>
#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <optional>
#include <unordered_map>
#include <stdexcept>
#include <variant>

#include "instructions.h"
#include "errorlist.h"

namespace Parser { 

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

    static const std::unordered_map<State, StateType> state_map {
        { State::Idn, StateType::Word },
        { State::Reg, StateType::Word },
        { State::Imm, StateType::Word },
        { State::Lbl, StateType::Word },
        { State::Adr, StateType::Word },
        { State::Rgt, StateType::RTransition },
        { State::Imt, StateType::Transition },
        { State::Lbt, StateType::Transition },
        { State::Adt, StateType::Transition },
        { State::Zer, StateType::Transition },
        { State::Sep, StateType::Separator },
        { State::Cmt, StateType::None },
        { State::Nil, StateType::None },
        { State::Err, StateType::None },
    };

    enum class Action {
        Push,   //push character to buffer
        Emit,   //emit token in buffer
        Idle,   //do nothing
    };

    class Token {

        public:

            Instruction::TokenType token_type;
            std::variant<Instruction::OpCode, int, std::string> value;

            Token();
            Token(Instruction::TokenType type, Instruction::OpCode val);
            Token(Instruction::TokenType type, int val);
            Token(Instruction::TokenType type, std::string val);
            
    };
    
    class UnvalInst {   //unvalidated parser generated instructions

        private:

            std::array<std::optional<Token>, 4> token_arr;
            size_t used_size;

        public:

            UnvalInst();
            bool push_token(Token token);

    };

    class Inst { //overhaul

        using TokenOpt = std::optional<Token>;

        private:

            Instruction::OpCode instruction;
            std::array<TokenOpt, 3> args;

        public:

            Inst(Instruction::OpCode i, TokenOpt t1 = std::nullopt, TokenOpt t2 = std::nullopt, TokenOpt t3 = std::nullopt);

    };

    class Tokenizer {
        
        private:
            State cur_state;
            State prev_state;
            Action cur_action;
            std::string buffer;
            UnvalInst cur_inst;
            unsigned char cur_ch;
            size_t ch_count;    //characters counted from input
            size_t line_count;
            size_t col_count;
            bool error_detected;
            
        public:

            std::vector<UnvalInst> pipeline;

            Tokenizer();
            void tokenize(); //!
            std::optional<Instruction::OpCode> match_token();
            void set_state(); //:D
            void set_action(); //:D
            void execute(); //!
            UnvalInst create_inst();
            void raise_parsing_error(Error::ParsingError e); //!

    };

}

