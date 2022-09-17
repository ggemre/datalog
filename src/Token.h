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
    TokenType type;
    std::string description;
    int line;

    std::string TypeName(TokenType type);

public:
    Token(TokenType type, std::string description, int line);
    std::string ToString();   
};

#endif // TOKEN_H