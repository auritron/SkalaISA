#include "analyzer.h"

using instruction_mod::OpCode;
using instruction_mod::TokenType;

namespace analyzer_mod {

    const ValidationMap validation_map {
        { OpCode::LOAD, {  } }
    };

}