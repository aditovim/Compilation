#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Token.h"
#include "parser.h"

//
int currentIndex = 0;
Node* currentNode = NULL;
Node* headNode=NULL;

#define TOKEN_ARRAY_SIZE 100
/*
char* token_name;

static char *TOKEN_STRING[]={"TOKEN_PROGRAM","TOKEN_START","TOKEN_END","TOKEN_CONST","TOKEN_EXCCPTION","TOKEN_REAL","TOKEN_INTEGER","TOKEN_WHEN",
                             "TOKEN_DO","TOKEN_OTHERWISE","TOKEN_DONE","TOKEN_CYCLE","TOKEN_UNTIL","TOKEN_END_CYCLE","TOKEN_RAISE",
                             "TOKEN_ID","TOKEN_AR_OP","TOKEN_REAL_OP","TOKEN_ASSIGNMENT","TOKEN_REAL_NUM","TOKEN_INT_NUM","TOKEN_DIGIT","TOKEN_LETTER","TOKEN_COMMA","TOKEN_COLON",
                             "TOKEN_SEMICOLON","TOKEN_LEFT_CURLY_BRACES","TOKEN_RIGHT_CURLY_BRACES","TOKEN_LEFT_BRACKET","TOKEN_RIGHT_BRACKET","TOKEN_EOF"
};
*/
void create_and_store_token(eTOKENS kind, char* lexeme, int numOfLine)
{ 
	// case 1: there is still no tokens in the storage.
	int i=0;

	if (currentNode == NULL)
	{
		currentNode = (Node*)malloc(sizeof(Node));
		currentNode->NumOfNode=1;

		if(currentNode == NULL)
		{
			fprintf(yyout,"\nUnable to allocate memory! \n"); 
			exit(0);
		}
		currentNode->tokensArray = (Token*)malloc(sizeof(Token)*TOKEN_ARRAY_SIZE);

		for(i=0;i<TOKEN_ARRAY_SIZE;i++)
		{
			currentNode->tokensArray[i].lexeme=NULL;
		}

		if(currentNode->tokensArray == NULL)
		{
			fprintf(yyout,"\nUnable to allocate memory! \n"); 
			exit(0);
		}
		currentNode->prev = NULL;
		currentNode->next = NULL;
		headNode=currentNode;
	}

	// case 2: at least one token exsits in the storage.
	else
	{
		// the array (the current node) is full, need to allocate a new node
		if (currentIndex == TOKEN_ARRAY_SIZE -1)
		{
			currentIndex = 0;
			currentNode->next = (Node*)malloc(sizeof(Node));

			if(currentNode == NULL)
			{
				fprintf(yyout,"\nUnable to allocate memory! \n"); 
				exit(0);
			}
			currentNode->next->prev = currentNode;
			currentNode = currentNode->next;
			currentNode->NumOfNode=(currentNode->prev->NumOfNode)+1;
			currentNode->tokensArray = (Token*)malloc(sizeof(Token)*TOKEN_ARRAY_SIZE);

			for(i=0;i<TOKEN_ARRAY_SIZE;i++)
			{
				currentNode->tokensArray[i].lexeme=NULL;
			}


			if(currentNode->tokensArray == NULL)
			{
				fprintf(yyout,"\nUnable to allocate memory! \n"); 
				exit(0);
			}
			currentNode->next = NULL;
		}

		// the array (the current node) is not full
		else
		{
			currentIndex++;
		}
	}

	currentNode->tokensArray[currentIndex].numnode=currentNode->NumOfNode;
	currentNode->tokensArray[currentIndex].kind=kind;
	currentNode->tokensArray[currentIndex].lexeme = (char*)malloc(sizeof(char)*(strlen(lexeme)+1));
	strcpy(currentNode->tokensArray[currentIndex].lexeme, lexeme);
	currentNode->tokensArray[currentIndex].lineNumber = numOfLine;

	token_name=TOKEN_STRING[kind-1]; 
	fprintf(yyout, "Token from kind '%s' was found at line: %d, lexeme: '%s'.\n",token_name, numOfLine, lexeme);
}

/*
* This function returns the token in the storage that is stored immediately before the current token (if exsits).
*/

void initCompiler(char* inputFilePath, char* outputFilePath)
   {

	   	char formattedFilePath[500];

	fr= fopen(inputFilePath,"r");
	sprintf(formattedFilePath, "%s%s", outputFilePath, "_lex.txt"); 
	fwLex = fopen(formattedFilePath, "w"); 

	sprintf(formattedFilePath, "%s%s", outputFilePath, "_syntactic.txt"); 
	fwParser = fopen(formattedFilePath,"w");


   }

Token *back_token()
{ 
	Token* token=NULL;

	if(currentIndex > 0)
	{
		currentIndex--;
		token = &(currentNode->tokensArray[currentIndex]); 

	}
	else if (currentIndex == 0  && cur_token->numnode == currentNode->NumOfNode)
	{
	  currentIndex = TOKEN_ARRAY_SIZE-1;
	  token = &(currentNode->prev->tokensArray[currentIndex]);

	}

	return token;


}


Token *next_token()
{
	Token* token=NULL;
	
	//Check if yylex need to read from input file

	if(currentNode == NULL )
	 {
		 	yylex();
		token =&(currentNode->tokensArray[currentIndex]);
		return token;
	 }
	 
//	the same node 1-98
	if( currentNode->NumOfNode == cur_token->numnode && currentIndex  < TOKEN_ARRAY_SIZE-1 )
	{
		     if( currentNode->tokensArray[currentIndex+1].lexeme == NULL ) // the same index
              	{
		             yylex();
				    token =&(currentNode->tokensArray[currentIndex]);
				    return token;
	            }
			 else {                                                     // back token called
				 	  currentIndex++;
				    token =&(currentNode->tokensArray[currentIndex]);
				  return token;
			       }
	}

	// the same node 99
	if( currentNode->NumOfNode == cur_token->numnode && currentIndex == TOKEN_ARRAY_SIZE-1 )
	{
	              yylex();
				  token =&(currentNode->tokensArray[currentIndex]);
				return token;
	}


	// not the same 
	if( currentNode->NumOfNode != cur_token->numnode )
	{
		if( currentIndex  < TOKEN_ARRAY_SIZE-1) // 1-98
	       {
		         currentIndex++;
				 token =&(currentNode->prev->tokensArray[currentIndex]);
				 return token;

	       }
		else if( currentIndex  == TOKEN_ARRAY_SIZE-1)
		{
           	   currentIndex=0;
				token =&(currentNode->tokensArray[currentIndex]);
				return token;

		}
	}


	return token;
}


void analyzeFile(char* inputFilePath, char* outputFilePath) 
{
	initCompiler(inputFilePath, outputFilePath);
	initParser();
	
	yyin = fr;  //input file path
	yyout = fwLex; //output file path

//	parseProgram(); 
	parseMain(); // call firt parse
	
	yyrestart(yyin);
 

	//free memory in main


	
}

void freeList()
{
	struct Node* temp;

	while(headNode!=NULL)

	{

		temp = headNode;
		headNode=headNode->next;
		free(temp->tokensArray);
		free(temp);




	}


}

 





	
	
