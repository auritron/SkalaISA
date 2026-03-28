#pragma once

#include <unordered_map>
#include <string_view>

namespace Instruction {

    enum class TokenType {
        OpCode,
        Variable,
        Register,
        Immediate,
        Label,
        Address,
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
    static const std::unordered_map<std::string_view, OpCode> instruction_map {
        { "LOAD",   OpCode::LOAD },
        { "SEND",   OpCode::SEND },
        { "COPY",   OpCode::COPY },
        { "SET",    OpCode::SET },
        { "SWAP",   OpCode::SWAP },
        { "NOT",    OpCode::NOT },
        { "AND",    OpCode::AND },
        { "OR",     OpCode::OR },
        { "XOR",    OpCode::XOR },
        { "STL",    OpCode::STL },
        { "STR",    OpCode::STR },
        { "RTL",    OpCode::RTL },
        { "RTR",    OpCode::RTR },
        { "ADD",    OpCode::ADD },
        { "SUB",    OpCode::SUB },
        { "MUL",    OpCode::MUL },
        { "DIV",    OpCode::DIV },
        { "MOD",    OpCode::MOD },
        { "NEG",    OpCode::NEG },
        { "CMP",    OpCode::CMP },
        { "GOTO",   OpCode::GOTO },
        { "WEQ",    OpCode::WEQ },
        { "WGT",    OpCode::WGT },
        { "WLT",    OpCode::WLT },
        { "WCY",    OpCode::WCY },
        { "WOV",    OpCode::WOV },
        { "WDZ",    OpCode::WDZ },
        { "CAL",    OpCode::CAL },
        { "RET",    OpCode::RET },
        { "PUSH",   OpCode::PUSH },
        { "POP",    OpCode::POP },
        { "PRINT",  OpCode::PRINT },
        { "PRINTC", OpCode::PRINTC },
        { "END",    OpCode::END },
        { "CLR",    OpCode::CLR },
    };

}
