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
typedef  int /*<<< orphan*/  CidxCursor ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  cidxCursorError (int /*<<< orphan*/ *,char*,char*) ; 
 char** cidxMalloc (int*,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_free (char**) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int cidxDecodeAfter(
  CidxCursor *pCsr, 
  int nCol, 
  const char *zAfterKey, 
  char ***pazAfter
){
  char **azAfter;
  int rc = SQLITE_OK;
  int nAfterKey = (int)strlen(zAfterKey);

  azAfter = cidxMalloc(&rc, sizeof(char*)*nCol + nAfterKey+1);
  if( rc==SQLITE_OK ){
    int i;
    char *zCopy = (char*)&azAfter[nCol];
    char *p = zCopy;
    memcpy(zCopy, zAfterKey, nAfterKey+1);
    for(i=0; i<nCol; i++){
      while( *p==' ' ) p++;

      /* Check NULL values */
      if( *p=='N' ){
        if( memcmp(p, "NULL", 4) ) goto parse_error;
        p += 4;
      }

      /* Check strings and blob literals */
      else if( *p=='X' || *p=='\'' ){
        azAfter[i] = p;
        if( *p=='X' ) p++;
        if( *p!='\'' ) goto parse_error;
        p++;
        while( 1 ){
          if( *p=='\0' ) goto parse_error;
          if( *p=='\'' ){
            p++;
            if( *p!='\'' ) break;
          }
          p++;
        }
      }

      /* Check numbers */
      else{
        azAfter[i] = p;
        while( (*p>='0' && *p<='9') 
            || *p=='.' || *p=='+' || *p=='-' || *p=='e' || *p=='E'
        ){
          p++;
        }
      }

      while( *p==' ' ) p++;
      if( *p!=(i==(nCol-1) ? '\0' : ',') ){
        goto parse_error;
      }
      *p++ = '\0';
    }
  }

  *pazAfter = azAfter;
  return rc;

 parse_error:
  sqlite3_free(azAfter);
  *pazAfter = 0;
  cidxCursorError(pCsr, "%s", "error parsing after value");
  return SQLITE_ERROR;
}