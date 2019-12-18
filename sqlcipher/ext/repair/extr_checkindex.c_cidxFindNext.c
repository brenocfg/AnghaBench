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
 int CIDX_PARSE_CLOSE ; 
 int CIDX_PARSE_COMMA ; 
 int CIDX_PARSE_EOF ; 
 int CIDX_PARSE_OPEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ cidx_isspace (char const) ; 

__attribute__((used)) static int cidxFindNext(
  const char *zIn, 
  const char **pzOut,
  int *pbDoNotTrim                /* OUT: True if prev is -- comment */
){
  const char *z = zIn;

  while( 1 ){
    while( cidx_isspace(*z) ) z++;
    if( z[0]=='-' && z[1]=='-' ){
      z += 2;
      while( z[0]!='\n' ){
        if( z[0]=='\0' ) return CIDX_PARSE_EOF;
        z++;
      }
      while( cidx_isspace(*z) ) z++;
      if( pbDoNotTrim ) *pbDoNotTrim = 1;
    }else
    if( z[0]=='/' && z[1]=='*' ){
      z += 2;
      while( z[0]!='*' || z[1]!='/' ){
        if( z[1]=='\0' ) return CIDX_PARSE_EOF;
        z++;
      }
      z += 2;
    }else{
      *pzOut = z;
      if( pbDoNotTrim==0 ) return CIDX_PARSE_EOF;
      switch( *z ){
        case '\0':
          return CIDX_PARSE_EOF;
        case '(':
          return CIDX_PARSE_OPEN;
        case ')':
          return CIDX_PARSE_CLOSE;
        case ',':
          return CIDX_PARSE_COMMA;
  
        case '"': 
        case '\'': 
        case '`': {
          char q = *z;
          z++;
          while( *z ){
            if( *z==q ){
              z++;
              if( *z!=q ) break;
            }
            z++;
          }
          break;
        }
  
        case '[':
          while( *z++!=']' );
          break;
  
        default:
          z++;
          break;
      }
      *pbDoNotTrim = 0;
    }
  }

  assert( 0 );
  return -1;
}