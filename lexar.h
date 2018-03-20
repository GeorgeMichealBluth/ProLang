//*****************************************************************************
// purpose: CSE 4713 / 6713 Assignment 1: Lexical Analyzer
// created: 8-25-2015
//  author: YOUR NAME HERE
//*****************************************************************************
 
#ifndef LEXER_H
#define LEXER_H

// Include standard IO streams
#include <stdio.h>

// The lexical analyzer global variables and functions
extern int   yylex();
extern FILE *yyin;         // input stream
extern FILE *yyout;        // output stream
extern int   yyleng;       // length of current lexeme
extern char *yytext;       // text of current lexeme

// Maximum lexeme length
#define MAX_LEXEME_LEN 100

// List of token codes

#define TOK_IF           1001  // if keyword
#define TOK_ELSE         1002  // else keyword
#define TOK_FOR          1003  // for keyword
#define TOK_WHILE        1004  // while keyword
#define TOK_PRINT		 1005  // print keyword
#define TOK_RETURN       1006  // return keyword
#define TOK_CONTINUE     1007  // continue keyword
#define TOK_BREAK        1008  // break keyword
#define TOK_DEBUG        1009  // debug keyword
#define TOK_READ         1010  // read keyword
#define TOK_LET          1011  // let keyword
#define TOK_INT			 1100  // int datatype specifier
#define TOK_FLOAT        1101  // float datatype specifier
#define TOK_STRING       1102  // string datatype specifier
#define TOK_SEMICOLON    2000  // ; punctuation
#define TOK_OPENPAREN    2001  // ( punctuation
#define TOK_CLOSEPAREN   2002  // ) punctuation
#define TOK_OPENBRACKET  2003  // [ punctuation
#define TOK_CLOSEBRACKET 2004  // ] punctuation
#define TOK_OPENBRACE    2005  // { punctuation
#define TOK_CLOSEBRACE   2006  // } punctuation
#define TOK_COMMA        2007  // , punctuation
#define TOK_PLUS         3000  // + operator
#define TOK_MINUS        3001  // - operator
#define TOK_MULTIPLY     3002  // * operator
#define TOK_DIVIDE       3003  // / operator
#define TOK_ASSIGN       3004  // assign operator
#define TOK_EQUALTO      3005  // equal to operator
#define TOK_LESSTHAN     3006  // less than operator
#define TOK_GREATERTHAN  3007  // greater than operator
#define TOK_NOTEQUALTO   3008  // not equal to operator
#define TOK_AND          3009  // and operator
#define TOK_OR           3010  // or operator
#define TOK_NOT          3011  // not operator
#define TOK_LENGTH       3012  // length operator
#define TOK_IDENTIFIER   4000  // identifier
#define TOK_INTLIT		 4001  // integer literal
#define TOK_FLOATLIT     4002  // float literal
#define TOK_STRINGLIT	 4003  // string literal
#define TOK_EOF          5000  // end of file
#define TOK_EOF_SL       5001  // end of file while parsing string literal
#define TOK_UNKNOWN      6000  // unknown lexeme

#endif

