#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int sqlite3_int64 ;
struct TYPE_3__ {unsigned char* aTokenChar; char* aFold; int nFold; int /*<<< orphan*/  eRemoveDiacritic; } ;
typedef  TYPE_1__ Unicode61Tokenizer ;
typedef  int /*<<< orphan*/  Fts5Tokenizer ;

/* Variables and functions */
 int /*<<< orphan*/  READ_UTF8 (unsigned char*,unsigned char*,scalar_t__) ; 
 int SQLITE_DONE ; 
 int /*<<< orphan*/  SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAM (int) ; 
 int /*<<< orphan*/  WRITE_UTF8 (char*,scalar_t__) ; 
 scalar_t__ fts5UnicodeIsAlnum (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ sqlite3Fts5UnicodeFold (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3Fts5UnicodeIsdiacritic (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (int) ; 

__attribute__((used)) static int fts5UnicodeTokenize(
  Fts5Tokenizer *pTokenizer,
  void *pCtx,
  int iUnused,
  const char *pText, int nText,
  int (*xToken)(void*, int, const char*, int nToken, int iStart, int iEnd)
){
  Unicode61Tokenizer *p = (Unicode61Tokenizer*)pTokenizer;
  int rc = SQLITE_OK;
  unsigned char *a = p->aTokenChar;

  unsigned char *zTerm = (unsigned char*)&pText[nText];
  unsigned char *zCsr = (unsigned char *)pText;

  /* Output buffer */
  char *aFold = p->aFold;
  int nFold = p->nFold;
  const char *pEnd = &aFold[nFold-6];

  UNUSED_PARAM(iUnused);

  /* Each iteration of this loop gobbles up a contiguous run of separators,
  ** then the next token.  */
  while( rc==SQLITE_OK ){
    u32 iCode;                    /* non-ASCII codepoint read from input */
    char *zOut = aFold;
    int is;
    int ie;

    /* Skip any separator characters. */
    while( 1 ){
      if( zCsr>=zTerm ) goto tokenize_done;
      if( *zCsr & 0x80 ) {
        /* A character outside of the ascii range. Skip past it if it is
        ** a separator character. Or break out of the loop if it is not. */
        is = zCsr - (unsigned char*)pText;
        READ_UTF8(zCsr, zTerm, iCode);
        if( fts5UnicodeIsAlnum(p, iCode) ){
          goto non_ascii_tokenchar;
        }
      }else{
        if( a[*zCsr] ){
          is = zCsr - (unsigned char*)pText;
          goto ascii_tokenchar;
        }
        zCsr++;
      }
    }

    /* Run through the tokenchars. Fold them into the output buffer along
    ** the way.  */
    while( zCsr<zTerm ){

      /* Grow the output buffer so that there is sufficient space to fit the
      ** largest possible utf-8 character.  */
      if( zOut>pEnd ){
        aFold = sqlite3_malloc64((sqlite3_int64)nFold*2);
        if( aFold==0 ){
          rc = SQLITE_NOMEM;
          goto tokenize_done;
        }
        zOut = &aFold[zOut - p->aFold];
        memcpy(aFold, p->aFold, nFold);
        sqlite3_free(p->aFold);
        p->aFold = aFold;
        p->nFold = nFold = nFold*2;
        pEnd = &aFold[nFold-6];
      }

      if( *zCsr & 0x80 ){
        /* An non-ascii-range character. Fold it into the output buffer if
        ** it is a token character, or break out of the loop if it is not. */
        READ_UTF8(zCsr, zTerm, iCode);
        if( fts5UnicodeIsAlnum(p,iCode)||sqlite3Fts5UnicodeIsdiacritic(iCode) ){
 non_ascii_tokenchar:
          iCode = sqlite3Fts5UnicodeFold(iCode, p->eRemoveDiacritic);
          if( iCode ) WRITE_UTF8(zOut, iCode);
        }else{
          break;
        }
      }else if( a[*zCsr]==0 ){
        /* An ascii-range separator character. End of token. */
        break; 
      }else{
 ascii_tokenchar:
        if( *zCsr>='A' && *zCsr<='Z' ){
          *zOut++ = *zCsr + 32;
        }else{
          *zOut++ = *zCsr;
        }
        zCsr++;
      }
      ie = zCsr - (unsigned char*)pText;
    }

    /* Invoke the token callback */
    rc = xToken(pCtx, 0, aFold, zOut-aFold, is, ie); 
  }
  
 tokenize_done:
  if( rc==SQLITE_DONE ) rc = SQLITE_OK;
  return rc;
}