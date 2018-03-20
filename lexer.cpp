//*****************************************************************************
// purpose: CSE 4713 / 6713 Assignment 1: Lexical Analyzer
// created: 8-25-2015
//  author: YOUR NAME HERE
//*****************************************************************************
#include "lexer.h"
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <iostream>

//*****************************************************************************
// Do the lexical parsing
char lexeme[MAX_LEXEME_LEN];  // Character buffer for lexeme
int yylex()
{
  static char c = -1;         // Have we read the first character yet?
  int char_type;              // Hold the character type

  // Prepare the buffer to hold the lexeme
  for( int i = 0; i < MAX_LEXEME_LEN; i++ )
    lexeme[i] = '\0';
  yytext = lexeme;
  yyleng = 0;

  // If the very first character has not yet been read, read it
  if( c < 0 )
    c = fgetc( yyin );
 
  // This checks for empty spaces or new lines and skips through them. 
  while (c == ' ' || c == '\n') {
	  c = fgetc(yyin);
  }

  // Test for end of file
  if( feof(yyin) ) {
    // Ready for next time
    c = -1; 
    // Done!
    return( TOK_EOF );
  }
 
  // Start with punctuation.  If statements are not the most efficient way of 
  // designing this program, but they do follow my design
  if (c == '\"') {					// check for "
	  lexeme[yyleng++] = c;			// store data and read in new c
	  c = fgetc( yyin );
	  while (c != '\"') {			// start loop that continously reads in c til " is reached
		  if (feof(yyin)) {			// checks for EOF during string read
			  c = -1;
			  return(TOK_EOF_SL);
		  }
		  lexeme[yyleng++] = c;
		  c = fgetc( yyin );
	  }
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_STRINGLIT);
  } 
  else if (c == ';') {				// check for ;
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_SEMICOLON);
  }
  else if (c == '(') {				// check for (
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_OPENPAREN);
  }
  else if (c == ')') {				// check for )
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_CLOSEPAREN);
  }
  else if (c == '[') {				// check for [
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_OPENBRACKET);
  }
  else if (c == ']') {				// check for ]
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_CLOSEBRACKET);
  }
  else if (c == '{') {				// check for {
	  int p = 0;
	  std::cin >> p;
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_OPENBRACE);
  }
  else if (c == '}') {				// check for }
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_CLOSEBRACE);
  }
  else if (c == ',') {				// check for ,
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_COMMA);
  }
  else if (c == '+') {				// check for +
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_PLUS);
  }
  else if (c == '-') {				// check for -
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_MINUS);
  }
  else if (c == '*') {				// check for *
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_MULTIPLY);
  }
  else if (c == '/') {				// check for /
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_DIVIDE);
  }
  else if (c == ':') {				// checks for : 
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  if (c == '=') {				// checks for = after : 
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  return(TOK_ASSIGN);
	  }
	  else {
			  return(TOK_UNKNOWN);	// if = is not present returns unknown
		   }
  }
  else if (c == '=') {				// checks for =
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  if (c == '=') {				// checks for = after =
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  return(TOK_EQUALTO);
	  }
		  else {
			  return(TOK_UNKNOWN);	// if = is not present returns unknown
		  }
  }
  else if (c == '<') {				// checks for <
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  if (c == '>') {				// checks for > after < for NotEqualTo Token
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  return(TOK_NOTEQUALTO);
	  }
	  else {
		  return(TOK_LESSTHAN);		// if > not present returns the LessThan Token
	  }
  }
  else if (c == '>') {				// checks for >
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);
	  return(TOK_GREATERTHAN);
  }
  // Now we move onto c that start with alphabet characters
  else if (isalpha(c)) {			// first check if the if the c is an alphabet character		
	  switch (c) {					// i used switches to switch the code up a little, should 
									//be fine as long as each case is terminated with a return

	  case 'a':						// check for a then cycles through n, d.  
		  lexeme[yyleng++] = c;		// final check is for _ interpret between AND and IDENTIFIER
		  c = fgetc(yyin);
		  if (c == 'n') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'd') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (!isalnum(c) && c != '_') {
					  return(TOK_AND);
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') { // loops through until c is no longer a alphanumeric character
			  lexeme[yyleng++] = c;			// or _
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'b':								// if c is b, cheack r,e,a,k in order
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'r') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'e') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 'a') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (c == 'k') {
						  lexeme[yyleng++] = c;
						  c = fgetc(yyin);
						  if (!isalnum(c) && c != '_') {
							  return(TOK_BREAK);
						  }
					  }
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  if (c == ' ' || c == '\n') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
			  }
			  return (TOK_IDENTIFIER);
	  case 'c':								// if c is c check o,n,t,i,n,u,e
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'o') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'n') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 't') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (c == 'i') {
						  lexeme[yyleng++] = c;
						  c = fgetc(yyin);
						  if (c == 'n') {
							  lexeme[yyleng++] = c;
							  c = fgetc(yyin);
							  if (c == 'u') {
								  lexeme[yyleng++] = c;
								  c = fgetc(yyin);
								  if (c == 'e') {
									  lexeme[yyleng++] = c;
									  c = fgetc(yyin);
									  if (!isalnum(c) && c != '_') {
										  return(TOK_CONTINUE);
									  }
								  }
							  }
						  }
					  }
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'd':								// if c is d check e,b,u,g
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'e') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'b') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 'u') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (c == 'g') {
						  lexeme[yyleng++] = c;
						  c = fgetc(yyin);
						  if (!isalnum(c) && c != '_') {
							  return(TOK_DEBUG);
						  }
					  }
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'e':							// if c is e check l,s,e
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'l') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 's') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 'e') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (!isalnum(c) && c != '_') {
						  return(TOK_ELSE);
					  }
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'f':								// if c is f check l,o,a,t and o,r
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'l') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'o') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 'a') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (c == 't') {
						  lexeme[yyleng++] = c;
						  c = fgetc(yyin);
						  if (!isalnum(c) && c != '_') {
							  return(TOK_FLOAT);
						  }
					  }
				  }
			  }
		  }
		  else if (c == 'o') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'r') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (!isalnum(c) && c != '_') {
					  return(TOK_FOR);
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'i':								// if c is i check f and n,t
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'f') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (!isalnum(c) && c != '_') {
				  return(TOK_IF);
			  }
		  }
		  else if (c == 'n') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 't') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (!isalnum(c) && c != '_') {
					  return(TOK_INT);
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'l':									// if c is l check e,n,g,t,h and e,t
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'e') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'n') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 'g') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (c == 't') {
						  lexeme[yyleng++] = c;
						  c = fgetc(yyin);
						  if (c == 'h') {
							  lexeme[yyleng++] = c;
							  c = fgetc(yyin);
							  if (!isalnum(c) && c != '_') {
								  return(TOK_LENGTH);
							  }
						  }
					  }
				  }
			  }
			  else if (c == 't') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (!isalnum(c) && c != '_') {
					  return(TOK_LET);
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'o':								// if c is o check r
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'r') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (!isalnum(c) && c != '_') {
				  return(TOK_OR);
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'n':								// if c is n check o,t
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'o') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 't') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (!isalnum(c) && c != '_') {
					  return(TOK_NOT);
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'p':								// if c is p check r,i,n,t
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'r') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'i') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 'n') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (c == 't') {
						  lexeme[yyleng++] = c;
						  c = fgetc(yyin);
						  if (!isalnum(c) && c != '_') {
							  return(TOK_PRINT);
						  }
					  }
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'r':									// if c is r check e,a,d and e,t,u,r,n
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'e') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'a') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 'd') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (!isalnum(c) && c != '_') {
						  return(TOK_READ);
					  }
				  }
			  }
			  else if (c == 't') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 'u') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (c == 'r') {
						  lexeme[yyleng++] = c;
						  c = fgetc(yyin);
						  if (c == 'n') {
							  lexeme[yyleng++] = c;
							  c = fgetc(yyin);
							  if (!isalnum(c) && c != '_') {
								  return(TOK_RETURN);
							  }
						  }
					  }
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 's':									// if c is s check t,r,i,n,g
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 't') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'r') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 'i') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (c == 'n') {
						  lexeme[yyleng++] = c;
						  c = fgetc(yyin);
						  if (c == 'g') {
							  lexeme[yyleng++] = c;
							  c = fgetc(yyin);
							  if (!isalnum(c) && c != '_') {
								  return(TOK_STRING);
							  }
						  }
					  }
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  case 'w':									// if c is w check h,i,l,e
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  if (c == 'h') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  if (c == 'i') {
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
				  if (c == 'l') {
					  lexeme[yyleng++] = c;
					  c = fgetc(yyin);
					  if (c == 'e') {
						  lexeme[yyleng++] = c;
						  c = fgetc(yyin);
						  if (!isalnum(c) && c != '_') {
							  return(TOK_WHILE);
						  }
					  }
				  }
			  }
		  }
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
	  default:								// default just assumes identifier for any 
											// Identifer
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
		  while (isalnum(c) || c == '_') {
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
		  }
		  return (TOK_IDENTIFIER);
		  }
	  }
  }
  else if (isdigit(c)) {						// check for if c is digit
	  while (isdigit(c) || c == '.') {			// begin loop of number value
		  if (c == '.') {						// check for .
			  lexeme[yyleng++] = c;
			  c = fgetc(yyin);
			  while (isdigit(c)) {				// second loop for float characters
				  lexeme[yyleng++] = c;
				  c = fgetc(yyin);
			  }
			  return(TOK_FLOATLIT);
		  }
		  lexeme[yyleng++] = c;
		  c = fgetc(yyin);
	  }
	  return(TOK_INTLIT);
  }

	  // Store current character and read the next
	  lexeme[yyleng++] = c;
	  c = fgetc(yyin);

  // We don't yet know how to recognize any lexemes
  return( TOK_UNKNOWN );
}
