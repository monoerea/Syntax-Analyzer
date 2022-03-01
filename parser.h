#ifndef PARSER_H_INCLUDED
   #define PARSER_H_INCLUDED

/**
 * @brief checks for error handling
 * 
 */
enum token_type {
	PROG = 0,
	STATE = 1,
	EQLS = 2,
	CONST = 3,
	EXPRS = 4,
	ITRV = 5,
	INPT_S = 6,
	INIT = 7,
	COND = 8,
	OTPT = 97,
	DCLR = 98,
	ARTH = 99,
	BLXP = 100,
	DTTP = 101,
	STXP = 102,
	OPRT = 103,
	ASGN = 120,

	//String symbols
	EXCM_MARK = 121,
	AT = 122,
	DOLLAR_SIGN = 123,
	CARET = 124,
	ASTERISK = 125,
	HYPHEN = 126,
	BACKSLASH = 127,
	BACKTICK = 128,
	SINGLE_QUOTE = 129,
	DOUBLE_QUOTE = 130,
	PERIOD = 131,
	FRWRD_SLASH = 132,
	QSTN_MARK = 133,
	PERCENT = 134,

	//idk
	NUMBER = 135,
	ALPHA = 136,
	ALPHANUM = 137,

	//Arithmetic
	PLUS = 104,
	MINUS = 105,
	MULT = 106,
	DIVD = 107,
	MODULO = 108,
	DOUBLE_SLASH = 109,
	POWER_OF = 110,

	//Boolean
	EXCLAMATION = 111,
	AND = 112,
	OR = 113,
	
	//Relational Operators
	RELATIONAL_EQLS = 114,
	GREATER = 115,
	LESS = 116,
	GREATER_EQLS = 117,
	LESS_EQLS = 118,
	NOT_EQLS = 119,

	//numbers
	INTEGER = 9,
	FLOAT = 10,
	IDENT = 11,
	NOTIDENT = 12,
	
	//operations
	ARITHMETIC_OP = 20,
	RELATIONAL_OP = 21,
	ASSIGNMENT_OP = 22,
	SET_OP = 23,
	BOOLEAN_OP = 24,

	//words
	KEYWORD = 25,
	RESERVED_WORD = 26,

	//brakets
	LEFT_PAREN = 27,
	RIGHT_PAREN = 28,
	LEFT_SQRB = 29,
	RIGHT_SQRB = 30,
	LEFT_CURB = 31,
	RIGHT_CURB = 32,

	//symbols
	SEMICOLON = 33,
	DBLQ = 34,
	COLON = 35,
	COMMA = 36,
	SNGLQ = 39,

	//comments
	COMMENT_L = 40,
	COMMENT_R = 41,

	//misc.
	UNDERSCORE = 95,
	OTHER_SYMBOLS = 96
};

typedef enum token_type TOKEN;

/**
 * @brief NODE data structure
 * 
 */
struct node {
	char next[100];
	TOKEN type;
	struct node* left;
	struct node* right;
};

typedef struct node* NODE;

NODE root;

struct token {
	char lex[100];
	int enum_rep;
};

struct token_item {
	struct token* token;
	struct token_item* next;
	struct token_item* prev;
	int rep;
};

struct token_linked_list {
    int length;
	struct token_linked_list *head;
    struct token_linked_list *tail;
};

typedef struct token_linked_list* LIST;

struct token_item* charToken;

/**
 * @brief Parser function prototypes
 * 
 */
void parser();
bool parse(int);
//struct token_item* getNextChar();
void getNextChar();
//struct token_item* getPrevChar();
bool expectToken(TOKEN type, char *str);
void deleteNode(NODE delete);
bool compareToken(int type, char *next);
NODE createNode(TOKEN type,char *next);
NODE insertHead(NODE head, NODE tail);

bool prog();
bool statement(NODE head);
bool asgn_statement(NODE head);
bool cond_statement(NODE head);
bool dclr_statement(NODE head);
bool init_statement(NODE head);
bool inpt_statement(NODE head);
bool itrv_statement(NODE head);
bool otpt_statement(NODE head);
bool arth_experssion(NODE head);
bool bool_expression(NODE head);
bool set_expression(NODE head);
bool expression(NODE head);
bool data_type(NODE head);
bool identifier(NODE head);
bool constant(NODE head);
bool operator(NODE head);
bool arth_operator(NODE head);
bool asgn_operator(NODE head);
bool rltn_operator(NODE head);
bool bool_operator(NODE head);
bool set_operator(NODE head);
bool alphanum(NODE head);
bool alphabet(NODE head);
bool upc(NODE head);
bool lwc(NODE head);
bool digit(NODE head);
bool symbol(NODE head);
bool boolean(NODE head);

/**
 * @brief Parser variables
 * 
 */
FILE *opener, *fopen(), *write;
char charLex;
int token_rep;
char allChar[1000];

#endif