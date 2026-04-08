#pragma once

namespace error {

    class Error {

        public:

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

    };

}