#pragma once

#include <vector>
#include <variant>
#include <concepts>
#include <string_view>

namespace error {

    enum class ParsingError {
        ImmediateValueError,
        IdentifierNamingError,
        LabelNamingError,
        AddressNamingError,
        UnknownCharError,
        RegisterOutOfRange,
        ImmediateValueTooBig,
        AddressOutOfRange,
        InstructionTooLong,
    };

    enum class SemanticError {
        MissingOpCodeError,
        IncorrectFirstToken,
        IncorrectOperandFmt,
    };

    template <typename T>
    concept Err = std::same_as<T, ParsingError> || std::same_as<T, SemanticError>;

    class Error {

        std::variant<ParsingError, SemanticError> error;

        public:

            Error() = delete;
            Error(Err auto error);
            std::string_view fmt_error_as_str();

    };

}