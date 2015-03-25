#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define KEYWORD 258
#define IDENTIFIER 259
#define INTEGER 260
#define STRING 261
#define DOUBLE 262
#define DIGITS "0123456789"
#define HEXDIGITS "0123456789abcdefABCDEF"
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))


string KEYWORDS[] = {"void", "int", "double", "bool", "string", "class", 
"interface", "null", "this", "extends", "implements", "for", "while",
  "if", "else", "return", "break", "New", "NewArray", "Print", "ReadInteger",
		     "ReadLine"};

struct Token {
  int type;
  string text;
  int line;
  Token() {} // leave uninitialized
  Token(int type, string text, int line) : type(type), text(text), line(line) {}
  string type2string() {
    switch(type) {
    case KEYWORD: return "KEYWORD";
    case IDENTIFIER: return "IDENTIFIER";
    case INTEGER: return "INTEGER";
    case DOUBLE: return "DOUBLE";
    case STRING: return "STRING";
      return "UNKNOWNBUG";
    }
  }
  string toString() {
    // convert line to a C string
    char lineStr[200];
    sprintf(lineStr,"%d",line);
    if (type>256) return type2string()+'('+text+','+lineStr+')';
    else return string("PUNCTUATION(")+(char)type+','+lineStr+')';
  }
  void print() {
    cout << toString() << endl;
  }
};


string sourceCode;
int currPos;
int currLine;

char current() {
  return sourceCode[currPos];
}

void advance() {
  if (currPos >= sourceCode.size()) return;
  if (current()=='\n') currLine++;
  currPos++;
}

bool eof() {
  return currPos >= sourceCode.size();
}


bool lookingAt(string item)
{
  return currPos+item.size() <= sourceCode.size() and
    sourceCode.substr(currPos,item.size()) == item;
}


bool identStartChar(char c)
{
  return ('A' <= c and c <= 'Z') or ('a' <= c and c <= 'z');
}

bool identChar(char c)
{
  bool answer = false;
  answer =  identStartChar(c) or  ('0' <= c and c <= '9') or (c == '_');
  return answer;
}


bool lexKeyword(string ident)
{
  for(int i = 0; i < ARRAY_SIZE(KEYWORDS); i++){
    if(ident == KEYWORDS[i]){
      return true;
    }
  }
  return false;
}

bool lexIdentifier(Token & token) // also leads to lexKeyword()
{
  if (not identStartChar(current()))
    return false;
  string ident = "";
  ident += current();
  advance();
  while (not eof() and identChar(current())) {
    ident += current();
    advance();
  }
  if (lexKeyword(ident)){
    token = Token(KEYWORD, ident, currLine);
  }else{
    token = Token(IDENTIFIER, ident, currLine);
  }
  return true;
}

bool lexString(Token & token)
{
  if (not (current() == '"'))
    return false;
  string cstring = "";
  int initialPos = currPos;
  while (not eof()){

    cstring += current();
    advance();
    if(lookingAt("\\")){
      advance();
    }else if(current() == '\n'){
      currPos = initialPos;
      return false;
    }else if(current() == '"'){
      cstring += current();
      advance();
      break;
    }
  }
  token = Token(STRING, cstring, currLine);
  return true;
}



bool lexInteger(Token & token) // also handles doubles
{
  char *allowed;
  bool hex = false; // allow hex digits?
  string text = "";

  allowed = (char*)DIGITS;
  if (lookingAt("0x") or lookingAt("0X")) {
    text = sourceCode.substr(currPos, 2);
    currPos += 2;
    hex = true;
    if (strchr(HEXDIGITS,current())==NULL) {
      // hack: no hex digit following 0x, revert to the zero.  
      currPos -= 1;
      token = Token(INTEGER, "0", currLine);
      return true;
    }
  }
  if (hex) 
    allowed = (char*)HEXDIGITS;
  while (strchr(allowed,current())) {
    text += current();
    advance();
  }
  if (text.length() == 0)
    return false;

  int type = INTEGER;
 
  // if statement handles doubles
  if (not hex and (current() == '.') and (text.length() > 0)){
    type = DOUBLE;
    allowed = (char*)DIGITS;
    text += current();
    advance();
    while (strchr(allowed, current())){
      text += current();
      advance();
    }
    if(lookingAt("E+") and strchr(allowed, sourceCode[currPos + 2])){
      text += sourceCode.substr(currPos, 2);
      currPos += 2;
      while (strchr(allowed, current())){
	text += current();
	advance();
      }
    }
  }

  token = Token(type, text, currLine);
  return true;
}





// bool lexInteger2(Token & token)
// {
//   int savePos = currPos;
//   int state = 1;
//   int greatestPos = currPos;
//   bool done = false;

//   while (!done) {
//     switch(state) {
//     case 1: 
//       if (current()=='0') {
// 	advance();
// 	state = 3;
//       }
//       else if (strchr("123456789",current())) {
// 	advance();
// 	state = 2;
//       }
//       else
// 	done = true;
//       break;

//     case 2:
//       greatestPos = currPos;
//       if (strchr(DIGITS,current())) 
// 	advance();
//       else
// 	done = true;
//       break;

//     case 3:
//       greatestPos = currPos;
//       if (strchr(DIGITS, current())) {
// 	advance();
// 	state = 2;
//       }
//       else if (strchr("xX",current())) {
// 	advance();
// 	state = 4;
//       }
//       else
// 	done = true;
//       break;

//     case 4:
//       if (strchr(HEXDIGITS, current())) {
// 	advance();
// 	state = 5;
//       }
//       else
// 	done = true;
//       break;

//     case 5:
//       greatestPos = currPos;
//       if (strchr(HEXDIGITS, current())) 
// 	advance();
//       else
// 	done = true;
//       break;
//     default:
//       cout << "bad state " << state << " in lexinteger2 " << endl;
//       break;
//     } // switch
//   } // while
//   if (greatestPos > savePos) {
//     token = Token(INTEGER, sourceCode.substr(savePos,greatestPos-savePos), currLine);
//     currPos = greatestPos;
//     return true;
//   }
//   else {
//     currPos = savePos;
//     return false;
//   }
// }




int main() {
  // Read the input
  sourceCode = "";
  char c;
  while (true) {
    c = cin.get();
    if (!cin) break;
    sourceCode += c;
  }
  currLine = 1;
  currPos = 0;
  Token tok;
  while (not eof()) {
    if (lexIdentifier(tok))
      tok.print();
    else if (lexInteger(tok))
      tok.print();
    else if (lexString(tok))
      tok.print();
    else
      advance();
  }

}
