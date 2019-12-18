#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  eRemoveDiacritic; } ;
typedef  TYPE_2__ unicode_tokenizer ;
struct TYPE_5__ {scalar_t__ pTokenizer; } ;
struct TYPE_7__ {unsigned char* aInput; size_t iOff; size_t nInput; char* zToken; int nAlloc; int /*<<< orphan*/  iToken; TYPE_1__ base; } ;
typedef  TYPE_3__ unicode_cursor ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer_cursor ;

/* Variables and functions */
 int /*<<< orphan*/  READ_UTF8 (unsigned char const*,unsigned char const*,unsigned int) ; 
 int SQLITE_DONE ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  WRITE_UTF8 (char*,int) ; 
 int sqlite3FtsUnicodeFold (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3FtsUnicodeIsdiacritic (int) ; 
 char* sqlite3_realloc64 (char*,int) ; 
 scalar_t__ unicodeIsAlnum (TYPE_2__*,int) ; 

__attribute__((used)) static int unicodeNext(
  sqlite3_tokenizer_cursor *pC,   /* Cursor returned by simpleOpen */
  const char **paToken,           /* OUT: Token text */
  int *pnToken,                   /* OUT: Number of bytes at *paToken */
  int *piStart,                   /* OUT: Starting offset of token */
  int *piEnd,                     /* OUT: Ending offset of token */
  int *piPos                      /* OUT: Position integer of token */
){
  unicode_cursor *pCsr = (unicode_cursor *)pC;
  unicode_tokenizer *p = ((unicode_tokenizer *)pCsr->base.pTokenizer);
  unsigned int iCode = 0;
  char *zOut;
  const unsigned char *z = &pCsr->aInput[pCsr->iOff];
  const unsigned char *zStart = z;
  const unsigned char *zEnd;
  const unsigned char *zTerm = &pCsr->aInput[pCsr->nInput];

  /* Scan past any delimiter characters before the start of the next token.
  ** Return SQLITE_DONE early if this takes us all the way to the end of 
  ** the input.  */
  while( z<zTerm ){
    READ_UTF8(z, zTerm, iCode);
    if( unicodeIsAlnum(p, (int)iCode) ) break;
    zStart = z;
  }
  if( zStart>=zTerm ) return SQLITE_DONE;

  zOut = pCsr->zToken;
  do {
    int iOut;

    /* Grow the output buffer if required. */
    if( (zOut-pCsr->zToken)>=(pCsr->nAlloc-4) ){
      char *zNew = sqlite3_realloc64(pCsr->zToken, pCsr->nAlloc+64);
      if( !zNew ) return SQLITE_NOMEM;
      zOut = &zNew[zOut - pCsr->zToken];
      pCsr->zToken = zNew;
      pCsr->nAlloc += 64;
    }

    /* Write the folded case of the last character read to the output */
    zEnd = z;
    iOut = sqlite3FtsUnicodeFold((int)iCode, p->eRemoveDiacritic);
    if( iOut ){
      WRITE_UTF8(zOut, iOut);
    }

    /* If the cursor is not at EOF, read the next character */
    if( z>=zTerm ) break;
    READ_UTF8(z, zTerm, iCode);
  }while( unicodeIsAlnum(p, (int)iCode) 
       || sqlite3FtsUnicodeIsdiacritic((int)iCode)
  );

  /* Set the output variables and return. */
  pCsr->iOff = (int)(z - pCsr->aInput);
  *paToken = pCsr->zToken;
  *pnToken = (int)(zOut - pCsr->zToken);
  *piStart = (int)(zStart - pCsr->aInput);
  *piEnd = (int)(zEnd - pCsr->aInput);
  *piPos = pCsr->iToken++;
  return SQLITE_OK;
}