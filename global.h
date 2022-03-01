#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/**
 * @brief Global Variables
 * 
 */
int charClass;
int symbol;
char lexeme [1000];
char nextChar;
int lexLen;
int nextToken;

/**
 * @brief Token codes
 */
#define INTEGER 9 
#define FLOAT 10 
#define IDENT 11
#define NOTIDENT 12
#define ARITHMETIC_OP 20 
#define RELATIONAL_OP 21
#define ASSIGNMENT_OP 22
#define SET_OP 23
#define BOOLEAN_OP 24
#define KEYWORD 25
#define RESERVED_WORD 26
#define LEFT_PAREN 27
#define RIGHT_PAREN 28
#define LEFT_SQRB 29
#define RIGHT_SQRB 30
#define LEFT_CURB 31
#define RIGHT_CURB 32
#define SEMICOLON 33
#define DBLQ 34
#define COLON 35
#define COMMA 36
#define SNGLQ 39
#define COMMENT_L 40
#define COMMENT_R 41
#define UNDERSCORE 95
#define OTHER_SYMBOLS 96

/**
 * @brief Character Classes
 * 
 */
#define DIGIT 1
#define UNKNOWN 1000

#endif