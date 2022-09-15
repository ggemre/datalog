#include <sstream>
#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    this->type = type;
    this->description = description;
    this->line = line;
}

/**
 * used for creating self describing string, in the lexer run method
 * 
 * @return information on token as a string, formatted
 * @see lexer::run()
 */
std::string Token::ToString() {
    std::stringstream os;
    os << "(" << TypeName(type) << ",\"" << description << "\"," << line << ")";
    return os.str();
}

/**
 * used for converting TokenType to a string
 * 
 * @param type the type of token
 * @return string equivalent of type
 */
std::string Token::TypeName(TokenType type) {
    switch (type) {
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::PERIOD:
            return "PERIOD";
        case TokenType::Q_MARK:
            return "Q_MARK";
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::COLON:
            return "COLON";
        case TokenType::COLON_DASH:
            return "COLON_DASH";
        case TokenType::MULTIPLY:
            return "MULTIPLY";
        case TokenType::ADD:
            return "ADD";
        case TokenType::SCHEMES:
            return "SCHEMES";
        case TokenType::FACTS:
            return "FACTS";
        case TokenType::RULES:
            return "RULES";
        case TokenType::QUERIES:
            return "QUERIES";
        case TokenType::ID:
            return "ID";
        case TokenType::STRING:
            return "STRING";
        case TokenType::COMMENT:
            return "COMMENT";
        case TokenType::UNDEFINED:
            return "UNDEFINED";
        case TokenType::EOF_TOKEN:
            return "EOF";
    }
    return "ERROR";
}