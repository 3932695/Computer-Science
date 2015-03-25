#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 55 "decaf.y"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "tokentype.h"
#include "parsetree.h"




  /* we are building parse trees */
#define YYSTYPE ParseTree *


using namespace std;


void PUSH(){
	opstack.push(myTok);
}


Token* POP(){
	Token *result = opstack.top();
	opstack.pop();
	return result;
}


#line 53 "y.tab.c"
#define Y_Void 257
#define Y_Int 258
#define Y_Double 259
#define Y_Bool 260
#define Y_String 261
#define Y_Class 262
#define Y_Interface 263
#define Y_Null 264
#define Y_This 265
#define Y_Extends 266
#define Y_Implements 267
#define Y_For 268
#define Y_While 269
#define Y_If 270
#define Y_Else 271
#define Y_Return 272
#define Y_Break 273
#define Y_New 274
#define Y_NewArray 275
#define Y_Print 276
#define Y_ReadInteger 277
#define Y_ReadLine 278
#define Y_Identifier 279
#define Y_TypeIdentifier 280
#define Y_IntConstant 281
#define Y_BoolConstant 282
#define Y_DoubleConstant 283
#define Y_StringConstant 284
#define Y_Plus 285
#define Y_Minus 286
#define Y_Times 287
#define Y_Div 288
#define Y_Mod 289
#define Y_Less 290
#define Y_LessEqual 291
#define Y_Greater 292
#define Y_GreaterEqual 293
#define Y_Assign 294
#define Y_Equal 295
#define Y_NotEqual 296
#define Y_And 297
#define Y_Or 298
#define Y_Not 299
#define Y_Semicolon 300
#define Y_Comma 301
#define Y_Dot 302
#define Y_LBracket 303
#define Y_RBracket 304
#define Y_LParen 305
#define Y_RParen 306
#define Y_LBrace 307
#define Y_RBrace 308
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    2,    8,    6,    9,
    9,   10,   10,   11,   11,   15,   15,   16,   16,    3,
   12,   12,   12,   12,   12,   12,    4,    4,   18,    5,
   22,   19,   19,   24,   20,   20,   21,   21,   25,   25,
   26,   26,   23,   23,   13,   13,   13,   17,   27,   27,
   28,   28,   32,   30,   34,   33,   29,   29,   38,   38,
   38,   38,   38,   36,   36,   36,   36,   37,   37,   37,
   47,   46,   50,   49,   52,   51,   53,   40,   41,   42,
   43,   43,   44,   45,   54,   54,   54,   54,   31,   31,
   48,   56,   48,   48,   48,   48,   58,   48,   59,   48,
   60,   48,   61,   48,   62,   48,   63,   48,   64,   48,
   65,   48,   66,   48,   67,   48,   68,   48,   69,   48,
   70,   48,   48,   71,   48,   72,   48,   73,   48,   74,
   48,   75,   48,   76,   48,   55,   55,   55,   77,   57,
   57,   78,   78,   35,   35,    7,   14,   39,
};
short yylen[] = {                                         2,
    1,    2,    1,    2,    1,    1,    1,    0,    6,    1,
    0,    2,    1,    6,    6,    1,    0,    3,    2,    2,
    1,    1,    1,    1,    1,    3,    6,    6,    0,    8,
    0,    3,    0,    0,    3,    0,    1,    0,    2,    1,
    2,    1,    3,    1,    3,    1,    0,    4,    1,    0,
    2,    1,    0,    4,    0,    6,    1,    1,    2,    2,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    0,    5,    0,    5,    0,    9,    3,    2,    2,    2,
    2,    2,    2,    2,    1,    1,    1,    1,    1,    0,
    1,    0,    4,    1,    1,    1,    0,    4,    0,    4,
    0,    4,    0,    4,    0,    4,    0,    4,    0,    4,
    0,    4,    0,    4,    0,    4,    0,    4,    0,    4,
    0,    4,    3,    0,    3,    0,    3,    0,    4,    0,
    4,    0,    5,    0,    7,    1,    1,    4,    3,    4,
    4,    1,    0,    3,    1,    1,    1,    1,
};
short yydefred[] = {                                      0,
  147,   21,   22,   23,   24,   29,    8,   25,    0,    0,
    3,    0,    5,    6,    7,    0,    0,    0,    0,    2,
    4,  146,    0,    0,    0,    0,    0,   26,    0,    0,
   31,    0,    0,   46,    0,    0,    0,    0,   34,    0,
    0,    0,   13,    0,    0,   20,    0,    0,    0,   32,
    0,    0,    9,   12,    0,    0,    0,   27,   45,   28,
   44,    0,    0,   42,    0,    0,   40,    0,    0,    0,
    0,    0,    0,   41,   30,   39,    0,    0,   19,   95,
   75,   73,   71,   53,  148,  132,  134,   55,  128,  130,
   85,   87,   86,   88,  124,  126,    0,    0,   63,    0,
    0,   52,   61,    0,   62,   57,   58,   64,    0,   65,
   66,   67,   68,   69,   70,    0,    0,    0,    0,    0,
   91,    0,   96,    0,    0,   43,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   48,   51,   60,   59,   81,    0,  111,  115,  113,
  117,  119,  121,  107,  109,   97,   99,  101,  103,  105,
    0,    0,   79,   83,   80,   84,   78,   82,   92,    0,
   18,   14,   15,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  123,    0,    0,    0,   77,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  139,    0,    0,    0,    0,    0,   54,
    0,    0,    0,  129,  131,    0,  141,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  138,    0,  140,    0,   74,   72,  133,    0,    0,    0,
    0,    0,   56,    0,  135,    0,   76,
};
short yydgoto[] = {                                       9,
   10,   11,   34,   13,   14,   15,   98,   19,   41,   42,
   43,   35,   36,   17,   71,   72,   99,   18,   32,   40,
   65,   38,   62,   51,   66,   67,  100,  101,  102,  103,
  104,  132,  105,  135,  186,  106,  107,  108,  109,  110,
  111,  112,  113,  114,  115,  116,  131,  117,  118,  130,
  119,  129,  120,  121,  122,  205,  123,  198,  199,  200,
  201,  202,  196,  197,  190,  192,  191,  193,  194,  195,
  138,  139,  136,  137,  133,  134,  124,  188,
};
short yysindex[] = {                                     50,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   50,
    0,  -31,    0,    0,    0,  -90, -250, -250, -250,    0,
    0,    0,  -53,    9,   10, -208,  -57,    0,  -48,  -48,
    0, -191, -108,    0,  -90,   18,  117, -250,    0,  -35,
  -14, -108,    0,  -90, -250,    0,  -13,  -48,  -13,    0,
 -250, -108,    0,    0,   77,   79,  -48,    0,    0,    0,
    0,   82,   69,    0,   11, -108,    0,  -48,  -48,   76,
  606,  -48, -250,    0,    0,    0,  143,  165,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  330,  114,    0,   12,
  606,    0,    0,  103,    0,    0,    0,    0,  108,    0,
    0,    0,    0,    0,    0,  606,  337,  606,  606,  606,
    0,   95,    0,  133,  115,    0,  127,  132,  138,  142,
  152,  330,  162,  167,  175,  177,  183,  330,  330,   97,
  330,    0,    0,    0,    0,    0,  -73,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  330, -250,    0,    0,    0,    0,    0,    0,    0,  330,
    0,    0,    0,  330,  330,  330,  182, -250,  330,  330,
  193,  206,  361,  -34,    0,  180,  337,  216,    0,  330,
  330,  330,  330,  330,  330,  330,  330,  330,  330,  330,
  330,  330,  123,    0,  330,  221,  205,  134,  158,    0,
  222,  184,  178,    0,    0,  330,    0,  607,  607,  511,
  511,  423,  397,  607,  607,  361,  361,  -34,  -34,  -34,
    0,  337,    0,  330,    0,    0,    0,  -48,  207,  337,
  244,  -38,    0,  330,    0,  232,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  274,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  217,    0, -121,    0,    0,  199,  199,
    0,  154,  153,    0,    0,    0,    0,    0,    0,    0,
    0,  155,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  157,    0,    0,    0,    0,  541,    0,    0,    0,
    0,  156,    0,    0,    0,  159,    0,  199,  199,    0,
  -32,  561,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -37,    0,    0,
  -28,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  224,  -27,  224,  224,  224,
    0,    1,    0,  -26,    0,    0,    0,    0,    0,    0,
    0,  224,    0,    0,    0,    0,    0,    0,    0,    0,
  247,    0,    0,    0,    0,    0,  586,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  247,
    0,    0,    0,  224,    0,    0,    0,    0,    0,    0,
    0,    0,  450,   27,    0,  252,  204,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  209,  345,  104,
  149,  192,  472,  365,  404,  458,  485,   36,   62,   71,
    0,  528,    0,    0,    0,    0,    0,    0,    0,  211,
    0,    0,    0,  259,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,  291,   75,  -15,    0,    0,  545,    0,    0,    0,
  272,  295,   22,   -3,    0,    0,   35,    0,    0,    0,
    0,    0,    0,    0,    0,  249,    0,    0,  -75,    0,
 -119,    0,    0,    0,  136,  119,  -18,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  753,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  147,
};
#define YYTABLESIZE 987
short yytable[] = {                                     136,
   23,   33,  245,  136,  136,  136,  136,  136,  136,  136,
  137,  162,  177,   89,  137,  137,  137,  137,  137,  137,
  137,  136,  136,  136,  136,  143,   90,   21,   22,   45,
   90,   89,  137,  137,  137,  137,   64,   94,   45,   28,
  146,   94,   94,   94,   94,   94,   94,   94,   29,   30,
   64,   37,   23,  136,  207,  136,  161,   31,   47,   94,
   94,   48,   94,  127,  137,   33,  137,  127,  127,  127,
  127,  127,  102,  127,   12,   39,  102,  102,  102,  102,
  102,   58,  102,   60,   12,  127,  127,   52,  127,   77,
   78,   94,   50,   94,  102,  102,   49,  102,  104,  164,
  166,  168,  104,  104,  104,  104,  104,  106,  104,   57,
   53,  106,  106,  106,  106,  106,   68,  106,   69,  127,
  104,  104,   59,  104,  246,   73,   63,   74,  102,  106,
  106,   70,  106,  160,   79,   75,  142,  185,  158,  156,
   63,  157,  162,  159,  114,   33,  125,  114,    1,    2,
    3,    4,    5,  141,  104,  169,  154,   49,  155,  160,
   48,  144,  114,  106,  158,  156,  145,  157,  162,  159,
  160,    8,  170,  171,  235,  158,  156,  174,  157,  162,
  159,  175,  154,  127,  155,  172,   48,  161,   22,  118,
  173,  176,  118,  154,  160,  155,  114,  189,  236,  158,
  156,  178,  157,  162,  159,  128,  179,  118,   48,    2,
    3,    4,    5,  161,  180,  231,  181,  154,  239,  155,
  160,  216,  182,  216,  161,  158,  156,  238,  157,  162,
  159,    8,  120,  214,  147,  120,  163,  165,  167,   47,
  210,  118,   47,  154,  145,  155,  215,  145,  161,  112,
  120,  144,  112,  136,  144,  136,  217,  136,  136,  136,
  136,  233,  237,  234,  137,  243,  137,  112,  137,  137,
  137,  137,  247,    1,  161,   20,   36,   11,   35,   10,
  160,   38,   90,   37,  120,  158,  156,  143,  157,  162,
  159,   94,  142,   94,   16,   94,   94,   94,   94,   90,
   20,  112,  244,  154,   16,  155,    1,    2,    3,    4,
    5,    6,    7,   54,   76,  213,  206,  127,    0,  127,
    0,  127,  127,  127,  127,    0,  102,   44,  102,    8,
  102,  102,  102,  102,  161,    0,   44,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   16,    0,    0,    0,
    0,    0,  104,    0,  104,    0,  104,  104,  104,  104,
   16,  106,   96,  106,    0,  106,  106,  106,  106,   97,
    0,    0,    0,  160,   95,    0,    0,    0,  158,  156,
    0,  157,  162,  159,    0,  116,    0,  148,  116,  149,
    0,  150,  151,  152,  153,    0,  154,  160,  155,    0,
  114,  114,  158,  116,    0,  108,  162,  159,  108,    0,
    0,    0,    0,  148,    0,  149,    0,  150,  151,  152,
  153,    0,    0,  108,  148,    0,  149,  161,  150,  151,
  152,  153,    0,  160,    0,    0,    0,  116,  158,  156,
    0,  157,  162,  159,  110,  118,  118,  110,  148,    0,
  149,  161,  150,  151,  152,  153,  154,  108,  155,  160,
    0,    0,  110,    0,  158,  156,    0,  157,  162,  159,
    0,    0,    0,    0,  148,    0,  149,    0,  150,  151,
  152,  153,  154,    0,  155,    0,    0,  161,  120,  120,
  125,    0,  125,  125,  125,    0,  110,    0,   98,    0,
   98,   98,   98,  112,  112,  112,  112,    0,  125,  125,
    0,  125,  122,  161,    0,  122,   98,   98,    0,   98,
    0,    0,    0,    0,    0,  100,    0,  100,  100,  100,
  122,    0,  242,    0,  148,    0,  149,    0,  150,  151,
  152,  153,  125,  100,  100,    0,  100,  160,    0,    0,
   98,    0,  158,  156,    0,  157,  162,  159,    0,    0,
   24,   25,   26,   27,  122,    0,    0,    0,   93,    0,
  154,   93,  155,   17,    0,    0,    0,  100,    0,   46,
   17,    0,   50,    0,    0,   17,   93,    0,   55,   56,
    0,    0,    0,   16,   80,   61,    0,    0,    0,   17,
   16,  161,    0,   86,   87,   16,   89,   90,   22,    0,
   91,   92,   93,   94,    0,    0,    0,  126,   57,   16,
   93,    0,    0,    0,    0,   57,    0,  148,    0,  149,
   57,  150,  151,  152,  153,    0,    0,    0,   96,  116,
  116,  116,  116,  160,   57,   97,    0,    0,  158,  156,
   95,  157,  162,  159,    0,    0,    0,    0,    0,  108,
  108,  108,  108,   17,    0,   17,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   16,    0,   16,    0,  148,    0,  149,
    0,  150,  151,  152,    0,    0,    0,  161,  110,  110,
  110,  110,    0,    0,    0,    0,  204,    0,   57,    0,
   57,    0,    0,  148,    0,  149,    0,  150,  151,    0,
    0,    0,  211,    0,    0,    0,    0,    0,   57,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  125,    0,  125,    0,  125,  125,  125,  125,   98,    0,
   98,    0,   98,   98,   98,   98,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  122,
    0,    0,    0,    0,    0,  100,    0,  100,    0,  100,
  100,  100,  100,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  148,    0,  149,    0,   17,    0,    0,   17,   17,
   17,    0,   17,   17,   17,   17,   17,   17,   17,   17,
    0,   17,   17,   17,   17,   16,    0,    0,   16,   16,
   16,    0,   16,   16,   16,   16,   16,   16,   16,   16,
    0,   16,   16,   16,   16,    0,    0,    0,    0,  140,
   57,    0,    0,   57,   57,   57,    0,   57,   57,   57,
   57,   57,   57,   57,   57,    0,   57,   57,   57,   57,
   80,    0,    0,   81,   82,   83,    0,   84,   85,   86,
   87,   88,   89,   90,   22,    0,   91,   92,   93,   94,
  183,  184,    0,  187,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  203,    0,    0,    0,    0,    0,    0,
    0,    0,  187,    0,    0,    0,    0,  208,  209,    0,
    0,  212,  187,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  218,  219,  220,  221,  222,  223,  224,  225,
  226,  227,  228,  229,  230,    0,    0,  232,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  240,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  241,
};
short yycheck[] = {                                      37,
   91,  123,   41,   41,   42,   43,   44,   45,   46,   47,
   37,   46,  132,   41,   41,   42,   43,   44,   45,   46,
   47,   59,   60,   61,   62,  101,   59,   59,  279,   33,
   59,   59,   59,   60,   61,   62,   52,   37,   42,   93,
  116,   41,   42,   43,   44,   45,   46,   47,   40,   40,
   66,   30,   91,   91,  174,   93,   91,  266,   41,   59,
   60,   44,   62,   37,   91,  123,   93,   41,   42,   43,
   44,   45,   37,   47,    0,  267,   41,   42,   43,   44,
   45,   47,   47,   49,   10,   59,   60,  123,   62,   68,
   69,   91,  125,   93,   59,   60,  125,   62,   37,  118,
  119,  120,   41,   42,   43,   44,   45,   37,   47,  123,
  125,   41,   42,   43,   44,   45,   40,   47,   40,   93,
   59,   60,   48,   62,  244,   44,   52,   59,   93,   59,
   60,   57,   62,   37,   59,  125,  125,   41,   42,   43,
   66,   45,   46,   47,   41,  267,   72,   44,  257,  258,
  259,  260,  261,   40,   93,   61,   60,   41,   62,   37,
   44,   59,   59,   93,   42,   43,   59,   45,   46,   47,
   37,  280,   40,   59,   41,   42,   43,   40,   45,   46,
   47,   40,   60,   41,   62,   59,   44,   91,  279,   41,
   59,   40,   44,   60,   37,   62,   93,  271,   41,   42,
   43,   40,   45,   46,   47,   41,   40,   59,   44,  258,
  259,  260,  261,   91,   40,   93,   40,   60,   41,   62,
   37,   44,   40,   44,   91,   42,   43,   44,   45,   46,
   47,  280,   41,   41,  116,   44,  118,  119,  120,   41,
   59,   93,   44,   60,   41,   62,   41,   44,   91,   41,
   59,   41,   44,  291,   44,  293,   41,  295,  296,  297,
  298,   41,   41,   59,  291,   59,  293,   59,  295,  296,
  297,  298,   41,    0,   91,   59,  123,  125,  123,  125,
   37,  125,   59,  125,   93,   42,   43,   41,   45,   46,
   47,  291,   41,  293,    0,  295,  296,  297,  298,   41,
   10,   93,   59,   60,   10,   62,  257,  258,  259,  260,
  261,  262,  263,   42,   66,  180,  170,  291,   -1,  293,
   -1,  295,  296,  297,  298,   -1,  291,   33,  293,  280,
  295,  296,  297,  298,   91,   -1,   42,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   52,   -1,   -1,   -1,
   -1,   -1,  291,   -1,  293,   -1,  295,  296,  297,  298,
   66,  291,   33,  293,   -1,  295,  296,  297,  298,   40,
   -1,   -1,   -1,   37,   45,   -1,   -1,   -1,   42,   43,
   -1,   45,   46,   47,   -1,   41,   -1,  291,   44,  293,
   -1,  295,  296,  297,  298,   -1,   60,   37,   62,   -1,
  297,  298,   42,   59,   -1,   41,   46,   47,   44,   -1,
   -1,   -1,   -1,  291,   -1,  293,   -1,  295,  296,  297,
  298,   -1,   -1,   59,  291,   -1,  293,   91,  295,  296,
  297,  298,   -1,   37,   -1,   -1,   -1,   93,   42,   43,
   -1,   45,   46,   47,   41,  297,  298,   44,  291,   -1,
  293,   91,  295,  296,  297,  298,   60,   93,   62,   37,
   -1,   -1,   59,   -1,   42,   43,   -1,   45,   46,   47,
   -1,   -1,   -1,   -1,  291,   -1,  293,   -1,  295,  296,
  297,  298,   60,   -1,   62,   -1,   -1,   91,  297,  298,
   41,   -1,   43,   44,   45,   -1,   93,   -1,   41,   -1,
   43,   44,   45,  295,  296,  297,  298,   -1,   59,   60,
   -1,   62,   41,   91,   -1,   44,   59,   60,   -1,   62,
   -1,   -1,   -1,   -1,   -1,   41,   -1,   43,   44,   45,
   59,   -1,  238,   -1,  291,   -1,  293,   -1,  295,  296,
  297,  298,   93,   59,   60,   -1,   62,   37,   -1,   -1,
   93,   -1,   42,   43,   -1,   45,   46,   47,   -1,   -1,
   16,   17,   18,   19,   93,   -1,   -1,   -1,   41,   -1,
   60,   44,   62,   33,   -1,   -1,   -1,   93,   -1,   35,
   40,   -1,   38,   -1,   -1,   45,   59,   -1,   44,   45,
   -1,   -1,   -1,   33,  265,   51,   -1,   -1,   -1,   59,
   40,   91,   -1,  274,  275,   45,  277,  278,  279,   -1,
  281,  282,  283,  284,   -1,   -1,   -1,   73,   33,   59,
   93,   -1,   -1,   -1,   -1,   40,   -1,  291,   -1,  293,
   45,  295,  296,  297,  298,   -1,   -1,   -1,   33,  295,
  296,  297,  298,   37,   59,   40,   -1,   -1,   42,   43,
   45,   45,   46,   47,   -1,   -1,   -1,   -1,   -1,  295,
  296,  297,  298,  123,   -1,  125,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  123,   -1,  125,   -1,  291,   -1,  293,
   -1,  295,  296,  297,   -1,   -1,   -1,   91,  295,  296,
  297,  298,   -1,   -1,   -1,   -1,  162,   -1,  123,   -1,
  125,   -1,   -1,  291,   -1,  293,   -1,  295,  296,   -1,
   -1,   -1,  178,   -1,   -1,   -1,   -1,   -1,  123,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  291,   -1,  293,   -1,  295,  296,  297,  298,  291,   -1,
  293,   -1,  295,  296,  297,  298,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  298,
   -1,   -1,   -1,   -1,   -1,  291,   -1,  293,   -1,  295,
  296,  297,  298,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  291,   -1,  293,   -1,  265,   -1,   -1,  268,  269,
  270,   -1,  272,  273,  274,  275,  276,  277,  278,  279,
   -1,  281,  282,  283,  284,  265,   -1,   -1,  268,  269,
  270,   -1,  272,  273,  274,  275,  276,  277,  278,  279,
   -1,  281,  282,  283,  284,   -1,   -1,   -1,   -1,   97,
  265,   -1,   -1,  268,  269,  270,   -1,  272,  273,  274,
  275,  276,  277,  278,  279,   -1,  281,  282,  283,  284,
  265,   -1,   -1,  268,  269,  270,   -1,  272,  273,  274,
  275,  276,  277,  278,  279,   -1,  281,  282,  283,  284,
  138,  139,   -1,  141,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  161,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  170,   -1,   -1,   -1,   -1,  175,  176,   -1,
   -1,  179,  180,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  190,  191,  192,  193,  194,  195,  196,  197,
  198,  199,  200,  201,  202,   -1,   -1,  205,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  216,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  234,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 308
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,0,0,
0,0,0,0,0,0,"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Y_Void","Y_Int","Y_Double","Y_Bool",
"Y_String","Y_Class","Y_Interface","Y_Null","Y_This","Y_Extends","Y_Implements",
"Y_For","Y_While","Y_If","Y_Else","Y_Return","Y_Break","Y_New","Y_NewArray",
"Y_Print","Y_ReadInteger","Y_ReadLine","Y_Identifier","Y_TypeIdentifier",
"Y_IntConstant","Y_BoolConstant","Y_DoubleConstant","Y_StringConstant","Y_Plus",
"Y_Minus","Y_Times","Y_Div","Y_Mod","Y_Less","Y_LessEqual","Y_Greater",
"Y_GreaterEqual","Y_Assign","Y_Equal","Y_NotEqual","Y_And","Y_Or","Y_Not",
"Y_Semicolon","Y_Comma","Y_Dot","Y_LBracket","Y_RBracket","Y_LParen","Y_RParen",
"Y_LBrace","Y_RBrace",
};
char *yyrule[] = {
"$accept : program",
"program : decls",
"decls : decls decl",
"decls : decl",
"decl : variable ';'",
"decl : functionDecl",
"decl : classDecl",
"decl : interfaceDecl",
"$$1 :",
"interfaceDecl : Y_Interface $$1 identifier '{' nprototypes '}'",
"nprototypes : prototypes",
"nprototypes :",
"prototypes : prototypes prototype",
"prototypes : prototype",
"prototype : type identifier '(' formals ')' ';'",
"prototype : void identifier '(' formals ')' ';'",
"nvariableDecls : variableDecls",
"nvariableDecls :",
"variableDecls : variableDecls variable ';'",
"variableDecls : variable ';'",
"variable : type identifier",
"type : Y_Int",
"type : Y_Double",
"type : Y_Bool",
"type : Y_String",
"type : Y_TypeIdentifier",
"type : type '[' ']'",
"functionDecl : type identifier '(' formals ')' stmtBlock",
"functionDecl : void identifier '(' formals ')' stmtBlock",
"$$2 :",
"classDecl : Y_Class $$2 identifier extends_ident implements_ident '{' nfields '}'",
"$$3 :",
"extends_ident : Y_Extends $$3 identifier",
"extends_ident :",
"$$4 :",
"implements_ident : Y_Implements $$4 identifiers",
"implements_ident :",
"nfields : fields",
"nfields :",
"fields : fields field",
"fields : field",
"field : variable ';'",
"field : functionDecl",
"identifiers : identifiers ',' identifier",
"identifiers : identifier",
"formals : formals ',' variable",
"formals : variable",
"formals :",
"stmtBlock : '{' nvariableDecls nstmts '}'",
"nstmts : stmts",
"nstmts :",
"stmts : stmts stmt",
"stmts : stmt",
"$$5 :",
"returnStmt : Y_Return $$5 nexpr ';'",
"$$6 :",
"printStmt : Y_Print $$6 '(' exprs ')' ';'",
"stmt : matched_stmt",
"stmt : open_stmt",
"other_stmt : breakStmt ';'",
"other_stmt : nexpr ';'",
"other_stmt : returnStmt",
"other_stmt : printStmt",
"other_stmt : stmtBlock",
"matched_stmt : other_stmt",
"matched_stmt : matched_if",
"matched_stmt : matched_while",
"matched_stmt : matched_for",
"open_stmt : open_if",
"open_stmt : open_while",
"open_stmt : open_for",
"$$7 :",
"commonIf : Y_If $$7 '(' expr ')'",
"$$8 :",
"commonWhile : Y_While $$8 '(' expr ')'",
"$$9 :",
"commonFor : Y_For $$9 '(' nexpr ';' expr ';' nexpr ')'",
"common_matched_else : commonIf matched_stmt Y_Else",
"matched_if : common_matched_else matched_stmt",
"matched_while : commonWhile matched_stmt",
"matched_for : commonFor matched_stmt",
"open_if : commonIf stmt",
"open_if : common_matched_else open_stmt",
"open_while : commonWhile open_stmt",
"open_for : commonFor open_stmt",
"constant : Y_IntConstant",
"constant : Y_DoubleConstant",
"constant : Y_BoolConstant",
"constant : Y_StringConstant",
"nexpr : expr",
"nexpr :",
"expr : constant",
"$$10 :",
"expr : lvalue '=' $$10 expr",
"expr : lvalue",
"expr : Y_This",
"expr : call",
"$$11 :",
"expr : expr '+' $$11 expr",
"$$12 :",
"expr : expr '-' $$12 expr",
"$$13 :",
"expr : expr '*' $$13 expr",
"$$14 :",
"expr : expr '/' $$14 expr",
"$$15 :",
"expr : expr '%' $$15 expr",
"$$16 :",
"expr : expr '<' $$16 expr",
"$$17 :",
"expr : expr '>' $$17 expr",
"$$18 :",
"expr : expr Y_LessEqual $$18 expr",
"$$19 :",
"expr : expr Y_Equal $$19 expr",
"$$20 :",
"expr : expr Y_GreaterEqual $$20 expr",
"$$21 :",
"expr : expr Y_NotEqual $$21 expr",
"$$22 :",
"expr : expr Y_And $$22 expr",
"$$23 :",
"expr : expr Y_Or $$23 expr",
"expr : '(' expr ')'",
"$$24 :",
"expr : '-' $$24 expr",
"$$25 :",
"expr : '!' $$25 expr",
"$$26 :",
"expr : Y_ReadInteger $$26 '(' ')'",
"$$27 :",
"expr : Y_ReadLine $$27 '(' ')'",
"$$28 :",
"expr : Y_New $$28 '(' identifier ')'",
"$$29 :",
"expr : Y_NewArray $$29 '(' expr ',' type ')'",
"lvalue : identifier",
"lvalue : dot",
"lvalue : expr '[' expr ']'",
"dot : expr '.' identifier",
"call : dot '(' actuals ')'",
"call : identifier '(' actuals ')'",
"actuals : exprs",
"actuals :",
"exprs : exprs ',' expr",
"exprs : expr",
"identifier : Y_Identifier",
"void : Y_Void",
"breakStmt : Y_Break",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 796 "decaf.y"

int yyerror(const char * s)
{
  fprintf(stderr, "%s\n", s);
  return 0;
}

int main() {

  yyparse();
  traverseTree(top, 0, 0);
  return 0;
}
#line 671 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 176 "decaf.y"
{
		ParseTree *result = new ParseTree("START PROGRAM");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 2:
#line 186 "decaf.y"
{
		yyvsp[-1]->addChild(yyvsp[0]);
		yyval = yyvsp[-1];
	}
break;
case 3:
#line 190 "decaf.y"
{
		ParseTree *result = new ParseTree("==== DECLARATIONS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 4:
#line 198 "decaf.y"
{yyval = yyvsp[-1];}
break;
case 5:
#line 199 "decaf.y"
{yyval = yyvsp[0];}
break;
case 6:
#line 200 "decaf.y"
{yyval = yyvsp[0];}
break;
case 7:
#line 201 "decaf.y"
{yyval = yyvsp[0];}
break;
case 8:
#line 205 "decaf.y"
{PUSH();}
break;
case 9:
#line 205 "decaf.y"
{
		ParseTree *result = new ParseTree("==== INTERFACE ====");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 10:
#line 215 "decaf.y"
{yyval = yyvsp[0];}
break;
case 11:
#line 216 "decaf.y"
{yyval = NULL;}
break;
case 12:
#line 219 "decaf.y"
{
		yyvsp[-1]->addChild(yyvsp[0]);
		yyval = yyvsp[-1];
	}
break;
case 13:
#line 223 "decaf.y"
{
		ParseTree *result = new ParseTree("==== PROTOTYPES ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 14:
#line 231 "decaf.y"
{
		ParseTree *result = new ParseTree("PROTOTYPE");
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-4]);
		result->addChild(yyvsp[-2]);
		top = yyval = result;
	}
break;
case 15:
#line 238 "decaf.y"
{
		ParseTree *result = new ParseTree("PROTOTYPE");
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-4]);
		result->addChild(yyvsp[-2]);
		top = yyval = result;
	}
break;
case 16:
#line 249 "decaf.y"
{yyval = yyvsp[0];}
break;
case 17:
#line 250 "decaf.y"
{yyval = NULL;}
break;
case 18:
#line 254 "decaf.y"
{
		yyvsp[-2]->addChild(yyvsp[-1]);
		yyval = yyvsp[-2];
	}
break;
case 19:
#line 258 "decaf.y"
{
		ParseTree *result = new ParseTree("==== VARIABLE DECLARATIONS ====");
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 20:
#line 266 "decaf.y"
{
		ParseTree *result = new ParseTree("VARIABLE");
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 21:
#line 278 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 22:
#line 279 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 23:
#line 280 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 24:
#line 281 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 25:
#line 282 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 26:
#line 283 "decaf.y"
{
		ParseTree *result = new ParseTree("ARRAY:");
		result->addChild(yyvsp[-2]);
		top = yyval = result;
	}
break;
case 27:
#line 292 "decaf.y"
{
		ParseTree *result = new ParseTree("==== FUNCTION (VARIABLE) ====");
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-4]);
		result->addChild(yyvsp[-2]);
		result->addChild(yyvsp[0]);
		
		
		top = yyval = result;
	}
break;
case 28:
#line 303 "decaf.y"
{
		ParseTree *result = new ParseTree("==== FUNCTION (VOID) ====");
		result->addChild(yyvsp[-2]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 29:
#line 314 "decaf.y"
{PUSH();}
break;
case 30:
#line 314 "decaf.y"
{
		ParseTree *result = new ParseTree("==== CLASS ====");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-4]);
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 31:
#line 325 "decaf.y"
{PUSH();}
break;
case 32:
#line 325 "decaf.y"
{
		ParseTree *result = new ParseTree("EXTENDS");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 33:
#line 331 "decaf.y"
{yyval = NULL;}
break;
case 34:
#line 334 "decaf.y"
{PUSH();}
break;
case 35:
#line 334 "decaf.y"
{
		ParseTree *result = new ParseTree("IMPLEMENTS");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 36:
#line 340 "decaf.y"
{yyval = NULL;}
break;
case 37:
#line 343 "decaf.y"
{yyval = yyvsp[0];}
break;
case 38:
#line 344 "decaf.y"
{yyval = NULL;}
break;
case 39:
#line 347 "decaf.y"
{
		yyvsp[-1]->addChild(yyvsp[0]);
		yyval = yyvsp[-1];
	}
break;
case 40:
#line 351 "decaf.y"
{
		ParseTree *result = new ParseTree("==== FIELDS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 41:
#line 358 "decaf.y"
{yyval = yyvsp[-1];}
break;
case 42:
#line 359 "decaf.y"
{yyval = yyvsp[0];}
break;
case 43:
#line 362 "decaf.y"
{
		yyvsp[-2]->addChild(yyvsp[0]);
		yyval = yyvsp[-2];
	}
break;
case 44:
#line 366 "decaf.y"
{
		ParseTree *result = new ParseTree("==== IDENTIFIERS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 45:
#line 377 "decaf.y"
{
		yyvsp[-2]->addChild(yyvsp[0]);
		yyval = yyvsp[-2];
	}
break;
case 46:
#line 381 "decaf.y"
{
		ParseTree *result = new ParseTree("==== FORMALS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 47:
#line 386 "decaf.y"
{yyval = NULL;}
break;
case 48:
#line 391 "decaf.y"
{ 
		ParseTree *result = new ParseTree("STATEMENT BLOCK");
		result->addChild(yyvsp[-2]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 49:
#line 400 "decaf.y"
{yyval = yyvsp[0];}
break;
case 50:
#line 401 "decaf.y"
{yyval = NULL;}
break;
case 51:
#line 406 "decaf.y"
{
		yyvsp[-1]->addChild(yyvsp[0]);
		yyval = yyvsp[-1];
	}
break;
case 52:
#line 410 "decaf.y"
{
		ParseTree *result = new ParseTree("==== STATEMENTS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 53:
#line 419 "decaf.y"
{PUSH();}
break;
case 54:
#line 419 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: return");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 55:
#line 428 "decaf.y"
{PUSH();}
break;
case 56:
#line 428 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: print");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-2]);
		top = yyval = result;
	}
break;
case 57:
#line 439 "decaf.y"
{yyval = yyvsp[0];}
break;
case 58:
#line 440 "decaf.y"
{yyval = yyvsp[0];}
break;
case 59:
#line 444 "decaf.y"
{yyval = yyvsp[-1];}
break;
case 60:
#line 445 "decaf.y"
{yyval = yyvsp[-1];}
break;
case 61:
#line 446 "decaf.y"
{yyval = yyvsp[0];}
break;
case 62:
#line 447 "decaf.y"
{yyval = yyvsp[0];}
break;
case 63:
#line 448 "decaf.y"
{yyval = yyvsp[0];}
break;
case 64:
#line 453 "decaf.y"
{yyval = yyvsp[0];}
break;
case 65:
#line 454 "decaf.y"
{yyval = yyvsp[0];}
break;
case 66:
#line 455 "decaf.y"
{yyval = yyvsp[0];}
break;
case 67:
#line 456 "decaf.y"
{yyval = yyvsp[0];}
break;
case 68:
#line 461 "decaf.y"
{yyval = yyvsp[0];}
break;
case 69:
#line 462 "decaf.y"
{yyval = yyvsp[0];}
break;
case 70:
#line 463 "decaf.y"
{yyval = yyvsp[0];}
break;
case 71:
#line 468 "decaf.y"
{PUSH();}
break;
case 72:
#line 468 "decaf.y"
{ yyval = yyvsp[-1];}
break;
case 73:
#line 473 "decaf.y"
{PUSH();}
break;
case 74:
#line 473 "decaf.y"
{ yyval = yyvsp[-1];}
break;
case 75:
#line 476 "decaf.y"
{PUSH();}
break;
case 76:
#line 476 "decaf.y"
{ 
		ParseTree *result = new ParseTree("(expr?; expr; expr?)");
		result->addChild(yyvsp[-5]);
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 77:
#line 487 "decaf.y"
{
		PUSH();
		ParseTree *result = new ParseTree("condition + statement");
		result->addChild(yyvsp[-2]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 78:
#line 497 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: if/else");
		Token* a_else = POP();
		Token* a_if = POP();
		result->addChild(new ParseTree(a_if));
		result->addChild(yyvsp[-1]);
		result->addChild(new ParseTree(a_else));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 79:
#line 510 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: while");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 80:
#line 519 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: for");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 81:
#line 530 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: if");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 82:
#line 537 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: if/else");
		Token* a_else = POP();
		Token* a_if = POP();
		result->addChild(new ParseTree(a_if));
		result->addChild(yyvsp[-1]);
		result->addChild(new ParseTree(a_else));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 83:
#line 551 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: while");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 84:
#line 560 "decaf.y"
{
		ParseTree *result = new ParseTree("STATEMENT: for");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 85:
#line 572 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 86:
#line 573 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 87:
#line 574 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 88:
#line 575 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 89:
#line 582 "decaf.y"
{yyval = yyvsp[0];}
break;
case 90:
#line 583 "decaf.y"
{yyval = NULL;}
break;
case 91:
#line 587 "decaf.y"
{yyval = yyvsp[0];}
break;
case 92:
#line 588 "decaf.y"
{PUSH();}
break;
case 93:
#line 588 "decaf.y"
{
		ParseTree *result = new ParseTree("ASSIGNMENT: lvalue = expr");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 94:
#line 595 "decaf.y"
{yyval = yyvsp[0];}
break;
case 95:
#line 596 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
case 96:
#line 597 "decaf.y"
{yyval = yyvsp[0];}
break;
case 97:
#line 598 "decaf.y"
{PUSH();}
break;
case 98:
#line 598 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: +");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 99:
#line 605 "decaf.y"
{PUSH();}
break;
case 100:
#line 605 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: -");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 101:
#line 612 "decaf.y"
{PUSH();}
break;
case 102:
#line 612 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: *");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;	
	}
break;
case 103:
#line 619 "decaf.y"
{PUSH();}
break;
case 104:
#line 619 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: /");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 105:
#line 626 "decaf.y"
{PUSH();}
break;
case 106:
#line 626 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: %");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 107:
#line 633 "decaf.y"
{PUSH();}
break;
case 108:
#line 633 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: <");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 109:
#line 640 "decaf.y"
{PUSH();}
break;
case 110:
#line 640 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: >");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 111:
#line 647 "decaf.y"
{PUSH();}
break;
case 112:
#line 647 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: <=");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 113:
#line 654 "decaf.y"
{PUSH();}
break;
case 114:
#line 654 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: ==");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 115:
#line 661 "decaf.y"
{PUSH();}
break;
case 116:
#line 661 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: >=");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 117:
#line 668 "decaf.y"
{PUSH();}
break;
case 118:
#line 668 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: !=");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 119:
#line 675 "decaf.y"
{PUSH();}
break;
case 120:
#line 675 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: &&");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 121:
#line 682 "decaf.y"
{PUSH();}
break;
case 122:
#line 682 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: ||");
		result->addChild(yyvsp[-3]);
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 123:
#line 689 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: (expr)");
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 124:
#line 694 "decaf.y"
{PUSH();}
break;
case 125:
#line 694 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: -expr");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 126:
#line 700 "decaf.y"
{PUSH();}
break;
case 127:
#line 700 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: !expr");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 128:
#line 706 "decaf.y"
{PUSH();}
break;
case 129:
#line 706 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: ReadInteger()");
		result->addChild(new ParseTree(POP()));
		top = yyval = result;
	}
break;
case 130:
#line 711 "decaf.y"
{PUSH();}
break;
case 131:
#line 711 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: ReadLine()");
		result->addChild(new ParseTree(POP()));
		top = yyval = result;
	}
break;
case 132:
#line 717 "decaf.y"
{PUSH();}
break;
case 133:
#line 717 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: New(ident)");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 134:
#line 723 "decaf.y"
{PUSH();}
break;
case 135:
#line 723 "decaf.y"
{
		ParseTree *result = new ParseTree("expr: New(expr, type)");
		result->addChild(new ParseTree(POP()));
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
		
	}
break;
case 136:
#line 734 "decaf.y"
{yyval = yyvsp[0];}
break;
case 137:
#line 735 "decaf.y"
{yyval = yyvsp[0];}
break;
case 138:
#line 736 "decaf.y"
{
		ParseTree *result = new ParseTree("ARRAY: expr[expr]");
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 139:
#line 746 "decaf.y"
{
		ParseTree *result = new ParseTree("DOT");
		result->addChild(yyvsp[-2]);
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 140:
#line 756 "decaf.y"
{
		ParseTree *result = new ParseTree("CALL: expr.ident(exprs)");
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 141:
#line 762 "decaf.y"
{
		ParseTree *result = new ParseTree("CALL: ident(exprs)");
		result->addChild(yyvsp[-3]);
		result->addChild(yyvsp[-1]);
		top = yyval = result;
	}
break;
case 142:
#line 772 "decaf.y"
{yyval = yyvsp[0];}
break;
case 143:
#line 773 "decaf.y"
{yyval = NULL;}
break;
case 144:
#line 776 "decaf.y"
{
		yyvsp[-2]->addChild(yyvsp[0]);
		yyval = yyvsp[-2];
	}
break;
case 145:
#line 780 "decaf.y"
{
		ParseTree *result = new ParseTree("==== EXPRESSIONS ====");
		result->addChild(yyvsp[0]);
		top = yyval = result;
	}
break;
case 146:
#line 790 "decaf.y"
{ yyval = new ParseTree(myTok);}
break;
case 147:
#line 791 "decaf.y"
{ yyval = new ParseTree(myTok);}
break;
case 148:
#line 792 "decaf.y"
{yyval = new ParseTree(myTok);}
break;
#line 1776 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
