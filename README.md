# Compilation

///////////////////////////////////////////////////////////////////////////////
instructions

put the test files ---test1 and test2---   in C:\temp 

 run 20478667_039843271.exe file 
 you wiil see the result in C:\temp 
 
///////////////////////////////////////////////////////////



Goal of Assignment : to develop parser (syntax analyzer) for this language. 
This assignment is an incremental step in the project development: it is based on what was developed in Assignment 1. 



 --------Lexical Analysis -------

Firts  creating tokens bye using Flex 
Syntax of a mini programming language is described by the following grammar 


PROGRAM -> program DEFINITIONS start COMMANDS end

DEFINITIONS ->  DEFINITION | DEFINITIONS, DEFINITION
DEFINITION -> id : TYPE 
                               |  id [DIMENSIONS_LIST] : TYPE const := NUMBER 
                               |  id : TYPE const := NUMBER 
                               |  id : exception

TYPE ->  real  |  integer
DIMENSIONS_LIST ->  DIMENSIONS_LIST, SIZE  |  SIZE
SIZE ->  int_num | id

COMMANDS ->  COMMAND | COMMAND; COMMANDS
COMMAND ->   RECEIVER := EXPRESSION
  
                          | when CONDITION do COMMANDS otherwise COMMANDS done 
 
                          | cycle COMMANDS until CONDITION end_cycle
 
                          | { DEFINITIONS start COMMANDS }
                                     | 
                          |raise id
                              
RECEIVER ->  id  |  id[EXPRESSIONS_LIST]  
EXPRESSIONS_LIST -> EXPRESSION | EXPRESSION , EXPRESSIONS_LIST

EXPRESSION ->  BASIC_EXPRESSION  | 
                              BASIC_EXPRESSION ar_op BASIC_EXPRESSION  
BASIC_EXPRESSION ->  NUMBER  |  id  |  id[EXPRESSIONS_LIST] 

NUMBER ->  int_num | real_num

CONDITION ->  id  rel_op  EXPRESSION  


---------------------- Syntactic Analysis  --------------------

Goal of Assignment 2: to develop parser (syntax analyzer) for this language. 
This assignment is an incremental step in the project development: it is based on what was developed in Lexical Analysis . 






