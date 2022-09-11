#include <iostream>
#include <fstream>
#include "Lexer.h"

int main(int argc, char** argv) {
    

    if (argc < 2) {
        std::cout << "Please provide an input file." << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    std::ifstream inputFile(fileName);
    std::string fileAsString = std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    fileAsString += EOF;

    Lexer* lexer = new Lexer();

    lexer->Run(fileAsString);
    std::cout << lexer->GetTokens();

    delete lexer;

    return 0;
}
