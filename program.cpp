#include <iostream>
#include <fstream>
#include <string>
#include "lexicalanalyzer.h"
#include "parser.h"

using namespace std;

// Function to execute the lexer and parser on the input source file
void exec(ifstream& source) {
    lexer rpalLexer(&source);       
    parser rpalParser(&rpalLexer);  
    rpalParser.evaluateProgram();      
}

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        cout << "Please write \"./rpal20 {Program file}\"\n";
        return 0;
    }

    // Extract the filename from the command-line arguments
    string filename = argv[1];

    // Open the input source file
    ifstream source(filename);

    // Check if the file was opened successfully
    if (!source.is_open()) {
        cout << "Invalid input file: " << filename << "\n";
        return 0;
    }

    // Execute the lexer and parser on the input source file
    exec(source);

    // Close the source file
    source.close();

    return 0;
}