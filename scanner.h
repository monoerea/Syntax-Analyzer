#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

/**
 * @brief Function Prototypes
 * @return * Function 
 */
int lookup(char ch);
void addChar();
extern void getChar();
void getNonBlank();
extern int lex();

FILE *in_fp, *fopen(), *write;

#endif