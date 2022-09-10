#include <sstream>
#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    this->type = type;
    this->description = description;
    this->line = line;
}

std::string Token::ToString() {
    std::stringstream os;
    os << "(" << TypeName(type) << ",\"" << description << "\"," << line << ")";
    return os.str();
}

std::string Token::TypeName(TokenType type) {
    switch (type) {
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::COLON:
            return "COLON";
        case TokenType::COLON_DASH:
            return "COLON_DASH";
        case TokenType::UNDEFINED:
            return "UNDEFINED";
        case TokenType::EOF_TOKEN:
            return "EOF";
    }
    return "ERROR";
}