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
 int /*<<< orphan*/  fts5_isdigit (char const) ; 
 int /*<<< orphan*/  sqlite3_strnicmp (char*,char const*,int) ; 

__attribute__((used)) static const char *fts5ConfigSkipLiteral(const char *pIn){
  const char *p = pIn;
  switch( *p ){
    case 'n': case 'N':
      if( sqlite3_strnicmp("null", p, 4)==0 ){
        p = &p[4];
      }else{
        p = 0;
      }
      break;

    case 'x': case 'X':
      p++;
      if( *p=='\'' ){
        p++;
        while( (*p>='a' && *p<='f') 
            || (*p>='A' && *p<='F') 
            || (*p>='0' && *p<='9') 
            ){
          p++;
        }
        if( *p=='\'' && 0==((p-pIn)%2) ){
          p++;
        }else{
          p = 0;
        }
      }else{
        p = 0;
      }
      break;

    case '\'':
      p++;
      while( p ){
        if( *p=='\'' ){
          p++;
          if( *p!='\'' ) break;
        }
        p++;
        if( *p==0 ) p = 0;
      }
      break;

    default:
      /* maybe a number */
      if( *p=='+' || *p=='-' ) p++;
      while( fts5_isdigit(*p) ) p++;

      /* At this point, if the literal was an integer, the parse is 
      ** finished. Or, if it is a floating point value, it may continue
      ** with either a decimal point or an 'E' character. */
      if( *p=='.' && fts5_isdigit(p[1]) ){
        p += 2;
        while( fts5_isdigit(*p) ) p++;
      }
      if( p==pIn ) p = 0;

      break;
  }

  return p;
}