/**
 * @file lexical.h
 * @title RC Lexical Analyzer
 * @author
 * 	Alarcon, Chastin A.
 * 	David, Adrien Christian D.
 * 	Ferrer, Bryan Kristoffer M.
 * 	Lintag, Juan Carlo G.
 * 	Olaguer, Matthew C.
 * 	Paano, Julius Angelo A.
 * 	Señorin, Ereka Sheen S. 
 * @section BSCS 3-1
 * @brief 
 * @version 0.1
 * @date 2022-02-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <ctype.h>
#include "global.h"
#include "scanner.h"

/**
 * @brief 
 * lookup - a function to lookup unknown symbols and return the token
 * @param ch used in switch case for comparison
 * @return nextToken is returned to the unknown symbol
 */
int lookup(char ch) {
	
	switch (ch) {
		
		//delimeters and brackets
		case '(':
			addChar();
			getChar();
			nextToken = LEFT_PAREN;
			break;
			
		case ')':
			addChar();
			getChar();
			nextToken = RIGHT_PAREN;
			break;
			
		case '[':
			addChar();
			getChar();
			nextToken = LEFT_SQRB;
			break;
			
		case ']':
			addChar();
			getChar();
			nextToken = RIGHT_SQRB;
			break;	

		case '{':
			addChar();
			getChar();
			nextToken = LEFT_CURB;
			break;

		case '}':
			addChar();
			getChar();
			nextToken = RIGHT_CURB;
			break;	

		case ';':
			addChar();
			getChar();
			nextToken = SEMICOLON;
			break;

		case ',':
			addChar();
			getChar();
			nextToken = COMMA;
			break;

		case ':':
			addChar();
			getChar();
			nextToken = COLON;
			break;

		case 34: // Double quote
			addChar();
			getChar();
			nextToken = DBLQ;
			break;

		case 39: // Single quote
			addChar();
			getChar();
			nextToken = SNGLQ;
			break;
		
		// Arithmetic Operators	
		case '%':
		case '^':
			addChar();
			getChar();
			nextToken = ARITHMETIC_OP;
			break;
		
		case '+':
			addChar();
			getChar();
			nextToken = ARITHMETIC_OP;
			switch (symbol){
				case '+':
				addChar();
				getChar();
				nextToken = ASSIGNMENT_OP;
				break;
			}
			break;
		
		case '-':
			addChar();
			getChar();
			nextToken = ARITHMETIC_OP;
			switch (symbol){
				case '-':
				addChar();
				getChar();
				nextToken = ASSIGNMENT_OP;
				break;
			}
			break;
			
		case '*':
			addChar();
			getChar();
			nextToken = ARITHMETIC_OP;
			
			switch (symbol){
				case '/':
				addChar();
				getChar();
				nextToken = COMMENT_R;
				break;
			}
			
			break;
		
		case '/':
			addChar();
			getChar();
			nextToken = ARITHMETIC_OP;
			
			switch (symbol){
				case '/':
				addChar();
				getChar();
				nextToken = ARITHMETIC_OP;
				break;
				
				case '*':
				addChar();
				getChar();
				nextToken = COMMENT_L;
				break;
				
			}
			
			break;
		
		// Relational operators		
		case '=':
			addChar();
			getChar();
			nextToken = ASSIGNMENT_OP;
			
			switch (symbol){
				case '=':
				addChar();
				getChar();
				nextToken = RELATIONAL_OP;
				break;
			}
			
			break;	
		
		case'<':
			addChar();
			getChar();
			nextToken = RELATIONAL_OP;
			switch (symbol){
				case '=':
				addChar();
				getChar();
				nextToken = RELATIONAL_OP;
				break;
			}
			break;
			
		case'>':
			addChar();
			getChar();
			nextToken = RELATIONAL_OP;
			switch (symbol){
				case '=':
				addChar();
				getChar();
				nextToken = RELATIONAL_OP;
				break;
			}
			break;
			
		case'&':
			addChar();
			getChar();
			nextToken = RELATIONAL_OP;
			switch (symbol){
				case '&':
				addChar();
				getChar();
				nextToken = BOOLEAN_OP;
				break;
			}
			
			break;
		
		case'!':
			addChar();
			getChar();
			nextToken = BOOLEAN_OP;
			
			switch (symbol){
				case '=':
				addChar();
				getChar();
				nextToken = RELATIONAL_OP;
				break;
			}
			break;
			
		case'|':
			addChar();
			getChar();
			nextToken = NOTIDENT;
				switch (symbol){
				case '|':
				addChar();
				getChar();
				nextToken = BOOLEAN_OP;
				break;
			}
			break;
		
		case 92:
			addChar();
			getChar();
			nextToken = NOTIDENT;
			
			switch (symbol){
				case 'u':
				addChar();
				getChar();
				nextToken = NOTIDENT;		
				goto close;
				break; 
				
				case 'i':
				addChar();
				getChar();
				nextToken = NOTIDENT;
				goto close;
				break; 
				
				case '-':
				addChar();
				getChar();
				nextToken = NOTIDENT;
				goto close;
				break; 
			
				case 'c':
				addChar();
				getChar();
				nextToken = NOTIDENT;
				goto close;
				break; 
				
				case 'x':
				addChar();
				getChar();
				nextToken = NOTIDENT;
				goto close;
				break; 
				
				close:
				switch (symbol){
					case 92:
					addChar();
					getChar();
					nextToken = SET_OP;
					break;
				}
				while (isalpha(symbol) || symbol == DIGIT){
					addChar();
					getChar();
					nextToken = NOTIDENT;
				}
				break;
			}
			break;
		
		case '@':
		case '$':
		case '#':
		case '`':
		case '.':
		case '?':	
			addChar();
			getChar();
			nextToken = OTHER_SYMBOLS;
		break;	
		
		
		default:
			addChar();
			getChar();
			nextToken = EOF;		
			break;
		}
				
		return nextToken;
}

/**
 * @brief 
 * addChar - a function to add nextChar to lexeme
 */
void addChar() {
	if (lexLen <= 1000) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}

/**
 * @brief Get the Char object
 * getChar - a function to get the next character of input and determine its character class
 */
void getChar() {
	if ((nextChar = getc(in_fp)) != EOF) {
		
		if (nextChar == '_')
		charClass = nextChar;
		else if (nextChar == 46)
		charClass = nextChar;
		else if (isalpha(nextChar)){
			charClass = nextChar;
			symbol = nextChar;
		}
		else if (isdigit(nextChar))
			charClass = DIGIT;
		else {
			charClass = UNKNOWN;
			symbol = nextChar;
		}
	}
	else
		charClass = EOF;
}

/**
 * @brief 
 * getNonBlank - a function to call getChar until it returns a non-whitespace character
 */
void getNonBlank() {
	while (isspace(nextChar))
		getChar();
}

/**
 * @brief 
 * lex - a simple lexical analyzer for arithmetic expressions
 * @return int 
 */
int lex() {
	lexLen = 0;
	getNonBlank();
	switch (charClass) {

		/* Parse Keywords/Reserved words */			
		case 'b':
            addChar();
            getChar();
            nextToken = IDENT;
            switch (charClass){
                case 'o':
                    addChar();
                    getChar();
                    switch (charClass){
                        case 'o':
                            addChar();
                            getChar();
                            switch (charClass){
                                case 'l':
                                    addChar();
                                    getChar();
                                    nextToken = RESERVED_WORD;
                                    goto Keyword;
									break;
                            }
                    		goto identifier;
							break;
					}
					goto identifier;
					break;
            }
            switch (charClass){
                case 'r':
                    addChar();
                    getChar();
                    switch (charClass){
                        case 'e':
                            addChar();
                            getChar();
                            switch (charClass){
                                case 'a':
                                    addChar();
                                    getChar();
                                    switch (charClass){
                                        case 'k':
                                            addChar();
                                            getChar();
                                            nextToken = RESERVED_WORD;
                                            goto Keyword;
											break;
                                    }
                                    goto identifier;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
            }
            switch (charClass){
                case 'y':
                    addChar();
                    getChar();
                    switch (charClass){
                        case 't':
                            addChar();
                            getChar();
                            switch (charClass){
                                case 'e':
                                    addChar();
                                    getChar();
                                    nextToken = RESERVED_WORD;
                                    goto Keyword;
									break;
                            }
                            goto identifier;
							break;
                    }
                    goto identifier;
					break;
            }
            goto identifier;
            break;
		
		case 'c':
			addChar();
			getChar();
			nextToken = IDENT;
			
			switch (charClass){
			
				case 'a':
                    addChar();
                    getChar();
                    switch (charClass){
                        case 's':
                            addChar();
                            getChar();
                            switch (charClass){
                                case 'e':
                                    addChar();
                                    getChar();
                                    nextToken = RESERVED_WORD;
                                    goto Keyword;
									break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
			
				case 'B':
				addChar();
				getChar();
				nextToken = IDENT;
		
					switch (charClass){
						case 'i':
						addChar();
						getChar();
						nextToken = IDENT;
						
							switch (charClass){
							case 'n':
							addChar();
							getChar();
							nextToken = IDENT;
								
								switch (charClass){
								case 'd':
								addChar();
								getChar();
								nextToken = KEYWORD;
								goto Keyword;
								break;	
							}
						goto identifier;
                        break;
					}
					goto identifier;
                    break;
				}
				
				case 'h':
                    addChar();
                    getChar();
                    switch (charClass){
                        case 'a':
                            addChar();
                            getChar();
                            switch (charClass){
                                case 'r':
                                    addChar();
                                    getChar();
                                    nextToken = RESERVED_WORD;
                                    goto Keyword;
									break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;	
                    
					goto identifier;
					break;
			// C O
			case 'o':
				addChar();
				getChar();
				nextToken = IDENT;
					
				switch(charClass){
					case 'n':
						addChar();
						getChar();
						nextToken = IDENT;
							
							switch(charClass){
							case 'c':
								addChar();
								getChar();
								nextToken = IDENT;
									
									switch(charClass){
									case 'a':
										addChar();
										getChar();
										nextToken = IDENT;
										
										switch(charClass){
										case 't':
											addChar();
											getChar();
											nextToken = KEYWORD;
											goto Keyword;
											break;
										}
										goto identifier;
										break;
									}
								
								
                                case 's':
                                    addChar();
                                    getChar();
                                    switch (charClass){
                                        case 't':
                                            addChar();
                                            getChar();
                                            nextToken = RESERVED_WORD;
                                            break;
                                    }
                                    break;
                           
								
								goto identifier;	
								break;
							}
					goto identifier;		
					break;
				}
			                 
			
			goto identifier;
			break;
			
			}
		
		goto identifier;		
		break;
		
		case 'd':
			addChar();
			getChar();
			nextToken = IDENT;
				
			switch (charClass){
				case 'a':
					addChar();
					getChar();
					nextToken = IDENT;
						
					switch (charClass){
						case 't':
							addChar();
							getChar();
							nextToken = IDENT;
										
							switch (charClass){
								case 'a':
									addChar();
									getChar();
									nextToken = IDENT;
													
									switch (charClass){
										case 'f':
											addChar();
											getChar();
											nextToken = IDENT;
																
										switch (charClass){
											case 'r':
												addChar();
												getChar();
												nextToken = IDENT;
																		
											switch (charClass){
												case 'a':
													addChar();
													getChar();
													nextToken = IDENT;
																				
												switch (charClass){
													case 'm':
														addChar();
														getChar();
														nextToken = IDENT;
																						
													switch (charClass){
														case 'e':
															addChar();
															getChar();
															nextToken = KEYWORD;
															goto Keyword;
															break;
														}
													goto identifier;										
													break;
												}
												goto identifier;									
												break;
											}
											goto identifier;
											break;
										}
										goto identifier;						
										break;
									}
									goto identifier;				
									break;
								}
							goto identifier;	
							break;
					}
					goto identifier;
					break;
			
			
			case 'e':
                    addChar();
                    getChar();
                    switch (charClass){
                        case 'f':
                            addChar();
                            getChar();
                            switch (charClass){
                                case 'a':
                                    addChar();
                                    getChar();
                                    switch (charClass){
                                        case 'u':
                                            addChar();
                                            getChar();
                                            switch (charClass){
                                                case 'l':
                                                    addChar();
                                                    getChar();
                                                    switch (charClass){
                                                        case 't':
                                                            addChar();
                                                            getChar();
                                                            nextToken = RESERVED_WORD;
                                                            goto Keyword;
															break;
                                                    }
                                                    goto identifier;
                                                    break;
                                            }
                                            goto identifier;
                                            break;
                                    }
                                    goto identifier;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
            }


            switch (charClass){
                case 'o':
                    addChar();
                    getChar();
                    nextToken = RESERVED_WORD;
            }
            switch (charClass){
                case 'u':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass){
                        case 'b':
                            addChar();
                            getChar();
                            switch (charClass){
                                case 'l':
                                    addChar();
                                    getChar();
                                    switch (charClass){
                                        case 'e':
                                            addChar();
                                            getChar();
                                            nextToken = RESERVED_WORD;
                                            break;
                                    }
                                    goto identifier;
									break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
            }
            goto identifier;
            break;
			
		case 'e':
            addChar();
            getChar();
            nextToken = IDENT;
            switch (charClass){
                case 'l':
                    addChar();
                    getChar();
                    switch (charClass){
                        case 's':
                            addChar();
                            getChar();
                            switch (charClass){
                                case 'e':
                                    addChar();
                                    getChar();
                                    nextToken = RESERVED_WORD;

                                    break;
                            }
                            break;
                    }
                    break;
            }
            break;

        case 'f':
            addChar();
            getChar();
            nextToken = IDENT;
            switch (charClass) {
                case 'a':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass) {
                        case 'l':
                            addChar();
                            getChar();
                            nextToken = IDENT;
                            switch (charClass) {
                                case 's':
                                    addChar();
                                    getChar();
                                    nextToken = IDENT;
                                    switch (charClass) {
                                        case 'e':
                                            addChar();
                                            getChar();
                                            nextToken = RESERVED_WORD;
                                            goto Keyword;
                                            break;
                                    }
                                    goto identifier;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
                case 'l':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass) {
                        case 'o':
                            addChar();
                            getChar();
                            nextToken = IDENT;
                            switch (charClass) {
                                case 'a':
                                    addChar();
                                    getChar();
                                    nextToken = IDENT;
                                    switch (charClass) {
                                        case 't':
                                            addChar();
                                            getChar();
                                            nextToken = RESERVED_WORD;
                                            goto Keyword;
                                            break;
                                    }
                                    goto identifier;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
                case 'o':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass) {
                        case 'r':
                            addChar();
                            getChar();
                            nextToken = RESERVED_WORD;
                            goto Keyword;
                            break;
                    }
                    goto identifier;
                    break;
            }
            goto identifier;
            break;	
		
		case 'g':
			addChar();
			getChar();
			
			switch(charClass){
				case 'e':
					addChar();
					getChar();
						
				switch(charClass){
					case 't':
						addChar();
						getChar();
						nextToken = KEYWORD;
						break;
					}
				
				break;
				}
				
			break;	
		
		case 'i':
			addChar();
			getChar();
			
				switch(charClass){
					case 'n':
						addChar();
						getChar();
						
							switch(charClass){
								case 'p':
									addChar();
									getChar();
									
										switch(charClass){
											case 'u':
												addChar();
												getChar();
												
													switch(charClass){
														case 't':
															addChar();
															getChar();
															nextToken = KEYWORD;
															goto Keyword;
															break;
														}
												goto identifier;
												break;
											}
									case 't':
			                            addChar();
			                        	getChar();
			                            nextToken = RESERVED_WORD;
			                            goto Keyword;
			                            break;
									
									goto identifier;
									break;
								}
						case 'f':
		                    addChar();
		                    getChar();
		                    nextToken = RESERVED_WORD;
		                    goto Keyword;
		                    break;
		                    
		                    goto identifier;
							break;
					}
		           
	            goto identifier;
	            break;
				
			goto identifier;		
			break;
		
		case 'l':
			addChar();
			getChar();
			
			switch(charClass){
					case 'i':
						addChar();
						getChar();
						
						switch(charClass){
							case 's':
								addChar();
								getChar();
									
								switch(charClass){
									case 't':
										addChar();
										getChar();
										nextToken = KEYWORD;
										goto Keyword;
										break;
									}
								goto identifier;	
								break;
							}
						goto identifier;
						break;
			 
			 case 'o':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass) {
                        case 'n':
                            addChar();
                            getChar();
                            nextToken = IDENT;
                            switch (charClass) {
                                case 'g':
                                    addChar();
                                    getChar();
                                    nextToken = RESERVED_WORD;
                                    goto Keyword;
                                    break;
                            }
                            goto identifier;
                            break;
						
			}
			goto identifier;
                            break;
		}
			goto identifier;
			break;
			
			case 'r':
			addChar();
			getChar();
			nextToken = IDENT;
			
			switch (charClass){
				case 'B':
				addChar();
				getChar();
				nextToken = IDENT;
		
					switch (charClass){
						case 'i':
						addChar();
						getChar();
						nextToken = IDENT;
						
							switch (charClass){
							case 'n':
							addChar();
							getChar();
							nextToken = IDENT;
								
								switch (charClass){
								case 'd':
								addChar();
								getChar();
								nextToken = KEYWORD;
								goto Keyword;
								break;	
							}
							goto identifier;
							break;
						}
						goto identifier;
						break;	
					}
					goto identifier;
					break;
				
				case 'e':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass) {
                        case 't':
                            addChar();
                            getChar();
                            nextToken = IDENT;
                            switch (charClass) {
                                case 'u':
                                    addChar();
                                    getChar();
                                    nextToken = IDENT;
                                    switch (charClass) {
                                        case 'r':
                                            addChar();
                                            getChar();
                                            nextToken = IDENT;
                                            switch (charClass) {
                                                case 'n':
                                                    addChar();
                                                    getChar();
                                                    nextToken = RESERVED_WORD;
                                                    goto Keyword;
                                                    break;
                                            }
                                            goto identifier;
                                            break;
                                    }
                                    goto identifier;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
				
				}
			goto identifier;
			break;
			
		
		case 's':
			addChar();
			getChar();
			nextToken = IDENT;
			
				switch (charClass){
					case 't':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass) {
                        case 'r':
                            addChar();
                            getChar();
                            nextToken = IDENT;
                            switch (charClass) {
                                case 'i':
                                    addChar();
                                    getChar();
                                    nextToken = IDENT;
                                    switch (charClass) {
                                        case 'n':
                                            addChar();
                                            getChar();
                                            nextToken = IDENT;
                                            switch (charClass) {
                                                case 'g':
                                                    addChar();
                                                    getChar();
                                                    nextToken = RESERVED_WORD;
                                                    goto Keyword;
                                                    break;
                                            }
                                            goto identifier;
                                            break;
                                    }
                                    goto identifier;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;

                case 'w':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass) {
                        case 'i':
                            addChar();
                            getChar();
                            nextToken = IDENT;
                            switch (charClass) {
                                case 't':
                                    addChar();
                                    getChar();
                                    nextToken = IDENT;
                                    switch (charClass) {
                                        case 'c':
                                            addChar();
                                            getChar();
                                            nextToken = IDENT;
                                            switch (charClass) {
                                                case 'h':
                                                    addChar();
                                                    getChar();
                                                    nextToken = RESERVED_WORD;
                                                    goto Keyword;
                                                    break;
                                            }
                                            goto identifier;
                                            break;
                                    }
                                    goto identifier;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;

                case 'e':
                    addChar();
                    getChar();
                    nextToken = IDENT;

                    switch (charClass){
                        case 't':
                            addChar();
                            getChar();
                            nextToken = KEYWORD;
                            goto Keyword;
                            break;
                    }
                    goto identifier;
                    break;


                case 'h':
                    addChar();
                    getChar();
                    nextToken = IDENT;

                    switch (charClass){
                        case 'o':
                            addChar();
                            getChar();
                            nextToken = IDENT;

                            switch (charClass){
                                case 'w':
                                    addChar();
                                    getChar();
                                    nextToken = KEYWORD;
                                    goto Keyword;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
            }
            goto identifier;
            break;

        case 't':
            addChar();
            getChar();
            nextToken = IDENT;
            switch (charClass) {
                case 'r':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass) {
                        case 'u':
                            addChar();
                            getChar();
                            nextToken = IDENT;
                            switch (charClass) {
                                case 'e':
                                    addChar();
                                    getChar();
                                    nextToken = RESERVED_WORD;
                                    goto Keyword;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
            }
            goto identifier;
            break;

        case 'w':
            addChar();
            getChar();
            nextToken = IDENT;
            switch (charClass) {
                case 'h':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass) {
                        case 'i':
                            addChar();
                            getChar();
                            nextToken = IDENT;
                            switch (charClass) {
                                case 'l':
                                    addChar();
                                    getChar();
                                    nextToken = IDENT;
                                    switch (charClass) {
                                        case 'e':
                                            addChar();
                                            getChar();
                                            nextToken = RESERVED_WORD;
                                            goto Keyword;
                                            break;
                                    }
                                    goto identifier;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
            }
            goto identifier;
            break;

        case 'v':
            addChar();
            getChar();
            nextToken = IDENT;
            switch (charClass) {
                case 'o':
                    addChar();
                    getChar();
                    nextToken = IDENT;
                    switch (charClass) {
                        case 'i':
                            addChar();
                            getChar();
                            nextToken = IDENT;
                            switch (charClass) {
                                case 'd':
                                    addChar();
                                    getChar();
                                    nextToken = RESERVED_WORD;
                                    goto Keyword;
                                    break;
                            }
                            goto identifier;
                            break;
                    }
                    goto identifier;
                    break;
            }
            goto identifier;
            break;

		/* Parse constant literals */
		
		case DIGIT:
			addChar();
			getChar();
			nextToken = INTEGER;
			while (charClass == DIGIT) {
				addChar();
				getChar();
			}
			if (charClass == 46){
						addChar();
						getChar();
						nextToken = FLOAT;
			while (charClass == DIGIT) {
						addChar();
						getChar();
						nextToken = FLOAT;
					}
			}
			if (isalpha(charClass)){
				addChar();
				getChar();
				nextToken = NOTIDENT;
			
			while (isalpha(charClass) || charClass == DIGIT || charClass == '_'){
					addChar();
					getChar();
					nextToken = NOTIDENT;
				}
				goto end;
			}
			
			break;
		
		/* Brackets and operators */
		case UNKNOWN:
			lookup(symbol);
			break;
		
		/* EOF */
		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;
			break;
		
		identifier:
		default:
			
			while (isalpha(charClass)) { 
				addChar();
				getChar();
				nextToken = IDENT;
				
				while (isalpha(charClass) || charClass == DIGIT){
					addChar();
					getChar();
					nextToken = IDENT;
				}
				while (charClass == '_'){
					addChar();
					getChar();
					nextToken = NOTIDENT;
				}
				while (isalpha(charClass) || charClass == DIGIT){
					addChar();
					getChar();
					nextToken = IDENT;
				}
				
			}
			
			if (charClass == '_'){
				addChar();
				getChar();
				nextToken = NOTIDENT;
				while (isalpha(charClass) || charClass == DIGIT){
					addChar();
					getChar();
					nextToken = NOTIDENT;
				}
			}
			
			end:	
			Keyword:
			break;
		
	} /* End of switch */
	
		write = fopen ("Symbol_table.txt", "a+");
		
		if (nextToken == 9){
			printf("Lexeme: %s \tToken: INTEGER\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: INTEGER\n", lexeme);
		}
		else if (nextToken == 10){
			printf("Lexeme: %s \tToken: FLOAT\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: FLOAT\n", lexeme);
		}
		else if (nextToken == 11){
			printf("Lexeme: %s \tToken: IDENTIFIER\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: IDENTIFIER\n", lexeme);
		}
		else if (nextToken == 12){
			printf("Lexeme: %s \tToken: INVALID_IDENTIFIER\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: INVALID_IDENTIFIER\n", lexeme);
		}
		else if (nextToken == 20){
			printf("Lexeme: %s \tToken: ARITHMETIC_OP\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: ARITHMETIC_OP\n", lexeme);
		}
		else if (nextToken == 21){
			printf("Lexeme: %s \tToken: RELATIONAL_OP\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: RELATIONAL_OP\n", lexeme);
		}
		else if (nextToken == 22){
			printf("Lexeme: %s \tToken: ASSIGNMENT_OP\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: ASSIGNMENT_OP\n", lexeme);
		}
		else if (nextToken == 23){
			printf("Lexeme: %s \tToken: SET_OP\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: SET_OP\n", lexeme);
		}
		else if (nextToken == 24){
			printf("Lexeme: %s \tToken: BOOLEAN_OP\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: BOOLEAN_OP\n", lexeme);
		}
		else if (nextToken == 25){
			printf("Lexeme: %s \tToken: KEYWORD\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: KEYWORD\n", lexeme);
		}
		else if (nextToken == 26){
			printf("Lexeme: %s \tToken: RESERVED_WORD\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: RESERVED_WORD\n", lexeme);
		}
		else if (nextToken == 27){
			printf("Lexeme: %s \tToken: LEFT_PAREN\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: LEFT_PAREN\n", lexeme);
		}
		else if (nextToken == 28){
			printf("Lexeme: %s \tToken: RIGHT_PAREN\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: RIGHT_PAREN\n", lexeme);
		}
		else if (nextToken == 29){
			printf("Lexeme: %s \tToken: LEFT_SQRB\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: LEFT_SQRB\n", lexeme);
		}
		else if (nextToken == 30){
			printf("Lexeme: %s \tToken: RIGHT_SQRB\n", lexeme);
			fprintf(write,"Lexeme: %s \tToken: RIGHT_SQRB\n", lexeme);
		}
		else if (nextToken == 31){
        printf("Lexeme: %s \tToken: LEFT_CURB\n", lexeme);
        fprintf(write, "Lexeme: %s \tToken: LEFT_CURB\n",lexeme);
	    }
	    else if (nextToken == 32){
	        printf("Lexeme: %s \tToken: RIGHT_CURB\n", lexeme);
	        fprintf(write, "Lexeme: %s \tToken: RIGHT_CURB\n",lexeme);
	    }
	    else if (nextToken == 33){
	        printf("Lexeme: %s \tToken: SEMICOLON\n", lexeme);
	        fprintf(write, "Lexeme: %s \tToken: SEMICOLON\n",lexeme);
	    }
	    else if (nextToken == 34){
	        printf("Lexeme: %s \tToken: DBLQ\n", lexeme);
	        fprintf(write, "Lexeme: %s \tToken: DBLQ\n",lexeme);
	    }
	    else if (nextToken == 35){
	        printf("Lexeme: %s \tToken: COLON\n", lexeme);
	        fprintf(write, "Lexeme: %s \tToken: COLON\n",lexeme);
	    }
	    else if (nextToken == 36){
	        printf("Lexeme: %s \tToken: COMMA\n", lexeme);
	        fprintf(write, "Lexeme: %s \tToken: COMMA\n",lexeme);
	    }
	    else if (nextToken == 39){
	        printf("Lexeme: %s \tToken: SNGLQ\n", lexeme);
	        fprintf(write, "Lexeme: %s \tToken: SNGLQ\n",lexeme);
	    }
	    else if (nextToken == 40){
	        printf("Lexeme: %s \tToken: COMMENT_L\n", lexeme);
	        fprintf(write, "Lexeme: %s \tToken: COMMENT_L\n",lexeme);
	    }
	    else if (nextToken == 41){
	        printf("Lexeme: %s \tToken: COMMENT_R\n", lexeme);
	        fprintf(write, "Lexeme: %s \tToken: COMMENT_R\n",lexeme);
	    }
	    else if (nextToken == 95){
	        printf("Lexeme: %s \tToken: UNDERSCORE\n", lexeme);
	        fprintf(write, "Lexeme: %s \tToken: UNDERSCORE\n",lexeme);
	    }
	    else if (nextToken == 96){
	        printf("Lexeme: %s \tToken: OTHER_SYMBOLS\n", lexeme);
	        fprintf(write, "Lexeme: %s \tToken: OTHER_SYMBOLS\n",lexeme);
	    }
		
		fclose(write);
	
	return nextToken;
	
} /* End of function lex */
