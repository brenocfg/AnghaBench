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
typedef  int WCHAR ;

/* Variables and functions */
 int TK_COMMA ; 
 int TK_DOT ; 
 int TK_EQ ; 
 int TK_GE ; 
 int TK_GT ; 
 int TK_ID ; 
 int TK_ILLEGAL ; 
 int TK_INTEGER ; 
 int TK_LE ; 
 int TK_LP ; 
 int TK_LT ; 
 int TK_MINUS ; 
 int TK_NE ; 
 int TK_RP ; 
 int TK_SPACE ; 
 int TK_STAR ; 
 int TK_STRING ; 
 int TK_WILDCARD ; 
 int /*<<< orphan*/  isDigit (int const) ; 
 int /*<<< orphan*/ * isIdChar ; 
 int /*<<< orphan*/  isSpace (int const) ; 
 int sqliteKeywordCode (int const*,int) ; 

int sqliteGetToken(const WCHAR *z, int *tokenType, int *skip){
  int i;

  *skip = 0;
  switch( *z ){
    case ' ': case '\t': case '\n': case '\f':
      for(i=1; isSpace(z[i]); i++){}
      *tokenType = TK_SPACE;
      return i;
    case '-':
      if( z[1]==0 ) return -1;
      *tokenType = TK_MINUS;
      return 1;
    case '(':
      *tokenType = TK_LP;
      return 1;
    case ')':
      *tokenType = TK_RP;
      return 1;
    case '*':
      *tokenType = TK_STAR;
      return 1;
    case '=':
      *tokenType = TK_EQ;
      return 1;
    case '<':
      if( z[1]=='=' ){
        *tokenType = TK_LE;
        return 2;
      }else if( z[1]=='>' ){
        *tokenType = TK_NE;
        return 2;
      }else{
        *tokenType = TK_LT;
        return 1;
      }
    case '>':
      if( z[1]=='=' ){
        *tokenType = TK_GE;
        return 2;
      }else{
        *tokenType = TK_GT;
        return 1;
      }
    case '!':
      if( z[1]!='=' ){
        *tokenType = TK_ILLEGAL;
        return 2;
      }else{
        *tokenType = TK_NE;
        return 2;
      }
    case '?':
      *tokenType = TK_WILDCARD;
      return 1;
    case ',':
      *tokenType = TK_COMMA;
      return 1;
    case '`': case '\'': {
      int delim = z[0];
      for(i=1; z[i]; i++){
        if( z[i]==delim )
          break;
      }
      if( z[i] ) i++;
      if( delim == '`' )
        *tokenType = TK_ID;
      else
        *tokenType = TK_STRING;
      return i;
    }
    case '.':
      if( !isDigit(z[1]) ){
        *tokenType = TK_DOT;
        return 1;
      }
      /* Fall through */
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      *tokenType = TK_INTEGER;
      for(i=1; isDigit(z[i]); i++){}
      return i;
    case '[':
      for(i=1; z[i] && z[i-1]!=']'; i++){}
      *tokenType = TK_ID;
      return i;
    default:
      if( !isIdChar[*z] ){
        break;
      }
      for(i=1; isIdChar[z[i]]; i++){}
      *tokenType = sqliteKeywordCode(z, i);
      if( *tokenType == TK_ID && z[i] == '`' ) *skip = 1;
      return i;
  }
  *tokenType = TK_ILLEGAL;
  return 1;
}