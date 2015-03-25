  /* definitions */

  /* keyword   void|int|double|bool|string|class|interface|null|this|extends|implements|for|while|if|else|return|break|New|NewArray|Print|ReadInteger|ReadLine
   */

%{

#include <iostream>

using namespace std;

#include "tokentype.h"

string resultString;
int lineNo;
Token* myTok;

int error(string msg, int line)
{
  cout << msg << " on line " << line << endl;
  return -1;
}

TokenType makeToken(TokenType type) {
    myTok = new Token(type, yytext, yylineno);
    return type;
}


%}

%option yylineno
%x STRING
%x COMMENT
%x BLOCK
%x DOUBLE

%%

  /* =================== rules ===================== */

  /* other */

\+ { return makeToken(Y_Plus); }
\- { return makeToken(Y_Minus); }
\* { return makeToken(Y_Times); }
\/ { return makeToken(Y_Div); }
\% { return makeToken(Y_Mod); }
\< { return makeToken(Y_Less); }
\<\= { return makeToken(Y_LessEqual); }
\> { return makeToken(Y_Greater); }
\>\= { return makeToken(Y_GreaterEqual); }
\= { return makeToken(Y_Assign); }
\=\= { return makeToken(Y_Equal); }
\!\= { return makeToken(Y_NotEqual); }
\&\& { return makeToken(Y_And); }
\|\| { return makeToken(Y_Or); }
\! { return makeToken(Y_Not); }
\; { return makeToken(Y_Semicolon); }
\, { return makeToken(Y_Comma); }
\. { return makeToken(Y_Dot); }
\[ { return makeToken(Y_LBracket); }
\] { return makeToken(Y_RBracket); }
\( { return makeToken(Y_LParen); }
\) { return makeToken(Y_RParen); }
\{ { return makeToken(Y_LBrace); }
\} { return makeToken(Y_RBrace); }

  /* keywords */

void  		{ return makeToken(Y_Void); }
int 		{ return makeToken(Y_Int); }
double 		{ return makeToken(Y_Double); }
bool 		{ return makeToken(Y_Bool); }
string		{ return makeToken(Y_String); }
class 		{ return makeToken(Y_Class); }
interface  	{ return makeToken(Y_Interface); }
null		{ return makeToken(Y_Null); }
this  		{ return makeToken(Y_This); }
extends   	{ return makeToken(Y_Extends); }
implements	{ return makeToken(Y_Implements); }
for   		{ return makeToken(Y_For); }
while   	{ return makeToken(Y_While); }
if   		{ return makeToken(Y_If); }
else   		{ return makeToken(Y_Else); }
return  	{ return makeToken(Y_Return); }
break   	{ return makeToken(Y_Break); }
New   		{ return makeToken(Y_New); }
NewArray 	{ return makeToken(Y_NewArray); }
Print   	{ return makeToken(Y_Print); }
ReadInteger	{ return makeToken(Y_ReadInteger); }
ReadLine 	{ return makeToken(Y_ReadLine); }

  /* bools */

true  							{ return makeToken(Y_BoolConstant); }
false  							{ return makeToken(Y_BoolConstant); }


  /* ignore whitespace | [[:space:]] */

  /* identifier */
[A-Za-z][A-Za-z0-9_]* 		{ 
								resultString = "";
								resultString += yytext;
								if(resultString.length() > 31){
									return error("identifier \"" + resultString + "\" too long", yylineno); 
								}
								return makeToken(Y_Identifier); 
								
							}
								


  /* ints */
[0-9]+ 							{ return makeToken(Y_IntConstant); }
0[Xx][0-9A-Fa-f]+ 				{ return makeToken(Y_IntConstant); }

  /* doubles */
  
[0-9]+\.[0-9]*[Ee][+-]?[0-9]+ 	{ return makeToken(Y_DoubleConstant); } 

[0-9]+\.[0-9]* 					{ return makeToken(Y_DoubleConstant); } 





  /* string */
  /* \"(.|\\.)*\"  { return makeToken(Y_StringConstant); }  */

\n {}

\" { BEGIN(STRING); resultString = "\""; }
<STRING>[^\n"]* { resultString += yytext; }
<STRING>\n      {return error("missing \" at end of string constant", 
		yylineno-1); }
<STRING><<EOF>>  {return error("missing \" at end of string constant", 
		yylineno); } 
<STRING>\"     { BEGIN(INITIAL); 
	         myTok = new Token(Y_StringConstant,resultString + "\"", 
                                  yylineno);
		 return Y_StringConstant; }

  /* comments */
  
\/\/ { BEGIN(COMMENT); resultString = ""; }
<COMMENT>[^\n]* { resultString += yytext; }
<COMMENT><<EOF>> { return error("missing new line character before EOF (how does this even happen?)",
		 yylineno); }
<COMMENT>\n  	 { BEGIN(INITIAL);}

\/\* { BEGIN(BLOCK); resultString = ""; lineNo = yylineno; }
<BLOCK>[^*/]* { resultString += yytext; }
<BLOCK><<EOF>> { return error("missing */ at end of comment block", lineNo); }
<BLOCK>\*\/  	 { BEGIN(INITIAL);}

[^ \t\n] { resultString = "stray '"; resultString += yytext; resultString += "'"; return error(resultString, yylineno); }
[ \t\n] {}
                  
<<EOF>> { return -1; }

%%

  /* subroutines */

int yywrap(void) {
    return 1;  // makes it stop at EOF.
} 

int main(int argc, char **argv) {
    int tok;
    /* Make sure there's a given file name */
    if (argc != 2) {
        cout << "USAGE: " << argv[0] << " FILE" << endl;
        exit(1);
    }       
    yyin = fopen(argv[1], "r");
    /* and that it exists and can be read */
    if (!yyin) {
        cout << argv[1] << ": No such file or file can't be opened for reading." 
             << endl;
        exit(1);
    }
    /* Read tokens until finished */
    while ((tok=yylex()) != -1)
        myTok->print();
}
