#include <iostream>
#include <fstream>
#include "Lexer.h"

int main(int argc, char** argv) {
    std::string fileName;

    if (argc < 2) {
        fileName = "../tests/Lab1PassOffCases/1-70/input7.txt";
    }
    else {
        fileName = argv[1];
    }

    std::ifstream inputFile(fileName);
    std::string fileAsString = std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    Lexer* lexer = new Lexer();

    // TODO
    lexer->Run(fileAsString);
    std::cout << lexer->GetTokens() << std::endl;

    delete lexer;

    return 0;
}
