#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <math.h>
#define TK_EOF 0 // Why not just make a const? Why 0 used as EOF token??
#define TK_ELON 1 
#define TK_BEGIN 2 
#define TK_END 3
#define TK_IF
//put more keywords here
#define TK_WHILE 30

// operators
#define TK_PLUS 40
#define TK_MINUS 41
#define TK_LESS_THAN 42
#define TK_GREATER_THAN 43
#define TK_EQUAL_TO 44
#define TK_COMMA 45
#define TK_COLON 46
#define TK_SEMICOLON 47
#define TK_DOT 48
#define TK_LEFT_PARAN 49
#define TK_RIGHT_PARAN 50

#define TK_INTLIT 100
#define TK_CHARLIT 101
#define TK_REALLIT 102
#define TK_STRLIT 103

#define TK_UNKNOWN 200

unsigned char* initialize();
void getToken();
void printToken();

#endif