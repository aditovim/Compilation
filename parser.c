#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "Token.h"


void parseMain()
{

	parseProgram(); 
}



void parseProgram()
{
	fprintf(fwParser,"Rule: PROGRAM -> program DEFINITIONS start COMMANDS end \n");

	if(!match(TOKEN_PROGRAM,PROGRAM)) return;
	parseDefinitions();
	if(!match(TOKEN_START,PROGRAM)) return;
	parseCommands();
	if(!match(TOKEN_END,PROGRAM)) return;
	if(!match(TOKEN_EOF,PROGRAM))return;

}

void parseDefinitions()
{
	fprintf(fwParser,"Rule:DEFINITIONS -> DEFINITION DEFINITIONS_A  \n");
	parseDefinition();
	parseDefinitionsA();




}





//DEFINITIONS_A ->, DEFINITION DEFINITIONS_A | ↋

void parseDefinitionsA() //DEFINITIONS_A -nullable
{
	
	cur_token = next_token();
	
	
	switch(cur_token->kind)
	{
	    
		
			
			case TOKEN_START:     // DEFINITIONS_A -nullable
				      
				      fprintf(fwParser, "Rule:DEFINITIONS_A ->epsilon \n");
					  cur_token = back_token(); // we jumped  ahead two  ids  so we go two back two for start
					  //cur_token = back_token();
						break;





			case TOKEN_COMMA: // id first of DEFINITION
				   	   fprintf(fwParser, "Rule: DEFINITIONS_A -> , DEFINITION DEFINITIONS_A  \n");
				       //cur_token=back_token();
					   parseDefinition();
	                   parseDefinitionsA();
			
		               break;
			
	         default:
				/* fprintf(fwParser, "Rule:DEFINITIONS_A ->epsilon \n");
			     cur_token = back_token();*/
				 
		      handleParsingErrorVar(DEFINITIONS_A);
			  errorRecovery(DEFINITIONS_A);
			   
			   break;
		
		
					
	
	}


}



//DEFINITION -> id DEFINITION_A

void parseDefinition()
{
	fprintf(fwParser, "Rule:  DEFINITION -> id DEFINITION_A \n" );
	if(!match(TOKEN_ID,DEFINITION))return;
	parseDefinitionA();
}


//DEFINITION_A -> : DEFINITION_A_1 | [DIMENSIONS_LIST] : TYPE

void parseDefinitionA()   
{
	cur_token=next_token();
	switch(cur_token->kind)
	{
	case TOKEN_COLON :
		  fprintf(fwParser, "Rule:  DEFINITION_A -> : DEFINITION_A_1 \n");
		 // cur_token= back_token();
		  parseDefinitionA1();
		  break;
		          
	  
	case TOKEN_LEFT_BRACKET :
	      fprintf(fwParser, "Rule:  DEFINITION_A ->[DIMENSIONS_LIST] : TYPE \n");
		  parseDimensionsList(); // no need  cur_token= back_token();
	//	 cur_token= next_token();
		  if(!match(TOKEN_RIGHT_BRACKET,DEFINITION_A))return;
		  if(!match(TOKEN_COLON,DEFINITION_A))return;
		 // cur_token= back_token(); // NO NEED FOR TEST4   need because parseType()  have next_token() 
		  parseType(); // have next_token()
		//  cur_token= next_token(); //  need TOKEN_RIGHT_BRACKET see INT 
		  break;

		  //?
		  
	default:
		handleParsingErrorVar(DEFINITION_A);
		errorRecovery(DEFINITION_A);
			break;
	
	}


}

//DEFINITION_A_1 -> TYPE DEFINITION_A_2 | exception 


void parseDefinitionA1()    
{
	cur_token= next_token();
	switch (cur_token->kind)
	{
	case TOKEN_EXCCPTION : 
		fprintf(fwParser, "Rule:   DEFINITION_A_1  -> exception  \n" );
		break;

	default: 

		    fprintf(fwParser, "Rule: DEFINITION_A_1 -> TYPE DEFINITION_A_2  \n");
			 cur_token= back_token(); 
			 parseType();
			 parseDefinitionA2();
			 break;
			



	}


}

//void parseDefinitionA1()    
//{
//	cur_token= next_token();
//	switch (cur_token->kind)
//	{
//	case TOKEN_EXCCPTION : 
//		fprintf(fwParser, "Rule:   DEFINITION_A_1  -> exception  \n" );
//		break;
//
//	 case TOKEN_INTEGER:
//	 case TOKEN_REAL:
//			 fprintf(fwParser, "Rule: DEFINITION_A_1 -> TYPE DEFINITION_A_2  \n");
//			 cur_token= back_token(); 
//			 parseType();
//			 parseDefinitionA2();
//			 break;
//
//	default: // no need? //need he isnt nullable
//
//		    handleParsingErrorVar(DEFINITION_A_1);
//		    errorRecovery(DEFINITION_A_1);
//			break;
//
//		/*
//		  fprintf(fwParser, "Rule: DEFINITION_A_1 -> TYPE DEFINITION_A_2   \n");
//		  cur_token= back_token();
//		  parseType();
//		  parseDefinitionA2();
//		  break;
//
//		  */
//
//	 
//
//			
//
//	}
//
//
//}

void parseDefinitionA2()    // DEFINITION_A_2 -- nullable
{
	cur_token=next_token();
	
		 switch (cur_token->kind)
		 {
		 case TOKEN_CONST:
			 fprintf(fwParser, "Rule: DEFINITION_A_2-> const := NUMBER \n");
			 if(!match(TOKEN_ASSIGNMENT,DEFINITION_A_2))return;
			 parseNumber();
			// cur_token=next_token(); 
			 // for DEFINITION_A_2-> const := NUMBER  if not he see int and no COMMA
			// cur_token = back_token();
			 break; 
		 case TOKEN_COMMA:
			 fprintf(fwParser, "Rule: DEFINITION_A_2->epsilon \n");
			  //parseDefinition(); 
			  cur_token = back_token();
	          break;

		 case TOKEN_START:
			   fprintf(fwParser, "Rule: DEFINITION_A_2->epsilon \n");
			   cur_token = back_token();
			   break;

		 default: 
			/* fprintf(fwParser, "Rule: DEFINITION_A_2-> epsilon \n");
			 cur_token = back_token();*/
			 	 handleParsingErrorVar(DEFINITION_A_2);
		         errorRecovery(DEFINITION_A_2);
			    break;
			 /*fprintf(fwParser, "Rule: DEFINITION_A_2-> NULL \n");
			   cur_token = back_token();
			   break;*/

			


		 }

}

// have recover

void parseType()
{
	 cur_token = next_token();

	 switch (cur_token->kind) 
	 {
	 case TOKEN_REAL:
		 fprintf(fwParser, "Rule: TYPE-> real \n");
		 break;
	 case TOKEN_INTEGER:
		 fprintf(fwParser, "Rule: TYPE->  integer \n");
		 break;
	default:
		    handleParsingErrorVar(TYPE);
			errorRecovery(TYPE);
			break;
	
	 }



}

void parseDimensionsList()
{
	fprintf(fwParser, "Rule: DIMENSIONS_LIST -> SIZE  DIMENSIONS_LIST_A\n");
	parseSize();
    parseDimensionsListA();

}

// nullable no need recover

void parseDimensionsListA()  // DIMENSIONS_LIST_A -- nullable
{


	cur_token=next_token();
	switch(cur_token->kind)
	{
	case TOKEN_COMMA: 
		fprintf(fwParser, "Rule: DIMENSIONS_LIST_A -> , SIZE DIMENSIONS_LIST_A  \n");
		parseSize();
		parseDimensionsListA();
		break;



	case TOKEN_RIGHT_BRACKET:   //nullable
	  
		fprintf(fwParser, "Rule: DIMENSIONS_LIST_A ->epsilon \n");
		cur_token = back_token();
		break;

	default:
	//	fprintf(fwParser, "Rule: DIMENSIONS_LIST_A ->epsilon \n");
		    handleParsingErrorVar(DIMENSIONS_LIST_A);
			errorRecovery(DIMENSIONS_LIST_A);
		//cur_token = back_token();
			break;
	
	}


}
	

// have recover
void parseSize()
{
	 cur_token = next_token();

	 switch (cur_token->kind) 
	 {
	 case TOKEN_INT_NUM:
		 fprintf(fwParser, "Rule: SIZE-> int_num \n");
		 break;
	 case TOKEN_ID:
		 fprintf(fwParser, "Rule: SIZE-> id \n");
		 break;
	default:
		    handleParsingErrorVar(SIZE);
			errorRecovery(SIZE);
			break;
	
	 }


}

void parseCommands()
{
	fprintf(fwParser, "Rule: COMMANDS -> COMMAND  COMMANDS_A \n");
	parseCommand();
	parseCommandsA();
	

}

// null able no need recover

void parseCommandsA() //CommandsA  -nullable
{
	 
	   cur_token = next_token();
	    
	  	 switch (cur_token->kind)
		 { 

			 case TOKEN_SEMICOLON:

					 fprintf(fwParser, "Rule: COMMANDS_A  ->  ; COMMANDS \n");
				  // cur_token=back_token();
					 parseCommands();
					 break;

			 case TOKEN_END:
			 case TOKEN_OTHERWISE:
			 case TOKEN_DONE:
			 case TOKEN_UNTIL:
			 case TOKEN_RIGHT_CURLY_BRACES:
				 fprintf(fwParser, "Rule: COMMANDS_A -> epsilon  \n");
			     cur_token = back_token(); 
				 break;


              default:
				 /* fprintf(fwParser, "Rule: COMMANDS_A -> epsilon  \n");
				  cur_token = back_token();*/
					 handleParsingErrorVar(COMMANDS_A);
			         errorRecovery(COMMANDS_A);
					 break;
         }

}

// defult  "Rule: COMMAND-> RECEIVER := EXPRESSION 

void parseCommand() // NOT FINISHED    RECEIVER_A  -nullable      COMMANDS_A    -nullable
{
	     cur_token = next_token();
	  	 switch (cur_token->kind)
		 {
			 case TOKEN_WHEN:
				  
			 fprintf(fwParser, "Rule:  COMMAND -> when CONDITION do COMMANDS otherwise COMMANDS done \n");
			 parseCondition();
			 if(!match(TOKEN_DO,COMMAND))return;
			 parseCommands();
			// fprintf(fwParser," %d\n" , cur_token->kind );
			// cur_token = next_token();//for  COMMANDS otherwise 
			 if(!match(TOKEN_OTHERWISE,COMMAND))return;
		//	 fprintf(fwParser," %d\n" , cur_token->kind );
			 parseCommands();
			 if(!match(TOKEN_DONE,COMMAND))return;

			 break;

			 case TOKEN_CYCLE:

			 fprintf(fwParser, "Rule: COMMAND->  cycle COMMANDS until CONDITION end_cycle  \n");
			 parseCommands();
			 if(!match(TOKEN_UNTIL,COMMAND))return;
			 parseCondition();
			 if(!match(TOKEN_END_CYCLE,COMMAND))return;
			 break;

			 case TOKEN_LEFT_CURLY_BRACES:
				 fprintf(fwParser, "Rule: COMMAND-> { DEFINITIONS start COMMANDS }  \n");
				 parseDefinitions();
				 if(!match(TOKEN_START,COMMAND))return;
				 parseCommands();
				 if(!match(TOKEN_RIGHT_CURLY_BRACES,COMMAND))return;
				 break;

			 case TOKEN_RAISE:
				 fprintf(fwParser, "Rule: COMMAND->  raise id  \n");
				 if(!match(TOKEN_ID,COMMAND))return;
				 break;

		    // case TOKEN_ID: // id first of RECIVER
				  //   fprintf(fwParser, "Rule: COMMAND-> RECEIVER := EXPRESSION  \n");
				  //  cur_token=back_token();
					 //parseReceiver();
				  //   if(!match(TOKEN_ASSIGNMENT,COMMAND))return;
				  //   parseExpression();
					
					

					 //break;
		  default:
					fprintf(fwParser, "Rule: COMMAND-> RECEIVER := EXPRESSION  \n");
				    cur_token=back_token();
					parseReceiver();
				    if(!match(TOKEN_ASSIGNMENT,COMMAND))return;
				    parseExpression();
			         
					break;


		 }
}
			//		 default:

			//	     
			//		// handleParsingErrorVar(COMMAND);
			//      //   errorRecovery(COMMAND);
			//         
			//		 break;

		 /*}*/



/*
RECEIVER  -> id  RECEIVER_A
RECEIVER_A -> ↋ | [EXPRESSIONS_LIST]  
*/
     
void parseReceiver()
{
	fprintf(fwParser, "Rule: RECEIVER  -> id  RECEIVER_A \n");
	if(!match(TOKEN_ID,RECEIVER))return;
	parseReceiverA();

}

// nulable no need recover

void parseReceiverA() //RECEIVER_A  ---nullable
{
         cur_token = next_token();
	  	 switch (cur_token->kind)
		 {
		 case TOKEN_LEFT_BRACKET:
			 fprintf(fwParser, "Rule: RECEIVER_A -> [EXPRESSIONS_LIST]   \n");
			 parseExpressionsList();
			 if(!match(TOKEN_RIGHT_BRACKET,RECEIVER_A))return;
			 break;


		 case TOKEN_ASSIGNMENT: //nullable
			  fprintf(fwParser, "Rule: RECEIVER_A -> epsilon  \n");
				 cur_token=back_token();
				 break;

		 default:  
			  /*fprintf(fwParser, "Rule: RECEIVER_A -> epsilon  \n");
			 cur_token=back_token();*/
			  handleParsingErrorVar(RECEIVER_A);
		         errorRecovery(RECEIVER_A);
			 break;
				/* handleParsingErrorVar(RECEIVER_A);
		         errorRecovery(RECEIVER_A);*/
		 }
}

/*

EXPRESSIONS_LIST -> EXPRESSION  EXPRESSIONS_LIST_A
EXPRESSIONS_LIST_A ->, EXPRESSIONS_LIST
EXPRESSIONS_LIST_A -> ↋

*/
void parseExpressionsList() 
{
	fprintf(fwParser, "Rule: EXPRESSIONS_LIST-> EXPRESSION EXPRESSIONS_LIST_A   \n");
	parseExpression();
	parseExpressionsListA();

}

// nulable no need recover

void parseExpressionsListA() // EXPRESSIONS_LIST_A ----- nullable
{
	     cur_token = next_token();
	  	 switch (cur_token->kind)
		 {
		 case TOKEN_COMMA:
			 fprintf(fwParser, "Rule: EXPRESSIONS_LIST_A -> , EXPRESSIONS_LIST  \n");
			  parseExpressionsList();
			   break;
		
		 case TOKEN_RIGHT_BRACKET:
			 fprintf(fwParser, "Rule: EXPRESSIONS_LIST_A -> epsilon  \n");
			 cur_token =back_token();
			 break;

		 default:
			/* fprintf(fwParser, "Rule: EXPRESSIONS_LIST_A -> epsilon  \n");
			 cur_token =back_token();*/
			 handleParsingErrorVar(EXPRESSIONS_LIST_A);
		     errorRecovery(EXPRESSIONS_LIST_A);
			 break;

		 }


}


/*
EXPRESSION -> BASIC_EXPRESSION   EXPRESSION_A
EXPRESSION_A -> ↋
EXPRESSION_A -> ar_op BASIC_EXPRESSION   
*/


void parseExpression()
{
	fprintf(fwParser, "Rule: EXPRESSION -> BASIC_EXPRESSION   EXPRESSION_A    \n");
	 parseBasicExpression();
	 //cur_token = next_token();
	 parseExpressionA();

}

// nulable no need recover

void parseExpressionA()
{
	   cur_token = next_token();
	  	 switch (cur_token->kind)
		 {
		 case TOKEN_AR_OP:
			 fprintf(fwParser, "Rule: EXPRESSION_A -> ar_op BASIC_EXPRESSION     \n");
			  parseBasicExpression();
			  break;

   
	
		 case TOKEN_RIGHT_BRACKET:
		 case TOKEN_COMMA:
		 case TOKEN_DO:
		 case TOKEN_END_CYCLE:
		 case TOKEN_OTHERWISE:
		 case TOKEN_END:
		 case TOKEN_DONE:
		 case TOKEN_UNTIL:
		 case TOKEN_RIGHT_CURLY_BRACES :
		  case TOKEN_SEMICOLON:
			 fprintf(fwParser, "Rule: EXPRESSION_A ->epsilon   \n");
			 cur_token =back_token();  
			 break;

		default:
			/*fprintf(fwParser, "Rule: EXPRESSION_A -> epsilon  \n");
			 cur_token =back_token();  */
	    handleParsingErrorVar(EXPRESSION_A);
		errorRecovery(EXPRESSION_A);
		break;
		 }
}



/* 

BASIC_EXPRESSION ->id  BASIC_EXPRESSION_A | NUMBER
BASIC_EXPRESSION_A  ->↋
BASIC_EXPRESSION_A  -> [EXPRESSIONS_LIST]
*/


void parseBasicExpression()
{
	   cur_token = next_token();
	  	 switch (cur_token->kind)
		 {
		 case TOKEN_ID:
			 fprintf(fwParser, "Rule: BASIC_EXPRESSION ->id  BASIC_EXPRESSION_A    \n");
			// cur_token= back_token();
			  parseBasicExpressionA();
			  break;

    //         case TOKEN_RIGHT_BRACKET:
			 //  //fprintf(fwParser, "Rule: BASIC_EXPRESSION -> NUMBER  \n");
			 //   cur_token= back_token(); 
				//break;


		 //case TOKEN_INT_NUM:
		 //case TOKEN_REAL_NUM:
			// fprintf(fwParser, "BASIC_EXPRESSION -> NUMBER  \n");
			// cur_token= back_token(); // for COMMAND-> RECEIVER := EXPRESSION 
			// parseNumber();
			//// cur_token= back_token();
			// break;
         default:
	      	 fprintf(fwParser, "Rule: BASIC_EXPRESSION -> NUMBER  \n");
			 cur_token= back_token(); // for COMMAND-> RECEIVER := EXPRESSION 
			 parseNumber();
			break;
		 }

}

/*
BASIC_EXPRESSION_A  ->↋
BASIC_EXPRESSION_A  -> [EXPRESSIONS_LIST]
*/

// nulable no need recover

void parseBasicExpressionA() // NULLABLE
{
	cur_token = next_token();
	switch (cur_token->kind)
		 {
		 case TOKEN_LEFT_BRACKET:
			  
			 fprintf(fwParser, "Rule: BASIC_EXPRESSION_A  -> [EXPRESSIONS_LIST]\n");
			 parseExpressionsList();
			 if(!match(TOKEN_RIGHT_BRACKET,BASIC_EXPRESSION_A))return;
			 break;

			 //nullable
		 case TOKEN_COMMA:
         case TOKEN_RIGHT_BRACKET:
		 case TOKEN_DO:
		 case TOKEN_END_CYCLE:
		 case TOKEN_OTHERWISE:
		 case TOKEN_END:
		 case TOKEN_DONE:
		 case TOKEN_UNTIL:
		 case TOKEN_RIGHT_CURLY_BRACES :
		 case TOKEN_SEMICOLON:
		 case TOKEN_AR_OP: 
			  fprintf(fwParser, "Rule: BASIC_EXPRESSION_A  ->epsilon \n");
		      cur_token = back_token();
			  break;


          default: 
			/*  fprintf(fwParser, "Rule: BASIC_EXPRESSION_A  ->epsilon \n");
			  cur_token = back_token();*/
			handleParsingErrorVar(BASIC_EXPRESSION_A);
		    errorRecovery(BASIC_EXPRESSION_A);
			break;
	}

}





// do number call number



//have recovery

void parseNumber()
{

	cur_token = next_token();

	

		 switch (cur_token->kind) 
				 {
				 case TOKEN_INT_NUM:
					 fprintf(fwParser, "Rule: NUMBER-> int_num \n");
					 break;
				 case TOKEN_REAL_NUM:
					 fprintf(fwParser, "Rule: NUMBER-> real_num \n");
					 break;
				default:
						handleParsingErrorVar(NUMBER);
						errorRecovery(NUMBER);
						break;
				 }
}


  


void parseCondition()
{
	fprintf (fwParser,"Rule:CONDITION -> id  rel_op  EXPRESSION  \n");
	if(!match(TOKEN_ID, CONDITION)) return;
	if(!match(TOKEN_REAL_OP, CONDITION)) return;
	parseExpression();
	

}

  //  \/\*(.*\n)*.*\*   {line++;}     fix eroer test 2

// call IfFollow

// recovery

void errorRecovery(int Rule) 
{

	while(IfFollow(Rule) == 0)
	{
		cur_token =next_token();
	}

	 cur_token =back_token();
	 
}

// if EOF exit(0)
// arr_rule

int  IfFollow(int rule)
{
	int followTokensSize = arr_rule[rule-1].followTotalSize;
	int i=0;
	

	for(i=0;i<followTokensSize;i++)
	{
		if(cur_token->kind == TOKEN_EOF)
			 exit(0);  //  return 1; 	
		if(cur_token->kind == arr_rule[rule-1].followTokens[i])
			return 1;
	}
	
	return 0;

}


 // call  handleParsingErrorTok(tokenId); errorRecovery(Rule);
			

int match(int tokenId , int Rule)
{
	cur_token=next_token();
	if(cur_token->kind == tokenId)
		return 1;
	else
	{
		    handleParsingErrorTok(tokenId);
			errorRecovery(Rule);

	}
	return 0;

}

// parseingError print  

void handleParsingErrorVar(int Rule)
{
	int i;

	char* str = (char*)malloc(sizeof(char)* arr_rule[Rule-1].firstTotalSize *30);
	str[0] = '\0';
	strcat(str, TOKEN_STRING[arr_rule[Rule-1].firstTokens[0]-1]);
	for (i=1; i< arr_rule[Rule-1].firstTotalSize; i++) 
	{
		strcat(str, " or ");
		strcat(str, TOKEN_STRING[arr_rule[Rule-1].firstTokens[i]-1]);
	}


	fprintf(fwParser, "Expected one of tokens %s ,  at line:  %d \n", str, cur_token->lineNumber );
	fprintf(fwParser, " Actual token %s', lexeme: %s \n", TOKEN_STRING[cur_token->kind -1] , cur_token->lexeme );
}



// errortok print


void handleParsingErrorTok(int token_ex)
{
	fprintf(fwParser,"Expected token '%s' at line: %d \n", TOKEN_STRING[token_ex-1], cur_token->lineNumber );
	fprintf(fwParser,"Actual token '%s',  lexeme:  '%s' \n" ,TOKEN_STRING[ cur_token->kind -1 ], cur_token->lexeme );
}



// init First
void First(int NumOfRule,int token_first)

{    static int IndFirst;
	if(arr_rule[NumOfRule-1].firstTokens == NULL)
	   IndFirst=0;
	else 
		IndFirst++;

	  arr_rule[NumOfRule-1].firstTokens=(int*)realloc(arr_rule[NumOfRule-1].firstTokens,(IndFirst+1)*sizeof(int));
		arr_rule[NumOfRule-1].firstTokens[IndFirst]=token_first;
		arr_rule[NumOfRule-1].firstTotalSize= IndFirst+1;
	
}


//init follow

void Follow(int NumOfRule,int token_follow)
{

	 static int IndFollow;
	if(arr_rule[NumOfRule-1].followTokens == NULL)
	   IndFollow=0;
	else 
		IndFollow++;

	    arr_rule[NumOfRule-1].followTokens=(int*)realloc(arr_rule[NumOfRule-1].followTokens,(IndFollow+1)*sizeof(int));
		arr_rule[NumOfRule-1].followTokens[IndFollow]=token_follow;
		arr_rule[NumOfRule-1].followTotalSize= IndFollow+1;

}






// init all parser  first and follow

void initParser()
{

 int NumOfRules=24;
 int i;
 arr_rule= (Rule*)malloc(sizeof(Rule)*NumOfRules); // 2D

 // all NULL
 for(i=0;i<NumOfRules;i++)
 {
	 arr_rule[i].firstTokens=NULL;
	 arr_rule[i].followTokens=NULL;
 }

 // all first follow
  
    First(PROGRAM,TOKEN_PROGRAM);
	Follow(PROGRAM,TOKEN_EOF);
	arr_rule[PROGRAM-1].nullable=0;


    First(DEFINITIONS,TOKEN_ID);
	Follow(DEFINITIONS,TOKEN_START);
	arr_rule[DEFINITIONS-1].nullable=0;


	First(DEFINITIONS_A,TOKEN_COMMA);
	Follow(DEFINITIONS_A,TOKEN_START);
	arr_rule[DEFINITIONS_A-1].nullable=1;

	First(DEFINITION,TOKEN_ID);
	Follow(DEFINITION,TOKEN_START);
	Follow(DEFINITION,TOKEN_COMMA);
	arr_rule[DEFINITION-1].nullable=0;

	First(DEFINITION_A,TOKEN_COLON);
	First(DEFINITION_A,TOKEN_LEFT_BRACKET);
	Follow(DEFINITION_A,TOKEN_START);
	Follow(DEFINITION_A,TOKEN_COMMA);
	arr_rule[DEFINITION_A-1].nullable=0;


	First(DEFINITION_A_1,TOKEN_REAL);
	First(DEFINITION_A_1,TOKEN_INTEGER);
	First(DEFINITION_A_1,TOKEN_EXCCPTION);
	Follow(DEFINITION_A_1,TOKEN_START);
	Follow(DEFINITION_A_1,TOKEN_COMMA);
	arr_rule[DEFINITION_A_1-1].nullable=0;


	First(DEFINITION_A_2,TOKEN_CONST);
	Follow(DEFINITION_A_2,TOKEN_START);
	Follow(DEFINITION_A_2,TOKEN_COMMA);
	arr_rule[DEFINITION_A_2-1].nullable=1;

	First(TYPE,TOKEN_REAL );
	First(TYPE,TOKEN_INTEGER);
	Follow(TYPE,TOKEN_START);
	Follow(TYPE,TOKEN_COMMA);
	Follow(TYPE,TOKEN_CONST);
	arr_rule[DEFINITION_A_2-1].nullable=0;

	First(DIMENSIONS_LIST,TOKEN_INT_NUM );
	First(DIMENSIONS_LIST,TOKEN_ID);
	Follow(DIMENSIONS_LIST,TOKEN_RIGHT_BRACKET);
	arr_rule[DIMENSIONS_LIST-1].nullable=0;

	First(DIMENSIONS_LIST_A,TOKEN_COMMA);
	Follow(DIMENSIONS_LIST_A,TOKEN_RIGHT_BRACKET);
	arr_rule[DIMENSIONS_LIST-1].nullable=1;


	First(SIZE,TOKEN_INT_NUM );
	First(SIZE,TOKEN_ID);
	Follow(SIZE,TOKEN_RIGHT_BRACKET);
	Follow(SIZE,TOKEN_COMMA);
	arr_rule[SIZE-1].nullable=0;


	First(COMMANDS,TOKEN_ID );
	First(COMMANDS,TOKEN_WHEN);
	First(COMMANDS,TOKEN_CYCLE );
	First(COMMANDS,TOKEN_LEFT_CURLY_BRACES);
	First(COMMANDS,TOKEN_RAISE);
	Follow(COMMANDS,TOKEN_END);
	Follow(COMMANDS,TOKEN_OTHERWISE);
	Follow(COMMANDS,TOKEN_DONE);
	Follow(COMMANDS,TOKEN_UNTIL);
	Follow(COMMANDS,TOKEN_RIGHT_CURLY_BRACES);
	arr_rule[COMMANDS-1].nullable=0;

	First(COMMANDS_A ,TOKEN_SEMICOLON);
	Follow(COMMANDS_A,TOKEN_END);
	Follow(COMMANDS_A,TOKEN_OTHERWISE);
	Follow(COMMANDS_A,TOKEN_DONE);
	Follow(COMMANDS_A,TOKEN_UNTIL);
	Follow(COMMANDS_A,TOKEN_RIGHT_CURLY_BRACES);
	arr_rule[COMMANDS_A-1].nullable=1;

	First(COMMAND,TOKEN_ID );
	First(COMMAND,TOKEN_WHEN);
	First(COMMAND,TOKEN_CYCLE );
	First(COMMAND,TOKEN_LEFT_CURLY_BRACES);
	First(COMMAND,TOKEN_RAISE);
	Follow(COMMAND,TOKEN_END);
	Follow(COMMAND,TOKEN_OTHERWISE);
	Follow(COMMAND,TOKEN_DONE);
	Follow(COMMAND,TOKEN_UNTIL);
	Follow(COMMAND,TOKEN_RIGHT_CURLY_BRACES);
	Follow(COMMAND,TOKEN_SEMICOLON);
	arr_rule[COMMAND-1].nullable=0;



	First(RECEIVER,TOKEN_ID);
	Follow(RECEIVER,TOKEN_ASSIGNMENT);
	arr_rule[RECEIVER-1].nullable=0;

	First(RECEIVER_A ,TOKEN_LEFT_BRACKET);
	Follow(RECEIVER_A ,TOKEN_ASSIGNMENT);
	arr_rule[RECEIVER_A-1].nullable=1;



	First(EXPRESSIONS_LIST ,TOKEN_ID);
	First(EXPRESSIONS_LIST ,TOKEN_INT_NUM);
	First(EXPRESSIONS_LIST ,TOKEN_REAL_NUM);
	Follow(EXPRESSIONS_LIST ,TOKEN_RIGHT_BRACKET);
	arr_rule[EXPRESSIONS_LIST-1].nullable=0;

	First(EXPRESSIONS_LIST_A ,TOKEN_COMMA);
	Follow(EXPRESSIONS_LIST_A ,TOKEN_RIGHT_BRACKET);
	arr_rule[EXPRESSIONS_LIST_A-1].nullable=1;


	First(EXPRESSION ,TOKEN_ID);
	First(EXPRESSION ,TOKEN_INT_NUM);
	First(EXPRESSION ,TOKEN_REAL_NUM);
	First(EXPRESSION ,TOKEN_AR_OP);
	Follow(EXPRESSION ,TOKEN_RIGHT_BRACKET);
	Follow(EXPRESSION ,TOKEN_COMMA);
	Follow(EXPRESSION ,TOKEN_DO);
	Follow(EXPRESSION ,TOKEN_END_CYCLE);
	Follow(EXPRESSION ,TOKEN_END);
	Follow(EXPRESSION ,TOKEN_OTHERWISE);
	Follow(EXPRESSION ,TOKEN_DONE);
	Follow(EXPRESSION ,TOKEN_UNTIL);
	Follow(EXPRESSION ,TOKEN_RIGHT_CURLY_BRACES);
	Follow(EXPRESSION ,TOKEN_SEMICOLON);
	arr_rule[EXPRESSION-1].nullable=0;
	//TOKEN_RIGHT_BRACKET


	First(EXPRESSION_A ,TOKEN_AR_OP);
	Follow(EXPRESSION_A ,TOKEN_RIGHT_BRACKET);
	Follow(EXPRESSION_A ,TOKEN_COMMA);
	Follow(EXPRESSION_A ,TOKEN_DO);
	Follow(EXPRESSION_A,TOKEN_END_CYCLE);
	Follow(EXPRESSION_A ,TOKEN_END);
	Follow(EXPRESSION_A ,TOKEN_OTHERWISE);
	Follow(EXPRESSION_A ,TOKEN_DONE);
	Follow(EXPRESSION_A ,TOKEN_UNTIL);
	Follow(EXPRESSION_A ,TOKEN_RIGHT_CURLY_BRACES);
	Follow(EXPRESSION_A ,TOKEN_SEMICOLON);
	arr_rule[EXPRESSION_A-1].nullable=1;
	//


	First(BASIC_EXPRESSION,TOKEN_ID);
	First(BASIC_EXPRESSION ,TOKEN_INT_NUM);
	First(BASIC_EXPRESSION ,TOKEN_REAL_NUM);
	Follow(BASIC_EXPRESSION ,TOKEN_RIGHT_BRACKET);
	Follow(BASIC_EXPRESSION ,TOKEN_COMMA);
	Follow(BASIC_EXPRESSION ,TOKEN_DO);
	Follow(BASIC_EXPRESSION,TOKEN_END_CYCLE);
	Follow(BASIC_EXPRESSION ,TOKEN_END);
	Follow(BASIC_EXPRESSION ,TOKEN_OTHERWISE);
	Follow(BASIC_EXPRESSION ,TOKEN_DONE);
	Follow(BASIC_EXPRESSION ,TOKEN_UNTIL);
	Follow(BASIC_EXPRESSION ,TOKEN_RIGHT_CURLY_BRACES);
	Follow(BASIC_EXPRESSION ,TOKEN_SEMICOLON);
	Follow(BASIC_EXPRESSION ,TOKEN_AR_OP);
	arr_rule[BASIC_EXPRESSION-1].nullable=0;

	//
	First(BASIC_EXPRESSION_A,TOKEN_LEFT_BRACKET);
	Follow(BASIC_EXPRESSION_A,TOKEN_RIGHT_BRACKET);
	Follow(BASIC_EXPRESSION_A ,TOKEN_COMMA);
	Follow(BASIC_EXPRESSION_A ,TOKEN_DO);
	Follow(BASIC_EXPRESSION_A,TOKEN_END_CYCLE);
	Follow(BASIC_EXPRESSION_A ,TOKEN_END);
	Follow(BASIC_EXPRESSION_A ,TOKEN_OTHERWISE);
	Follow(BASIC_EXPRESSION_A ,TOKEN_DONE);
	Follow(BASIC_EXPRESSION_A ,TOKEN_UNTIL);
	Follow(BASIC_EXPRESSION_A,TOKEN_RIGHT_CURLY_BRACES);
	Follow(BASIC_EXPRESSION_A ,TOKEN_SEMICOLON);
	Follow(BASIC_EXPRESSION_A,TOKEN_AR_OP);
	arr_rule[BASIC_EXPRESSION_A-1].nullable=1;
	//

	First(NUMBER ,TOKEN_INT_NUM);
	First(NUMBER ,TOKEN_REAL_NUM);
	Follow(NUMBER ,TOKEN_COMMA);
	Follow(NUMBER ,TOKEN_DO);
	Follow(NUMBER,TOKEN_END_CYCLE);
	Follow(NUMBER,TOKEN_END);
	Follow(NUMBER ,TOKEN_OTHERWISE);
	Follow(NUMBER ,TOKEN_DONE);
	Follow(NUMBER ,TOKEN_UNTIL);
	Follow(NUMBER,TOKEN_RIGHT_CURLY_BRACES);
	Follow(NUMBER ,TOKEN_SEMICOLON);
	Follow(NUMBER,TOKEN_AR_OP);
	Follow(NUMBER,TOKEN_START);
	Follow(NUMBER ,TOKEN_RIGHT_BRACKET);
	arr_rule[NUMBER-1].nullable=0;

	

	First(CONDITION ,TOKEN_ID);
	Follow(CONDITION,TOKEN_DO);
	Follow(CONDITION,TOKEN_END_CYCLE);
	arr_rule[CONDITION-1].nullable=0;




}

