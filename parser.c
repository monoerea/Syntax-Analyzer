/**
 * @file parser.h
 * @title RC Syntax Analyzer
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
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
//#include <limits.h>
#include <string.h>
#include "parser.h"

char *error_statement = "SYNTAX ERROR: There is an error on ";

int main(int argc, char const *argv[]) {
	parser();
	return 0;
}


/**
 * @brief parses the Symbols_Table.txt
 * 
 */
void parser() {

	if((opener = fopen("Symbol_table.txt", "r")) == NULL) {
		printf("ERROR: cannot open file");
		return;
	}
	
	/*while (fscanf(opener, "%s %s", allChar) == 1) {
		printf("%s", allChar);
	}*/
	  else
    {
        //4
        while ((charLex = fgetc(opener)) != EOF)
        {
            printf("%c", charLex);
        }
    }
	
	// fclose(opener);
	// opener = fopen("Parse.txt", "w");
	// getNextChar();
	// prog();

	fclose(opener);
	printf("program is done");
}

/**
 * @brief Creates a Node object
 * 
 * @param next 
 * @return NODE 
 */
NODE createNode(TOKEN type, char *next) {
	NODE node = (NODE)malloc(sizeof(struct node));
	strcpy(node->next, next);
	node->left = NULL;
	node->right = NULL;

	return (node);
}

/**
 * @brief deletes node
 * 
 * @param root 
 */
void deleteNode(NODE root) {
	if(root = NULL)
		return;
	if(root->left != NULL) {
        struct node *current = root->left;
        struct node *next = NULL;

        while(current != NULL) {
            next = current->right;
            deleteNode(current);
            current = next;
        }
    }
	free(root);
}

/**
 * @brief Inserts node at left of leaf node
 * 
 * @param node 
 * @param next 
 * @return node->left
 */
NODE insertHead(NODE head, NODE tail) {
	if(head == NULL)
		return NULL;
	if(head->left == NULL)
		head->left = tail;
	else {
		NODE current = head->left;
		while (current->right != NULL) {
			current = current->right;
		}
		current->right = tail;
	}
	return tail;
}

/**
 * @brief Get the next Char from Symbols_Table.txt file
 * 
 * @return LIST
 */
void getNextChar() {
	if ((charLex = getc(opener)) != EOF) {
		
		if (charLex == ' ' || charLex == '\n') {
			getNextChar();
		}
	}
	else
		charLex = EOF;
}

/**
 * @brief Get the Prev Char from Symbols_Table.txt file
 * 
 * @return LIST 
 */
// struct token_item* getPrevChar() {
// 	charToken = charToken->next;
//     if(charToken -> token != NULL) {
//         charLex = charToken -> token->lex;
//         charToken->rep = charToken->token->enum_rep;
//     }
//     return charToken;
// }

/**
 * @brief compares char and token
 * 
 * @param type 
 * @param next 
 * @return true 
 * @return false 
 */
bool compareToken(int type, char *next) {
	bool correct = parse(type);
	if(!correct)
		printf("%s %s", error_statement, charToken->next);
	return correct;
}

/**
 * @brief parses each token
 * 
 * @param type 
 * @return true 
 * @return false 
 */
bool parse(int type) {
	struct token_item* prev = charToken;
	if(token_rep == EOF)
		return false;
	getNextChar();
	bool correct = type == token_rep;
	if(!correct) {
		charToken = prev->prev;
		getNextChar();
	}
	return correct;
}

/**
 * @brief syntax of <program>
 * 
 * @return true 
 * @return false 
 */
bool prog() {
	root = createNode(PROG, "PROG");
	bool correct = statement(root);

	while(!correct && token_rep != EOF) {
		correct = statement(root);
		getNextChar();
	}

	if(!correct)
		printf("%s %s", error_statement, root->next);

	return correct;
}

/**
 * @brief syntax of <statement>
 * 
 * @param head
 * @return true 
 * @return false 
 */
bool statement(NODE head) {

	getNextChar();

	NODE local_node = createNode(STATE, "statement");
	struct token_item *prev = charToken;
	bool correct = asgn_statement(local_node)
					|| cond_statement(local_node)
					|| dclr_statement(local_node)
					|| init_statement(local_node)
					|| inpt_statement(local_node)
					|| itrv_statement(local_node)
					|| otpt_statement(local_node);

	//creates leaf
	if(correct)
		insertHead(head, local_node);
	else {
		deleteNode(local_node);
		charToken = prev->prev;
		getNextChar();
	}

	return correct;
}

/**
 * @brief syntax of <assignment_statement>
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool asgn_statement(NODE head) {

	struct token_item *prev = charToken;

	NODE local_node = createNode(ASGN, "assignment statement");
	bool correct = identifier(local_node)
                && expectToken(EQLS, "=")
				&& ((constant(local_node)
				|| expression(local_node)
				|| identifier(local_node))
				&& expectToken(SEMICOLON, ";"))
				|| (expectToken(LEFT_PAREN, "("))
				&& ((constant(local_node)
				|| expression(local_node)
				|| identifier(local_node))
				&& expectToken(RIGHT_PAREN, ")")
				&& expectToken(SEMICOLON, ";"));

	return correct;
}

/**
 * @brief syntax for condition statement
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool cond_statement(NODE head) {
	NODE local_node = createNode(COND, "conditional statement");
	bool correct = (expectToken(KEYWORD, "if")
				&& expectToken(LEFT_PAREN, "(")
				&& bool_expression(local_node)
				&& expectToken(RIGHT_PAREN, ")")
				&& expectToken(LEFT_CURB, "{")
				&& expectToken(STATE, "statement")
				&& expectToken(RIGHT_CURB, "}"))
				|| (expectToken(KEYWORD, "if")
				&& expectToken(LEFT_PAREN, "(")
				&& bool_expression(local_node)
				&& expectToken(RIGHT_PAREN, ")")
				&& expectToken(LEFT_CURB, "{")
				&& expectToken(STATE, "statement")
				&& expectToken(RIGHT_CURB, "}")
				&& expectToken(KEYWORD, "else")
				&& expectToken(KEYWORD, "if")
				&& expectToken(LEFT_PAREN, "(")
				&& expression(local_node)
				&& expectToken(RIGHT_PAREN, ")")
				&& expectToken(LEFT_CURB, "{")
				&& statement(local_node)
				&& expectToken(RIGHT_PAREN, "}"))
				|| (expectToken(KEYWORD, "if")
				&& expectToken(LEFT_PAREN, "(")
				&& bool_expression(local_node)
				&& expectToken(RIGHT_PAREN, ")")
				&& expectToken(LEFT_CURB, "{")
				&& expectToken(STATE, "statement")
				&& expectToken(RIGHT_CURB, "}")
				&& expectToken(KEYWORD, "else")
				&& expectToken(KEYWORD, "if")
				&& expectToken(LEFT_PAREN, "(")
				&& expression(local_node)
				&& expectToken(RIGHT_PAREN, ")")
				&& expectToken(LEFT_CURB, "{")
				&& statement(local_node)
				&& expectToken(RIGHT_PAREN, "}")
				&& expectToken(KEYWORD, "else")
				&& expectToken(LEFT_CURB, "{")
				&& statement(local_node)
				&& expectToken(RIGHT_CURB, "}"));

	return correct;
}

/**
 * @brief syntax for declarative statement
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool dclr_statement(NODE head) {

	NODE local_node = createNode(DCLR, "declarative statement");
	bool correct = data_type(local_node)
				&& identifier(local_node)
				&& expectToken(COMMA, ",")
				&& identifier(local_node)
				&& expectToken(SEMICOLON, ";");
	return correct;
}

/**
 * @brief syntax for initialization statement
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool init_statement(NODE head) {

	NODE local_node = createNode(INIT, "initialization");
	bool correct = data_type(local_node)
            && asgn_statement(local_node)
            && expectToken(SEMICOLON, ";");
	return correct;

}

/**
 * @brief syntax for input statement
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool inpt_statement(NODE head) {

	NODE local_node = createNode(INPT_S, "input statement");
	bool correct = expectToken(KEYWORD, "get")//get
                && expectToken(LEFT_SQRB,"[")
                && data_type(local_node)
                && expectToken(RIGHT_SQRB,"]")
                && expectToken(SEMICOLON, ";");

	return correct;
}

/**
 * @brief syntax for iterative statement
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool itrv_statement(NODE head) {

	struct token_item *prev = charToken;

	NODE local_node = createNode(ITRV, "iterative statement");
	bool correct = expectToken(RESERVED_WORD, "do")//do
                && expectToken(LEFT_CURB, "{")
                && statement(local_node)
                && expectToken(RIGHT_CURB, "}")
                && expectToken(RESERVED_WORD, "while")//while
                && expectToken(LEFT_SQRB, "[")
                && expression(local_node)
                && expectToken(RIGHT_SQRB, "]")
                || expectToken(RESERVED_WORD, "for")//for
                && expectToken(LEFT_SQRB, "[")
                && init_statement(local_node)
                && expectToken(SEMICOLON, ";")
                && bool_expression(local_node)
                && expectToken(SEMICOLON, ";")
                && expression(local_node)
                && expectToken(RIGHT_SQRB, "]")
                && expectToken(LEFT_CURB, "{")
                && statement(local_node)
                && expectToken(RIGHT_CURB, "}")
                || expectToken(RESERVED_WORD, "while")//while
                && expectToken(LEFT_SQRB, "[")
                && expression(local_node)
                && expectToken(RIGHT_SQRB, "]")
                && expectToken(LEFT_CURB, "{")
                && statement(local_node)
                && expectToken(RIGHT_CURB, "}")
                || expectToken(RESERVED_WORD, "while")//while
                && expectToken(LEFT_SQRB, "[")
                && expression(local_node)
                && expectToken(LEFT_CURB, "{")
                && statement(local_node)
                && expectToken(RIGHT_CURB, "}");
	return correct;
}

/**
 * @brief syntax for output statement
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool otpt_statement(NODE head) {

	NODE local_node = createNode(OTPT, "output statement");
	bool correct = expectToken(KEYWORD, "show") // show
                && expectToken(LEFT_PAREN,"(")
                && (expression(local_node)
                || identifier(local_node))
                && expectToken(COMMA, ",")
                && (expression(local_node)
                || identifier(local_node))
                && expectToken (RIGHT_SQRB,"]")
                && expectToken(SEMICOLON, ";");

	return correct;
}

/**
 * @brief syntax for arithmetic statement
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool arth_experssion(NODE head) {

	NODE local_node = createNode(ARTH, "arithmetic expression");
	bool correct = (identifier(local_node)
            || constant(local_node))
            && arth_operator(local_node)
            && (identifier(local_node)
            || constant(local_node));
}

/**
 * @brief syntax for boolean statement
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool bool_expression(NODE head) {

	NODE local_node = createNode(BLXP, "boolean expression");
	bool correct = (identifier(local_node)
				|| constant(local_node));
	return correct;
}

/**
 * @brief syntax for Set expression
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool set_expression(NODE head) {

	NODE local_node = createNode(STXP, "set expression");
	bool correct = (identifier(local_node)
            || constant(local_node))
            && ((bool_operator(local_node)
            || rltn_operator(local_node))
            && identifier(local_node)
            && constant(local_node));

	return correct;
}

/**
 * @brief syntax of expressions
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool expression(NODE head) {
	NODE local_node = createNode(EXPRS, "expression");
	bool correct = (identifier(local_node)
            || constant(local_node))
            && (operator(local_node)
                && identifier(local_node)
                ||constant(local_node)
            );
	return correct;
}

/**
 * @brief syntax for data types
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool data_type(NODE head) {
	NODE local_node = createNode(DTTP,"data type");
	bool correct = expectToken(DTTP, "bool")
				|| expectToken(DTTP, "byte")
				|| expectToken(DTTP, "character")
				|| expectToken(DTTP, "double")
				|| expectToken(DTTP, "float")
				|| expectToken(DTTP, "string");

	return correct;
}

/**
 * @brief syntax for Identifier
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool identifier(NODE head) {
	NODE local_node = createNode(IDENT, "identifier");
	bool correct = alphabet(local_node)
				&& alphanum(local_node)
				&& expectToken(UNDERSCORE, "_");
	return correct;
}

/**
 * @brief syntax for constants
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool constant(NODE head) {
	NODE local_node = createNode(CONST, "constant");
	bool correct = (constant(local_node)
				|| alphanum(local_node)
				|| digit(local_node))
				|| boolean(local_node);
	return correct;
}

/**
 * @brief syntax for operators
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool operator(NODE head) {
	NODE local_node = createNode(OPRT, "operator");
	bool correct = arth_operator(local_node)
				|| bool_operator(local_node)
				|| rltn_operator(local_node)
				|| set_operator(local_node);
	return correct;
}

/**
 * @brief syntax for arithmetic expressions
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool arth_operator(NODE head) {
	NODE local_node = createNode(ARITHMETIC_OP, "arithmetic operator");
	bool correct = expectToken(PLUS, "+")
				|| expectToken(MINUS, "-")
				|| expectToken(MULT, "*")
				|| expectToken(DIVD, "/")
				|| expectToken(MODULO, "%%")
				|| expectToken(DOUBLE_SLASH, "//")
				|| expectToken(POWER_OF, "^");
	return correct;
}

/**
 * @brief syntax for assignment operators
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool asgn_operator(NODE head) {
	NODE local_node = createNode(ASSIGNMENT_OP, "assignment operator");
	bool correct = expectToken(EQLS, "=");
	return correct;
}

/**
 * @brief syntax for relational operators
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool rltn_operator(NODE head) {
	NODE local_node = createNode(RELATIONAL_OP, "relational operator");
	bool correct = expectToken(RELATIONAL_EQLS, "==")
				|| expectToken(GREATER, ">")
				|| expectToken(LESS, "<")
				|| expectToken(GREATER_EQLS, ">=")
				|| expectToken(LESS_EQLS, "<=")
				|| expectToken(NOT_EQLS, "!=");
	return correct;
}

/**
 * @brief syntax for boolean operators
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool bool_operator(NODE head) {
	NODE local_node = createNode(BOOLEAN_OP, "boolean operator");
	bool correct = expectToken(EXCLAMATION, "!")
				|| expectToken(AND, "&&")
				|| expectToken(OR, "||");
	return correct;
}

/**
 * @brief Set the operator object
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool set_operator(NODE head) {
	NODE local_node = createNode(SET_OP, "set operator");
	bool correct = expectToken(BACKSLASH, "\\")
			&& (expectToken(SET_OP,"u")
            || expectToken(SET_OP,"i")
            || expectToken(SET_OP,"c")
            || expectToken(SET_OP,"-")
            || expectToken(SET_OP,"x"))
			&& expectToken(BACKSLASH, "\\");
	return correct;
}

/**
 * @brief syntax for alphanumeric
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool alphanum(NODE head) {

	NODE local_node = createNode(ALPHA, "alphabet");
	bool correct =  alphanum(local_node)
			|| upc(local_node)
            || lwc(local_node)
			|| digit(local_node);
	return correct;
}

/**
 * @brief syntax for alphabet
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool alphabet(NODE head) {
	NODE local_node = createNode(ALPHA, "alphabet");
	bool correct = upc(local_node)
            || lwc(local_node);
	
	return correct;
}

/**
 * @brief syntax for uppercase characters
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool upc(NODE head) {
	bool correct = expectToken(ALPHA,"A")
            || expectToken(ALPHA,"B")
            || expectToken(ALPHA,"C")
            || expectToken(ALPHA,"D")
            || expectToken(ALPHA,"E")
            || expectToken(ALPHA,"F")
            || expectToken(ALPHA,"G")
            || expectToken(ALPHA,"H")
            || expectToken(ALPHA,"I")
            || expectToken(ALPHA,"J")
            || expectToken(ALPHA,"K")
            || expectToken(ALPHA,"L")
            || expectToken(ALPHA,"M")
            || expectToken(ALPHA,"N")
            || expectToken(ALPHA,"O")
            || expectToken(ALPHA,"P")
            || expectToken(ALPHA,"Q")
            || expectToken(ALPHA,"R")
            || expectToken(ALPHA,"S")
            || expectToken(ALPHA,"T")
            || expectToken(ALPHA,"U")
            || expectToken(ALPHA,"V")
            || expectToken(ALPHA,"W")
            || expectToken(ALPHA,"X")
            || expectToken(ALPHA,"Y")
            || expectToken(ALPHA,"Z");

    return correct;
}

/**
 * @brief syntax for lower case character
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool lwc(NODE head) {
	NODE local_node = createNode(ALPHA, "alphabet");
	bool correct = expectToken(ALPHA,"a")
            || expectToken(ALPHA,"b")
            || expectToken(ALPHA,"c")
            || expectToken(ALPHA,"d")
            || expectToken(ALPHA,"e")
            || expectToken(ALPHA,"f")
            || expectToken(ALPHA,"g")
            || expectToken(ALPHA,"h")
            || expectToken(ALPHA,"i")
            || expectToken(ALPHA,"j")
            || expectToken(ALPHA,"k")
            || expectToken(ALPHA,"l")
            || expectToken(ALPHA,"m")
            || expectToken(ALPHA,"n")
            || expectToken(ALPHA,"o")
            || expectToken(ALPHA,"p")
            || expectToken(ALPHA,"q")
            || expectToken(ALPHA,"r")
            || expectToken(ALPHA,"s")
            || expectToken(ALPHA,"t")
            || expectToken(ALPHA,"u")
            || expectToken(ALPHA,"v")
            || expectToken(ALPHA,"w")
            || expectToken(ALPHA,"x")
            || expectToken(ALPHA,"y")
            || expectToken(ALPHA,"z");
	
	return correct;
}

/**
 * @brief syntax for digit
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool digit(NODE head) {
	bool correct = expectToken(NUMBER,"0")
            || expectToken(NUMBER,"1")
            || expectToken(NUMBER,"2")
            || expectToken(NUMBER,"3")
            || expectToken(NUMBER,"4")
            || expectToken(NUMBER,"5")
            || expectToken(NUMBER,"6")
            || expectToken(NUMBER,"7")
            || expectToken(NUMBER,"8")
            || expectToken(NUMBER,"9");
        
        return correct;
}

/**
 * @brief syntax for symbols
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool symbol(NODE head) {
	bool correct = expectToken(EXCM_MARK, "!")
				|| expectToken(AT,"@")
				|| expectToken(DOLLAR_SIGN,"$")
				|| expectToken(PERCENT,"%%")
				|| expectToken(CARET,"^")
				|| expectToken(AND,"&")
				|| expectToken(ASTERISK, "*")
				|| expectToken(LEFT_PAREN,"(")
				|| expectToken(RIGHT_PAREN,")")
				|| expectToken(HYPHEN, "-")
				|| expectToken(EQLS,"=")
				|| expectToken(PLUS,"+")
				|| expectToken(LEFT_SQRB,"[")
				|| expectToken(RIGHT_SQRB,"]")
				|| expectToken(LEFT_CURB,"{")
				|| expectToken(RIGHT_CURB,"}")
				|| expectToken(BACKSLASH,"")
				|| expectToken(OR, "|")
				|| expectToken(BACKTICK, "`")
				|| expectToken(SEMICOLON,(";"))
				|| expectToken(COLON,":")
				|| expectToken(SINGLE_QUOTE,"\'")
				|| expectToken(DOUBLE_QUOTE,"\"")// dalawa quote marks
				|| expectToken(COMMA,",")
				|| expectToken(LESS, "<")
				|| expectToken(GREATER,">")
				|| expectToken(PERIOD,".")
				|| expectToken(FRWRD_SLASH,"/")
				|| expectToken(QSTN_MARK,"?");

	return correct;
}

/**
 * @brief syntax for boolean
 * 
 * @param head 
 * @return true 
 * @return false 
 */
bool boolean(NODE head) {
	bool correct = expectToken(KEYWORD, "true")
				|| expectToken(KEYWORD, "false");
	return correct;
}

/**
 * @brief gets token and compares with enum
 * 
 * @param token 
 * @return true 
 * @return false 
 */
bool parseToken(int token) {
    struct token_item *prev = charToken;
    if(token_rep == EOF) 
		return false;
    getNextChar();
    bool correct = token == token_rep;
    if(!correct) {
        charToken = prev->prev;
        getNextChar();
    }
    return correct;
}

/**
 * @brief checks for correct token
 * 
 * @param type 
 * @param str 
 * @return true 
 * @return false 
 */
bool expectToken(TOKEN type, char* str) {
	bool correct = parseToken(type);
	if(!correct)
		printf("%s : Expected %s but returned %s", type, charToken->next->token->lex);
	return correct;
}
