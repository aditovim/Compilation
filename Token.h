#ifndef TOKEN_H
#define TOKEN_H

// all tokens

typedef enum eTOKENS
{

     TOKEN_PROGRAM=1,
     TOKEN_START,
     TOKEN_END,
     TOKEN_CONST,
     TOKEN_EXCCPTION,
     TOKEN_REAL,
     TOKEN_INTEGER,
     TOKEN_WHEN,
     TOKEN_DO,
     TOKEN_OTHERWISE,
     TOKEN_DONE,
     TOKEN_CYCLE,
     TOKEN_UNTIL,
     TOKEN_END_CYCLE,
     TOKEN_RAISE,
	 TOKEN_AR_OP,
     TOKEN_ID,
     TOKEN_REAL_OP,
     TOKEN_ASSIGNMENT,
	 TOKEN_REAL_NUM,
	 TOKEN_INT_NUM,
     TOKEN_DIGIT,
     TOKEN_LETTER,
     TOKEN_COMMA,
     TOKEN_COLON,
     TOKEN_SEMICOLON,
     TOKEN_LEFT_CURLY_BRACES, 
     TOKEN_RIGHT_CURLY_BRACES,
     TOKEN_LEFT_BRACKET,
     TOKEN_RIGHT_BRACKET,
     TOKEN_EOF
}eTOKENS;

typedef struct Token
{
	eTOKENS kind;
	char *lexeme;
	int lineNumber;
	int numnode;
}Token;

typedef struct Node
{
	int NumOfNode;
	Token *tokensArray;
	struct Node *prev;
	struct Node *next;
} Node;


static char *TOKEN_STRING[]={"TOKEN_PROGRAM","TOKEN_START","TOKEN_END","TOKEN_CONST","TOKEN_EXCCPTION","TOKEN_REAL","TOKEN_INTEGER","TOKEN_WHEN",
                             "TOKEN_DO","TOKEN_OTHERWISE","TOKEN_DONE","TOKEN_CYCLE","TOKEN_UNTIL","TOKEN_END_CYCLE","TOKEN_RAISE","TOKEN_AR_OP",
                             "TOKEN_ID","TOKEN_REAL_OP","TOKEN_ASSIGNMENT","TOKEN_REAL_NUM","TOKEN_INT_NUM","TOKEN_DIGIT","TOKEN_LETTER","TOKEN_COMMA","TOKEN_COLON",
                             "TOKEN_SEMICOLON","TOKEN_LEFT_CURLY_BRACES","TOKEN_RIGHT_CURLY_BRACES","TOKEN_LEFT_BRACKET","TOKEN_RIGHT_BRACKET","TOKEN_EOF"
};
char* token_name;

FILE *yyin,*yyout;
FILE *fr;
FILE *fwLex;
FILE *fwParser;



void freeList();
void create_and_store_token(eTOKENS kind, char* lexeme, int numOfLine);
void analyzeFile(char* inputFilePathe , char* outputFilePath);
void initCopiler(char* inputFilePath , char* outputFilePath);
void parseMain();

Token *next_token();
Token *back_token();

extern yylex();   //fix all red



#endif