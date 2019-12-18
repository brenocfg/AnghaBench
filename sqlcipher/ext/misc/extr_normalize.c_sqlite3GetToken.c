#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  CC_AND 154 
#define  CC_BANG 153 
#define  CC_COMMA 152 
#define  CC_DIGIT 151 
#define  CC_DOLLAR 150 
#define  CC_DOT 149 
#define  CC_EQ 148 
#define  CC_GT 147 
#define  CC_ID 146 
#define  CC_KYWD 145 
#define  CC_LP 144 
#define  CC_LT 143 
#define  CC_MINUS 142 
#define  CC_PERCENT 141 
#define  CC_PIPE 140 
#define  CC_PLUS 139 
#define  CC_QUOTE 138 
#define  CC_QUOTE2 137 
#define  CC_RP 136 
#define  CC_SEMI 135 
#define  CC_SLASH 134 
#define  CC_SPACE 133 
#define  CC_STAR 132 
#define  CC_TILDA 131 
#define  CC_VARALPHA 130 
#define  CC_VARNUM 129 
#define  CC_X 128 
 scalar_t__ IdChar (unsigned char const) ; 
 int TK_BITAND ; 
 int TK_BITNOT ; 
 int TK_BITOR ; 
 int TK_BLOB ; 
 int TK_COMMA ; 
 int TK_CONCAT ; 
 int TK_DOT ; 
 int TK_EQ ; 
 int TK_FLOAT ; 
 int TK_GE ; 
 int TK_GT ; 
 int TK_ID ; 
 int TK_ILLEGAL ; 
 int TK_INTEGER ; 
 int TK_LE ; 
 int TK_LP ; 
 int TK_LSHIFT ; 
 int TK_LT ; 
 int TK_MINUS ; 
 int TK_NE ; 
 int TK_PLUS ; 
 int TK_REM ; 
 int TK_RP ; 
 int TK_RSHIFT ; 
 int TK_SEMI ; 
 int TK_SLASH ; 
 int TK_SPACE ; 
 int TK_STAR ; 
 int TK_STRING ; 
 int TK_VARIABLE ; 
 int* aiClass ; 
 int /*<<< orphan*/  sqlite3Isdigit (unsigned char const) ; 
 int /*<<< orphan*/  sqlite3Isspace (unsigned char const) ; 
 int /*<<< orphan*/  sqlite3Isxdigit (unsigned char const) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int sqlite3GetToken(const unsigned char *z, int *tokenType){
  int i, c;
  switch( aiClass[*z] ){  /* Switch on the character-class of the first byte
                          ** of the token. See the comment on the CC_ defines
                          ** above. */
    case CC_SPACE: {
      for(i=1; sqlite3Isspace(z[i]); i++){}
      *tokenType = TK_SPACE;
      return i;
    }
    case CC_MINUS: {
      if( z[1]=='-' ){
        for(i=2; (c=z[i])!=0 && c!='\n'; i++){}
        *tokenType = TK_SPACE;
        return i;
      }
      *tokenType = TK_MINUS;
      return 1;
    }
    case CC_LP: {
      *tokenType = TK_LP;
      return 1;
    }
    case CC_RP: {
      *tokenType = TK_RP;
      return 1;
    }
    case CC_SEMI: {
      *tokenType = TK_SEMI;
      return 1;
    }
    case CC_PLUS: {
      *tokenType = TK_PLUS;
      return 1;
    }
    case CC_STAR: {
      *tokenType = TK_STAR;
      return 1;
    }
    case CC_SLASH: {
      if( z[1]!='*' || z[2]==0 ){
        *tokenType = TK_SLASH;
        return 1;
      }
      for(i=3, c=z[2]; (c!='*' || z[i]!='/') && (c=z[i])!=0; i++){}
      if( c ) i++;
      *tokenType = TK_SPACE;
      return i;
    }
    case CC_PERCENT: {
      *tokenType = TK_REM;
      return 1;
    }
    case CC_EQ: {
      *tokenType = TK_EQ;
      return 1 + (z[1]=='=');
    }
    case CC_LT: {
      if( (c=z[1])=='=' ){
        *tokenType = TK_LE;
        return 2;
      }else if( c=='>' ){
        *tokenType = TK_NE;
        return 2;
      }else if( c=='<' ){
        *tokenType = TK_LSHIFT;
        return 2;
      }else{
        *tokenType = TK_LT;
        return 1;
      }
    }
    case CC_GT: {
      if( (c=z[1])=='=' ){
        *tokenType = TK_GE;
        return 2;
      }else if( c=='>' ){
        *tokenType = TK_RSHIFT;
        return 2;
      }else{
        *tokenType = TK_GT;
        return 1;
      }
    }
    case CC_BANG: {
      if( z[1]!='=' ){
        *tokenType = TK_ILLEGAL;
        return 1;
      }else{
        *tokenType = TK_NE;
        return 2;
      }
    }
    case CC_PIPE: {
      if( z[1]!='|' ){
        *tokenType = TK_BITOR;
        return 1;
      }else{
        *tokenType = TK_CONCAT;
        return 2;
      }
    }
    case CC_COMMA: {
      *tokenType = TK_COMMA;
      return 1;
    }
    case CC_AND: {
      *tokenType = TK_BITAND;
      return 1;
    }
    case CC_TILDA: {
      *tokenType = TK_BITNOT;
      return 1;
    }
    case CC_QUOTE: {
      int delim = z[0];
      testcase( delim=='`' );
      testcase( delim=='\'' );
      testcase( delim=='"' );
      for(i=1; (c=z[i])!=0; i++){
        if( c==delim ){
          if( z[i+1]==delim ){
            i++;
          }else{
            break;
          }
        }
      }
      if( c=='\'' ){
        *tokenType = TK_STRING;
        return i+1;
      }else if( c!=0 ){
        *tokenType = TK_ID;
        return i+1;
      }else{
        *tokenType = TK_ILLEGAL;
        return i;
      }
    }
    case CC_DOT: {
      if( !sqlite3Isdigit(z[1]) ){
        *tokenType = TK_DOT;
        return 1;
      }
      /* If the next character is a digit, this is a floating point
      ** number that begins with ".".  Fall thru into the next case */
    }
    case CC_DIGIT: {
      *tokenType = TK_INTEGER;
      if( z[0]=='0' && (z[1]=='x' || z[1]=='X') && sqlite3Isxdigit(z[2]) ){
        for(i=3; sqlite3Isxdigit(z[i]); i++){}
        return i;
      }
      for(i=0; sqlite3Isdigit(z[i]); i++){}
      if( z[i]=='.' ){
        i++;
        while( sqlite3Isdigit(z[i]) ){ i++; }
        *tokenType = TK_FLOAT;
      }
      if( (z[i]=='e' || z[i]=='E') &&
           ( sqlite3Isdigit(z[i+1]) 
            || ((z[i+1]=='+' || z[i+1]=='-') && sqlite3Isdigit(z[i+2]))
           )
      ){
        i += 2;
        while( sqlite3Isdigit(z[i]) ){ i++; }
        *tokenType = TK_FLOAT;
      }
      while( IdChar(z[i]) ){
        *tokenType = TK_ILLEGAL;
        i++;
      }
      return i;
    }
    case CC_QUOTE2: {
      for(i=1, c=z[0]; c!=']' && (c=z[i])!=0; i++){}
      *tokenType = c==']' ? TK_ID : TK_ILLEGAL;
      return i;
    }
    case CC_VARNUM: {
      *tokenType = TK_VARIABLE;
      for(i=1; sqlite3Isdigit(z[i]); i++){}
      return i;
    }
    case CC_DOLLAR:
    case CC_VARALPHA: {
      int n = 0;
      testcase( z[0]=='$' );  testcase( z[0]=='@' );
      testcase( z[0]==':' );  testcase( z[0]=='#' );
      *tokenType = TK_VARIABLE;
      for(i=1; (c=z[i])!=0; i++){
        if( IdChar(c) ){
          n++;
        }else if( c=='(' && n>0 ){
          do{
            i++;
          }while( (c=z[i])!=0 && !sqlite3Isspace(c) && c!=')' );
          if( c==')' ){
            i++;
          }else{
            *tokenType = TK_ILLEGAL;
          }
          break;
        }else if( c==':' && z[i+1]==':' ){
          i++;
        }else{
          break;
        }
      }
      if( n==0 ) *tokenType = TK_ILLEGAL;
      return i;
    }
    case CC_KYWD: {
      for(i=1; aiClass[z[i]]<=CC_KYWD; i++){}
      if( IdChar(z[i]) ){
        /* This token started out using characters that can appear in keywords,
        ** but z[i] is a character not allowed within keywords, so this must
        ** be an identifier instead */
        i++;
        break;
      }
      *tokenType = TK_ID;
      return i;
    }
    case CC_X: {
      testcase( z[0]=='x' ); testcase( z[0]=='X' );
      if( z[1]=='\'' ){
        *tokenType = TK_BLOB;
        for(i=2; sqlite3Isxdigit(z[i]); i++){}
        if( z[i]!='\'' || i%2 ){
          *tokenType = TK_ILLEGAL;
          while( z[i] && z[i]!='\'' ){ i++; }
        }
        if( z[i] ) i++;
        return i;
      }
      /* If it is not a BLOB literal, then it must be an ID, since no
      ** SQL keywords start with the letter 'x'.  Fall through */
    }
    case CC_ID: {
      i = 1;
      break;
    }
    default: {
      *tokenType = TK_ILLEGAL;
      return 1;
    }
  }
  while( IdChar(z[i]) ){ i++; }
  *tokenType = TK_ID;
  return i;
}