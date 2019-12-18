#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nToken; TYPE_1__* aToken; } ;
struct TYPE_6__ {scalar_t__ eType; int bDeferred; struct TYPE_6__* pRight; struct TYPE_6__* pLeft; TYPE_4__* pPhrase; } ;
struct TYPE_5__ {scalar_t__ pDeferred; } ;
typedef  TYPE_2__ Fts3Expr ;
typedef  int /*<<< orphan*/  Fts3Cursor ;

/* Variables and functions */
 scalar_t__ FTSQUERY_PHRASE ; 
 int SQLITE_OK ; 
 int fts3EvalPhraseStart (int /*<<< orphan*/ *,int,TYPE_4__*) ; 

__attribute__((used)) static void fts3EvalStartReaders(
  Fts3Cursor *pCsr,               /* FTS Cursor handle */
  Fts3Expr *pExpr,                /* Expression to initialize phrases in */
  int *pRc                        /* IN/OUT: Error code */
){
  if( pExpr && SQLITE_OK==*pRc ){
    if( pExpr->eType==FTSQUERY_PHRASE ){
      int nToken = pExpr->pPhrase->nToken;
      if( nToken ){
        int i;
        for(i=0; i<nToken; i++){
          if( pExpr->pPhrase->aToken[i].pDeferred==0 ) break;
        }
        pExpr->bDeferred = (i==nToken);
      }
      *pRc = fts3EvalPhraseStart(pCsr, 1, pExpr->pPhrase);
    }else{
      fts3EvalStartReaders(pCsr, pExpr->pLeft, pRc);
      fts3EvalStartReaders(pCsr, pExpr->pRight, pRc);
      pExpr->bDeferred = (pExpr->pLeft->bDeferred && pExpr->pRight->bDeferred);
    }
  }
}