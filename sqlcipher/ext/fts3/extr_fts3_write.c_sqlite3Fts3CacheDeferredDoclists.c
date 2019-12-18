#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int (* xNext ) (int /*<<< orphan*/ *,char const**,int*,int*,int*,int*) ;int /*<<< orphan*/  (* xClose ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ sqlite3_tokenizer_module ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer_cursor ;
struct TYPE_12__ {TYPE_2__* pModule; } ;
typedef  TYPE_3__ sqlite3_tokenizer ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_10__ {scalar_t__ pVtab; } ;
struct TYPE_16__ {scalar_t__ isRequireSeek; TYPE_6__* pDeferred; int /*<<< orphan*/  iLangid; int /*<<< orphan*/  pStmt; TYPE_1__ base; } ;
struct TYPE_15__ {int iCol; scalar_t__ pList; struct TYPE_15__* pNext; TYPE_5__* pToken; } ;
struct TYPE_14__ {scalar_t__ bFirst; int n; int /*<<< orphan*/  z; scalar_t__ isPrefix; } ;
struct TYPE_13__ {int nColumn; scalar_t__* abNotindexed; TYPE_3__* pTokenizer; } ;
typedef  TYPE_4__ Fts3Table ;
typedef  TYPE_5__ Fts3PhraseToken ;
typedef  TYPE_6__ Fts3DeferredToken ;
typedef  TYPE_7__ Fts3Cursor ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3PendingListAppend (scalar_t__*,int /*<<< orphan*/ ,int,int,int*) ; 
 int fts3PendingListAppendVarint (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int sqlite3Fts3OpenTokenizer (TYPE_3__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ *,char const**,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

int sqlite3Fts3CacheDeferredDoclists(Fts3Cursor *pCsr){
  int rc = SQLITE_OK;             /* Return code */
  if( pCsr->pDeferred ){
    int i;                        /* Used to iterate through table columns */
    sqlite3_int64 iDocid;         /* Docid of the row pCsr points to */
    Fts3DeferredToken *pDef;      /* Used to iterate through deferred tokens */
  
    Fts3Table *p = (Fts3Table *)pCsr->base.pVtab;
    sqlite3_tokenizer *pT = p->pTokenizer;
    sqlite3_tokenizer_module const *pModule = pT->pModule;
   
    assert( pCsr->isRequireSeek==0 );
    iDocid = sqlite3_column_int64(pCsr->pStmt, 0);
  
    for(i=0; i<p->nColumn && rc==SQLITE_OK; i++){
      if( p->abNotindexed[i]==0 ){
        const char *zText = (const char *)sqlite3_column_text(pCsr->pStmt, i+1);
        sqlite3_tokenizer_cursor *pTC = 0;

        rc = sqlite3Fts3OpenTokenizer(pT, pCsr->iLangid, zText, -1, &pTC);
        while( rc==SQLITE_OK ){
          char const *zToken;       /* Buffer containing token */
          int nToken = 0;           /* Number of bytes in token */
          int iDum1 = 0, iDum2 = 0; /* Dummy variables */
          int iPos = 0;             /* Position of token in zText */

          rc = pModule->xNext(pTC, &zToken, &nToken, &iDum1, &iDum2, &iPos);
          for(pDef=pCsr->pDeferred; pDef && rc==SQLITE_OK; pDef=pDef->pNext){
            Fts3PhraseToken *pPT = pDef->pToken;
            if( (pDef->iCol>=p->nColumn || pDef->iCol==i)
                && (pPT->bFirst==0 || iPos==0)
                && (pPT->n==nToken || (pPT->isPrefix && pPT->n<nToken))
                && (0==memcmp(zToken, pPT->z, pPT->n))
              ){
              fts3PendingListAppend(&pDef->pList, iDocid, i, iPos, &rc);
            }
          }
        }
        if( pTC ) pModule->xClose(pTC);
        if( rc==SQLITE_DONE ) rc = SQLITE_OK;
      }
    }

    for(pDef=pCsr->pDeferred; pDef && rc==SQLITE_OK; pDef=pDef->pNext){
      if( pDef->pList ){
        rc = fts3PendingListAppendVarint(&pDef->pList, 0);
      }
    }
  }

  return rc;
}