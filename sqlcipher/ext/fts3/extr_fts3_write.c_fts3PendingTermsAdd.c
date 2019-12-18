#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct Fts3Index {int nPrefix; int /*<<< orphan*/  hPending; } ;
struct TYPE_7__ {int (* xNext ) (int /*<<< orphan*/ *,char const**,int*,int*,int*,int*) ;int /*<<< orphan*/  (* xClose ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ sqlite3_tokenizer_module ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer_cursor ;
struct TYPE_8__ {TYPE_1__* pModule; } ;
typedef  TYPE_2__ sqlite3_tokenizer ;
struct TYPE_9__ {int nIndex; struct Fts3Index* aIndex; TYPE_2__* pTokenizer; } ;
typedef  TYPE_3__ Fts3Table ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3PendingTermsAddOne (TYPE_3__*,int,int,int /*<<< orphan*/ *,char const*,int) ; 
 int sqlite3Fts3OpenTokenizer (TYPE_2__*,int,char const*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3PendingTermsAdd(
  Fts3Table *p,                   /* Table into which text will be inserted */
  int iLangid,                    /* Language id to use */
  const char *zText,              /* Text of document to be inserted */
  int iCol,                       /* Column into which text is being inserted */
  u32 *pnWord                     /* IN/OUT: Incr. by number tokens inserted */
){
  int rc;
  int iStart = 0;
  int iEnd = 0;
  int iPos = 0;
  int nWord = 0;

  char const *zToken;
  int nToken = 0;

  sqlite3_tokenizer *pTokenizer = p->pTokenizer;
  sqlite3_tokenizer_module const *pModule = pTokenizer->pModule;
  sqlite3_tokenizer_cursor *pCsr;
  int (*xNext)(sqlite3_tokenizer_cursor *pCursor,
      const char**,int*,int*,int*,int*);

  assert( pTokenizer && pModule );

  /* If the user has inserted a NULL value, this function may be called with
  ** zText==0. In this case, add zero token entries to the hash table and 
  ** return early. */
  if( zText==0 ){
    *pnWord = 0;
    return SQLITE_OK;
  }

  rc = sqlite3Fts3OpenTokenizer(pTokenizer, iLangid, zText, -1, &pCsr);
  if( rc!=SQLITE_OK ){
    return rc;
  }

  xNext = pModule->xNext;
  while( SQLITE_OK==rc
      && SQLITE_OK==(rc = xNext(pCsr, &zToken, &nToken, &iStart, &iEnd, &iPos))
  ){
    int i;
    if( iPos>=nWord ) nWord = iPos+1;

    /* Positions cannot be negative; we use -1 as a terminator internally.
    ** Tokens must have a non-zero length.
    */
    if( iPos<0 || !zToken || nToken<=0 ){
      rc = SQLITE_ERROR;
      break;
    }

    /* Add the term to the terms index */
    rc = fts3PendingTermsAddOne(
        p, iCol, iPos, &p->aIndex[0].hPending, zToken, nToken
    );
    
    /* Add the term to each of the prefix indexes that it is not too 
    ** short for. */
    for(i=1; rc==SQLITE_OK && i<p->nIndex; i++){
      struct Fts3Index *pIndex = &p->aIndex[i];
      if( nToken<pIndex->nPrefix ) continue;
      rc = fts3PendingTermsAddOne(
          p, iCol, iPos, &pIndex->hPending, zToken, pIndex->nPrefix
      );
    }
  }

  pModule->xClose(pCsr);
  *pnWord += nWord;
  return (rc==SQLITE_DONE ? SQLITE_OK : rc);
}