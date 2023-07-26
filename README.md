# RPAL Language Lexical Analyzer and Parser

## Introduction

This project implements a lexical analyzer and a parser for the RPAL language. RPAL is a programming language with a specific set of lexical rules and grammar details. The goal of this project is to read RPAL programs, create an Abstract Syntax Tree (AST), standardize the tree, and implement a CSE machine for evaluation.

## Lexical Analyzer

The lexical analyzer is responsible for scanning the input RPAL program and identifying its tokens based on the lexical rules provided in RPAL_Lex.pdf. It is implemented in C++ using custom logic to tokenize the input program.

## Parser

The parser takes the tokens generated by the lexical analyzer and constructs the Abstract Syntax Tree (AST) for the input RPAL program. The grammar details for constructing the AST are specified in RPAL_Grammar.pdf. The parser is implemented in C/C++ and does not rely on external parser generators.

## Abstract Syntax Tree (AST) to Standardized Tree (ST)

Once the AST is constructed, the program implements an algorithm to convert the AST into a Standardized Tree (ST). This step involves performing specific transformations on the AST to ensure it adheres to certain standardization rules.

## CSE Machine

After standardizing the tree, the project implements a CSE machine to evaluate the RPAL program. The CSE machine is responsible for executing the standardized tree and producing the output for the given input program.

## Input and Output

The program can read RPAL programs from an input file. The output of the program will be the final result of the evaluation of program.

## Implementation Language

This project is implemented in C/C++.

## Usage

To use the program, simply compile the source code and run the executable. Provide the path to the RPAL program file as the input, and the program will display the AST and the result of the evaluation.

## References

- RPAL_Lex.pdf - Contains lexical rules for RPAL language.
- RPAL_Grammar.pdf - Contains grammar details for RPAL language.
