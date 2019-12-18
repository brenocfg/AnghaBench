#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  aFold ;
struct TYPE_2__ {unsigned char* aTokenChar; } ;
typedef  int /*<<< orphan*/  Fts5Tokenizer ;
typedef  TYPE_1__ AsciiTokenizer ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int /*<<< orphan*/  SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAM (int) ; 
 int /*<<< orphan*/  asciiFold (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (int) ; 

__attribute__((used)) static int fts5AsciiTokenize(
  Fts5Tokenizer *pTokenizer,
  void *pCtx,
  int iUnused,
  const char *pText, int nText,
  int (*xToken)(void*, int, const char*, int nToken, int iStart, int iEnd)
){
  AsciiTokenizer *p = (AsciiTokenizer*)pTokenizer;
  int rc = SQLITE_OK;
  int ie;
  int is = 0;

  char aFold[64];
  int nFold = sizeof(aFold);
  char *pFold = aFold;
  unsigned char *a = p->aTokenChar;

  UNUSED_PARAM(iUnused);

  while( is<nText && rc==SQLITE_OK ){
    int nByte;

    /* Skip any leading divider characters. */
    while( is<nText && ((pText[is]&0x80)==0 && a[(int)pText[is]]==0) ){
      is++;
    }
    if( is==nText ) break;

    /* Count the token characters */
    ie = is+1;
    while( ie<nText && ((pText[ie]&0x80) || a[(int)pText[ie]] ) ){
      ie++;
    }

    /* Fold to lower case */
    nByte = ie-is;
    if( nByte>nFold ){
      if( pFold!=aFold ) sqlite3_free(pFold);
      pFold = sqlite3_malloc64((sqlite3_int64)nByte*2);
      if( pFold==0 ){
        rc = SQLITE_NOMEM;
        break;
      }
      nFold = nByte*2;
    }
    asciiFold(pFold, &pText[is], nByte);

    /* Invoke the token callback */
    rc = xToken(pCtx, 0, pFold, nByte, is, ie);
    is = ie+1;
  }
  
  if( pFold!=aFold ) sqlite3_free(pFold);
  if( rc==SQLITE_DONE ) rc = SQLITE_OK;
  return rc;
}