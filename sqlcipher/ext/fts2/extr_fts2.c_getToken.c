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
 int /*<<< orphan*/  IdChar (char const) ; 
 int TOKEN_EOF ; 
 int TOKEN_ID ; 
 int TOKEN_PUNCT ; 
 int TOKEN_SPACE ; 
 int TOKEN_STRING ; 
 int /*<<< orphan*/  safe_isspace (char const) ; 

__attribute__((used)) static int getToken(const char *z, int *tokenType){
  int i, c;
  switch( *z ){
    case 0: {
      *tokenType = TOKEN_EOF;
      return 0;
    }
    case ' ': case '\t': case '\n': case '\f': case '\r': {
      for(i=1; safe_isspace(z[i]); i++){}
      *tokenType = TOKEN_SPACE;
      return i;
    }
    case '`':
    case '\'':
    case '"': {
      int delim = z[0];
      for(i=1; (c=z[i])!=0; i++){
        if( c==delim ){
          if( z[i+1]==delim ){
            i++;
          }else{
            break;
          }
        }
      }
      *tokenType = TOKEN_STRING;
      return i + (c!=0);
    }
    case '[': {
      for(i=1, c=z[0]; c!=']' && (c=z[i])!=0; i++){}
      *tokenType = TOKEN_ID;
      return i;
    }
    default: {
      if( !IdChar(*z) ){
        break;
      }
      for(i=1; IdChar(z[i]); i++){}
      *tokenType = TOKEN_ID;
      return i;
    }
  }
  *tokenType = TOKEN_PUNCT;
  return 1;
}