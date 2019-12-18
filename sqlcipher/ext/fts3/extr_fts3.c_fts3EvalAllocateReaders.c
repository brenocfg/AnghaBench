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
struct TYPE_7__ {scalar_t__ eType; struct TYPE_7__* pRight; struct TYPE_7__* pLeft; TYPE_1__* pPhrase; } ;
struct TYPE_6__ {int /*<<< orphan*/  pSegcsr; int /*<<< orphan*/  isPrefix; int /*<<< orphan*/  n; int /*<<< orphan*/  z; } ;
struct TYPE_5__ {int nToken; int iDoclistToken; TYPE_2__* aToken; } ;
typedef  TYPE_2__ Fts3PhraseToken ;
typedef  TYPE_3__ Fts3Expr ;
typedef  int /*<<< orphan*/  Fts3Cursor ;

/* Variables and functions */
 scalar_t__ FTSQUERY_OR ; 
 scalar_t__ FTSQUERY_PHRASE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3TermSegReaderCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts3EvalAllocateReaders(
  Fts3Cursor *pCsr,               /* FTS cursor handle */
  Fts3Expr *pExpr,                /* Allocate readers for this expression */
  int *pnToken,                   /* OUT: Total number of tokens in phrase. */
  int *pnOr,                      /* OUT: Total number of OR nodes in expr. */
  int *pRc                        /* IN/OUT: Error code */
){
  if( pExpr && SQLITE_OK==*pRc ){
    if( pExpr->eType==FTSQUERY_PHRASE ){
      int i;
      int nToken = pExpr->pPhrase->nToken;
      *pnToken += nToken;
      for(i=0; i<nToken; i++){
        Fts3PhraseToken *pToken = &pExpr->pPhrase->aToken[i];
        int rc = fts3TermSegReaderCursor(pCsr, 
            pToken->z, pToken->n, pToken->isPrefix, &pToken->pSegcsr
        );
        if( rc!=SQLITE_OK ){
          *pRc = rc;
          return;
        }
      }
      assert( pExpr->pPhrase->iDoclistToken==0 );
      pExpr->pPhrase->iDoclistToken = -1;
    }else{
      *pnOr += (pExpr->eType==FTSQUERY_OR);
      fts3EvalAllocateReaders(pCsr, pExpr->pLeft, pnToken, pnOr, pRc);
      fts3EvalAllocateReaders(pCsr, pExpr->pRight, pnToken, pnOr, pRc);
    }
  }
}