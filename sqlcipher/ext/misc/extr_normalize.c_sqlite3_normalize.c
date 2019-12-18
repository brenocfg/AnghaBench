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
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */
 scalar_t__ IdChar (char const) ; 
#define  TK_ERROR 132 
#define  TK_LITERAL 131 
#define  TK_NAME 130 
#define  TK_PUNCT 129 
#define  TK_SPACE 128 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int sqlite3GetToken (unsigned char*,int*) ; 
 char sqlite3Tolower (char const) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (scalar_t__) ; 
 char* sqlite3_realloc64 (char*,int) ; 
 int /*<<< orphan*/  sqlite3_strnicmp (char const*,char*,int) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

char *sqlite3_normalize(const char *zSql){
  char *z;              /* The output string */
  sqlite3_int64 nZ;     /* Size of the output string in bytes */
  sqlite3_int64 nSql;   /* Size of the input string in bytes */
  int i;                /* Next character to read from zSql[] */
  int j;                /* Next slot to fill in on z[] */
  int tokenType;        /* Type of the next token */
  int n;                /* Size of the next token */
  int k;                /* Loop counter */

  nSql = strlen(zSql);
  nZ = nSql;
  z = sqlite3_malloc64( nZ+2 );
  if( z==0 ) return 0;
  for(i=j=0; zSql[i]; i += n){
    n = sqlite3GetToken((unsigned char*)zSql+i, &tokenType);
    switch( tokenType ){
      case TK_SPACE: {
        break;
      }
      case TK_ERROR: {
        sqlite3_free(z);
        return 0;
      }
      case TK_LITERAL: {
        z[j++] = '?';
        break;
      }
      case TK_PUNCT:
      case TK_NAME: {
        if( n==4 && sqlite3_strnicmp(zSql+i,"NULL",4)==0 ){
          if( (j>=3 && strncmp(z+j-2,"is",2)==0 && !IdChar(z[j-3]))
           || (j>=4 && strncmp(z+j-3,"not",3)==0 && !IdChar(z[j-4]))
          ){
            /* NULL is a keyword in this case, not a literal value */
          }else{
            /* Here the NULL is a literal value */
            z[j++] = '?';
            break;
          }
        }
        if( j>0 && IdChar(z[j-1]) && IdChar(zSql[i]) ) z[j++] = ' ';
        for(k=0; k<n; k++){
          z[j++] = sqlite3Tolower(zSql[i+k]);
        }
        break;
      }
    }
  }
  while( j>0 && z[j-1]==' ' ){ j--; }
  if( j>0 && z[j-1]!=';' ){ z[j++] = ';'; }
  z[j] = 0;

  /* Make a second pass converting "in(...)" where the "..." is not a
  ** SELECT statement into "in(?,?,?)" */
  for(i=0; i<j; i=n){
    char *zIn = strstr(z+i, "in(");
    int nParen;
    if( zIn==0 ) break;
    n = (int)(zIn-z)+3;  /* Index of first char past "in(" */
    if( n && IdChar(zIn[-1]) ) continue;
    if( strncmp(zIn, "in(select",9)==0 && !IdChar(zIn[9]) ) continue;
    if( strncmp(zIn, "in(with",7)==0 && !IdChar(zIn[7]) ) continue;
    for(nParen=1, k=0; z[n+k]; k++){
      if( z[n+k]=='(' ) nParen++;
      if( z[n+k]==')' ){
        nParen--;
        if( nParen==0 ) break;
      }
    }
    /* k is the number of bytes in the "..." within "in(...)" */
    if( k<5 ){
      z = sqlite3_realloc64(z, j+(5-k)+1);
      if( z==0 ) return 0;
      memmove(z+n+5, z+n+k, j-(n+k));
    }else if( k>5 ){
      memmove(z+n+5, z+n+k, j-(n+k));
    }
    j = j-k+5;
    z[j] = 0;
    memcpy(z+n, "?,?,?", 5);
  }
  return z;
}