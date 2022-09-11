#include <iostream>
#include <fstream>
#include "Lexer.h"

int main(int argc, char** argv) {
    std::string fileName;

    if (argc < 2) {
        fileName = "../tests/Lab1PassOffCases/1-100/input2.txt";
    }
    else {
        fileName = argv[1];
    }

    std::ifstream inputFile(fileName);
    std::string fileAsString = std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    fileAsString += EOF;

    Lexer* lexer = new Lexer();

    // TODO
    lexer->Run(fileAsString);
    std::cout << lexer->GetTokens();

    delete lexer;

    return 0;
}
