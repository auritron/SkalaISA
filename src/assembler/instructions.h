#pragma once

#include <array>
#include <vector>
#include <unordered_map>
#include <string>
#include <string_view>
#include <optional>
#include <variant>

namespace instruction_mod {

    enum class TokenType {
        OpCode,
        Variable,
        Register,
        Immediate,
        Label,
        Address,
        Invalid, //debugging purposes
    };

    enum class OpCode {

        //  memory and registers
        LOAD,
        SEND,
        COPY,
        SET,
        SWAP,

        //  bitwise
        NOT,
        AND,
        OR,
        XOR,

        //  shift and rotation
        STL,
        STR,
        RTL,
        RTR,

        //  arithmetic
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        NEG,

        //  comparison and branching
        CMP,
        GOTO,
        WEQ,
        WGT,
        WLT,
        WCY,
        WOV,
        WDZ,

        //  stacks and sub-routines
        CAL,
        RET,
        PUSH,
        POP,

        //  i/o
        PRINT,
        PRINTC,

        //  misc. and debugging
        END,
        CLR,

    };

    // Opcode : number of args
    extern const std::unordered_map<std::string_view, OpCode> instruction_map; //defined in instruction.cpp

    class Token {

        public:

            TokenType token_type;

            using TokenDataType = std::variant<OpCode, int, std::string>;
            TokenDataType value;

            Token();
            Token(TokenType type, OpCode val);
            Token(TokenType type, int val);
            Token(TokenType type, std::string val);
            
    };

    class Inst {

        public:

            static constexpr int INST_SIZE = 4;
            size_t used_size;
            std::array<std::optional<Token>, INST_SIZE> token_arr;

            Inst();
            bool push_token(Token&& token);

    };

    using Pipeline = std::vector<Inst>;

}
