#include "parser.h"
#include "errorlist.h"

using namespace Parser;

using ParseErr = Error::ParsingError;

Token::Token(Instruction::TokenType type, Instruction::OpCode val) :
    token_type{type}, value{val} { }
Token::Token(Instruction::TokenType type, int val) :
    token_type{type}, value{val} { }
Token::Token(Instruction::TokenType type, std::string val) :
    token_type{type}, value{val} { }

Inst::Inst(Instruction::OpCode i, TokenOpt t1, TokenOpt t2, TokenOpt t3 ) : //overhaul
    instruction{i}, 
    args{t1, t2, t3} 
{ }

UnvalInst::UnvalInst() :
    token_arr{std::nullopt},
    used_size{0}
{ }

Tokenizer::Tokenizer() :
    cur_state{State::Nil},
    prev_state{State::Nil},
    cur_action{Action::Idle},
    buffer{""},
    cur_inst(),
    cur_ch{0},
    ch_count{0},
    line_count{0},
    col_count{0},
    error_detected{false},
    pipeline{}
{ }

void Tokenizer::set_state() {

    if (cur_ch == '\n') {

        cur_state = State::Nil;

    } else if (cur_state != State::Cmt && cur_state != State::Err) {

        if (cur_ch == ';') {

            cur_state = State::Cmt;
            
        } else if (cur_state == State::Zer && cur_ch == 'x') { //0x detection

            cur_state = State::Adt;

        } else if (std::isspace(cur_ch)) { //simple state machine lmao

            switch (cur_state) {
                case State::Idn:
                case State::Reg:
                case State::Rgt: // despite being a transition state, this is allowed since R is alphanumeric
                case State::Sep:
                case State::Imm:
                case State::Lbl:
                case State::Adr:
                case State::Nil:
                    cur_state = State::Nil;
                    break;
                case State::Imt:
                case State::Zer:
                    raise_parsing_error(ParseErr::ImmediateValueError);
                    break;
                case State::Lbt:
                    raise_parsing_error(ParseErr::LabelNamingError);
                    break;
                case State::Adt:
                    raise_parsing_error(ParseErr::AddressNamingError);
                    break;
                case State::Err:
                    break;
                case State::Cmt:
                    std::abort();

            }

        } else if (cur_ch == 'R') {

            switch (cur_state) {
                case State::Nil:
                case State::Sep:
                    cur_state = State::Rgt;
                    break;
                case State::Rgt:
                case State::Reg:
                    cur_state = State::Idn;
                    break;
                case State::Adt:
                case State::Adr:
                    raise_parsing_error(ParseErr::AddressNamingError);
                    break;
                case State::Imt:
                case State::Imm:
                    raise_parsing_error(ParseErr::ImmediateValueError);
                    break;
                case State::Zer:
                    raise_parsing_error(ParseErr::IdentifierNamingError);
                    break;
                case State::Err:
                    break;
                case State::Cmt:
                    std::abort();
                default:
                    break;
            }

        } else if (cur_ch == '@') {
            
            switch (cur_state) {
                case State::Idn:
                case State::Rgt:
                case State::Reg:
                case State::Zer:
                    raise_parsing_error(ParseErr::IdentifierNamingError);
                    break;
                case State::Imt:
                case State::Imm:
                    raise_parsing_error(ParseErr::ImmediateValueError);
                    break;
                case State::Lbl:
                case State::Lbt:
                    raise_parsing_error(ParseErr::LabelNamingError);
                    break;
                case State::Adt:
                case State::Adr:
                    raise_parsing_error(ParseErr::AddressNamingError);
                    break;
                case State::Sep:
                case State::Nil:
                    cur_state = State::Lbt;
                    break;
                case State::Err:
                    break;
                case State::Cmt:
                    std::abort();
            }

        } else if (cur_ch == '#') {

            switch (cur_state) {
                case State::Idn:
                case State::Rgt:
                case State::Reg:
                case State::Zer:
                    raise_parsing_error(ParseErr::IdentifierNamingError);
                    break;
                case State::Imt:
                case State::Imm:
                    raise_parsing_error(ParseErr::ImmediateValueError);
                    break;
                case State::Lbl:
                case State::Lbt:
                    raise_parsing_error(ParseErr::LabelNamingError);
                    break;
                case State::Adt:
                case State::Adr:
                    raise_parsing_error(ParseErr::AddressNamingError);
                    break;
                case State::Sep:
                case State::Nil:
                    cur_state = State::Imt;
                    break;
                case State::Err:
                    break;
                case State::Cmt:
                    std::abort();
            }

        } else if (cur_ch == '_') {

            switch (cur_state) {
                case State::Idn:
                case State::Rgt:
                case State::Reg:
                case State::Sep:
                case State::Nil:
                    cur_state = State::Idn;
                    break;
                case State::Zer:
                    raise_parsing_error(ParseErr::IdentifierNamingError);
                    break;
                case State::Imt:
                case State::Imm:
                    raise_parsing_error(ParseErr::ImmediateValueError);
                    break;
                case State::Lbl:
                case State::Lbt:
                    cur_state = State::Lbl;
                    break;
                case State::Adt:
                case State::Adr:
                    raise_parsing_error(ParseErr::AddressNamingError);
                    break;
                case State::Err:
                    break;
                case State::Cmt:
                    std::abort();
            }
            
        } else if (std::isdigit(cur_ch)) {

            switch (cur_state) {
                case State::Idn:
                    cur_state = State::Idn;
                    break;
                case State::Rgt:
                case State::Reg:
                    cur_state = State::Reg;
                    break;
                case State::Sep:
                case State::Nil:
                    if (cur_ch == '0') { //if its zero, set to zer to transition to address, else raise error
                        cur_state = State::Zer;
                    } else {
                        raise_parsing_error(ParseErr::IdentifierNamingError);
                    }
                    break;
                case State::Imt:
                case State::Imm:
                    cur_state = State::Imm;
                    break;
                case State::Lbt:
                case State::Lbl:
                    cur_state = State::Lbl;
                    break;
                case State::Zer:
                    raise_parsing_error(ParseErr::ImmediateValueError);
                    break;
                case State::Adt:
                case State::Adr:
                    cur_state = State::Adr;
                    break;
                case State::Err:
                    break;
                case State::Cmt:
                    std::abort();
            }

        } else if (std::isalpha(cur_ch)) {

            switch (cur_state) {
                case State::Idn:
                case State::Rgt:
                case State::Reg:
                case State::Sep:
                case State::Nil:
                    cur_state = State::Idn;
                    break;
                case State::Imm:
                case State::Imt:
                    raise_parsing_error(ParseErr::ImmediateValueError);
                    break;
                case State::Lbt:
                case State::Lbl:
                    cur_state = State::Lbl;
                    break;
                case State::Zer:
                    raise_parsing_error(ParseErr::IdentifierNamingError);
                    break;
                case State::Adt:
                case State::Adr:
                    if ((cur_ch >= 'A' && cur_ch <= 'F') || (cur_ch >= 'a' && cur_ch <= 'f')) { //if between A-F or a-f
                        cur_state = State::Adr;
                    } else {
                        raise_parsing_error(ParseErr::AddressNamingError);
                    }
                    break;
                case State::Err:
                    break;
                case State::Cmt:
                    std::abort();
                
            }

        } else {

            cur_state = State::Err;
            raise_parsing_error(ParseErr::UnknownCharError);

        }

    }

}

void Tokenizer::set_action() {

    switch ( Parser::state_map.at(prev_state) ) {

        case StateType::Word:
        case StateType::RTransition:
            switch ( Parser::state_map.at(cur_state) ) {
                case StateType::Word:
                    cur_action = Action::Push;
                    break;
                case StateType::Separator:
                case StateType::None:
                    cur_action = Action::Emit;
                    break;
                case StateType::Transition: // anyways handled by error
                case StateType::RTransition:
                    cur_action = Action::Idle;
                    break;
            }
            break;

        case StateType::Transition:
            switch ( Parser::state_map.at(cur_state) ) {
                case StateType::Word:
                    cur_action = Action::Push;
                    break;
                default:
                    cur_action = Action::Idle; // anyways handled by error
                    break;
            }
            break;

        case StateType::Separator:
        case StateType::None:
            switch ( Parser::state_map.at(cur_state) ) {
                case StateType::Separator:
                case StateType::None:
                    cur_action = Action::Idle;
                    break;
                default:
                    cur_action = Action::Push;
                    break;
            }
            break;
    }

}

void Tokenizer::execute() {
    
    if (!error_detected) {
        
        Token token;
        switch (cur_action) {

        case Action::Push:
            buffer.push_back(cur_ch);
            break;
        
        case Action::Emit:
            
            
            switch (prev_state) {
                case State::Idn:
                    try {
                        token = Token(Instruction::TokenType::OpCode, Instruction::instruction_map.at(buffer)); //tt
                    } catch (const std::out_of_range& e) {
                        token = Token(Instruction::TokenType::Variable, buffer); //sv
                    }
                    break;
                case State::Reg:
                case State::Imm:
                    try {
                        size_t pos;
                        int val = std::stoi(buffer.substr(1), &pos);
                        if (pos != (buffer.size() - 1)) throw std::invalid_argument("Not completely int!");
                        switch (prev_state) {
                            case State::Reg: token = Token(Instruction::TokenType::Register, val); break; //account for error handling
                            case State::Imm: token = Token(Instruction::TokenType::Immediate, val); break;
                        }
                    } catch (const std::invalid_argument& e) { //shouldnt happen ideally
                        token = Token(Instruction::TokenType::Invalid, 0);
                    } catch (const std::out_of_range& e) {
                        switch (prev_state) {
                            case State::Reg: raise_parsing_error(ParseErr::RegisterOutOfRange); break;
                            case State::Imm: raise_parsing_error(ParseErr::ImmediateValueTooBig); break;
                        }
                    }
                    break;
                case State::Adr:
                    try {
                        size_t pos;
                        int val = std::stoi(buffer.substr(2), &pos, 16); //hex code
                        if (pos != (buffer.size() - 2)) throw std::invalid_argument("Not completely hex!");
                        token = Token(Instruction::TokenType::Address, val); //account for error handling
                    } catch (const std::invalid_argument& e) { //shouldnt happen ideally
                        token = Token(Instruction::TokenType::Invalid, 0);
                    } catch (const std::out_of_range& e) {
                        raise_parsing_error(ParseErr::AddressOutOfRange);
                    }
                    break;
                case State::Lbl:
                    token = Token(Instruction::TokenType::Label, buffer.substr(1));
                    break;
                default:
                    std::abort();
            }

            cur_inst.push_token(token); //move happens here
            buffer.clear();

        }    
    
    }

}

void Tokenizer::tokenize() {

    set_state(); // set state

    if (cur_state != State::Err) {
        set_action();
        create_inst();
    }

    if (cur_ch == '\n') {
        ++line_count;
        col_count = 0;
    } else {
        ++col_count;
    }
}

void Tokenizer::raise_parsing_error(ParseErr e) {

}