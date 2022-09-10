#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOF_TOKEN
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    TokenType type;
    std::string description;
    int line;

    std::string TypeName(TokenType type);

public:
    Token(TokenType type, std::string description, int line);
    std::string ToString();

    // TODO: add other needed methods
    
};

#endif // TOKEN_H

