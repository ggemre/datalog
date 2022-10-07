#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

int main(int argc, char** argv) {
    // check argument count and quit if insufficient
    if (argc < 2) {
        std::cout << "Please provide an input file." << std::endl;
        return 1;
    }

    // convert file contents to single string
    std::string fileName = argv[1];
    std::ifstream inputFile(fileName);
    std::string fileAsString = std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    fileAsString += EOF;

    Lexer* lexer = new Lexer();

    // commence pipeline
    // <fileStr> -> lexer -> <tokens> -> parser -> <datalogProg>
    lexer->Run(fileAsString);
    Parser* parser = new Parser(lexer->GetTokens());
    Interpreter* interpreter = new Interpreter();
    interpreter->Interpret(parser->ParseDatalogProgram());

    delete lexer;
    delete parser;
    delete interpreter;

    return 0;
}
