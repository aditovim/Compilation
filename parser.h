#ifndef PARSER
#define PARSER 

#include "Token.h"

//define all parses

#define PROGRAM 1
#define DEFINITIONS 2
#define DEFINITIONS_A 3
#define DEFINITION 4
#define DEFINITION_A 5
#define DEFINITION_A_1 6
#define DEFINITION_A_2 7
#define TYPE 8
#define DIMENSIONS_LIST 9
#define DIMENSIONS_LIST_A 10
#define SIZE 11
#define COMMANDS 12
#define COMMANDS_A 13
#define COMMAND 14
#define RECEIVER 15 
#define RECEIVER_A 16
#define EXPRESSIONS_LIST 17
#define EXPRESSIONS_LIST_A 18
#define EXPRESSION 19
#define EXPRESSION_A 20
#define BASIC_EXPRESSION 21
#define BASIC_EXPRESSION_A 22
#define NUMBER 23
#define CONDITION 24

// declaration functions

void parseProgram();
void parseDefinitions();
void parseDefinitionsA();
void parseDefinition();
void parseDefinitionA();
void parseDefinitionA1();
void parseDefinitionA2();
void parseType();
void parseDimensionsList();
void parseDimensionsListA();
void parseSize();
void parseCommands();
void parseCommandsA();
void parseCommand();
void parseReceiver(); 
void parseReceiverA();
void parseExpressionsList();
void parseExpressionsListA();
void parseExpression();
void parseExpressionA();
void parseBasicExpression();
void parseBasicExpressionA();
void parseNumber();
void parseCondition();








// struct Rule

typedef struct Rule
{
	int* firstTokens;
	int* followTokens;
	int nullable;
	int firstTotalSize;
	int followTotalSize;

}Rule;

void initParser();
int match(int tokenId, int rule);
void errorRecovery(int rule);
void handleParsingErrorVar(int r );
void handleParsingErrorTok(int r);
void First(int NumOfRule,int token_first);
void Follow(int NumOfRule,int token_first);
int  IfFollow(int rule);
Token *cur_token;
Rule * arr_rule;
#endif