#pragma once

namespace Error {

    enum class ParsingError {
        ImmediateValueError,
        IdentifierNamingError,
        LabelNamingError,
        AddressNamingError,
        UnknownCharError,
        RegisterOutOfRange,
        ImmediateValueTooBig,
        AddressOutOfRange,
    };

}