#include <iostream>
#include "Lexer.h"

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    // TODO
    std::string inp = "Hello this is a sentence";
    lexer->Run(inp);
    std::cout << lexer->GetTokens() << std::endl;

    delete lexer;

    return 0;
}
