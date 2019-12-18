#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ eType; struct TYPE_12__* pRight; struct TYPE_12__* pLeft; TYPE_3__* pPhrase; } ;
struct TYPE_11__ {int nToken; int /*<<< orphan*/  iColumn; TYPE_1__* aToken; } ;
struct TYPE_10__ {int iToken; int /*<<< orphan*/  nOvfl; TYPE_1__* pToken; int /*<<< orphan*/  iCol; TYPE_4__* pRoot; TYPE_3__* pPhrase; } ;
struct TYPE_9__ {int /*<<< orphan*/  pSegcsr; } ;
typedef  TYPE_2__ Fts3TokenAndCost ;
typedef  TYPE_3__ Fts3Phrase ;
typedef  TYPE_4__ Fts3Expr ;
typedef  int /*<<< orphan*/  Fts3Cursor ;

/* Variables and functions */
 scalar_t__ FTSQUERY_AND ; 
 scalar_t__ FTSQUERY_NEAR ; 
 scalar_t__ FTSQUERY_NOT ; 
 scalar_t__ FTSQUERY_OR ; 
 scalar_t__ FTSQUERY_PHRASE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3Fts3MsrOvfl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts3EvalTokenCosts(
  Fts3Cursor *pCsr,               /* FTS Cursor handle */
  Fts3Expr *pRoot,                /* Root of current AND/NEAR cluster */
  Fts3Expr *pExpr,                /* Expression to consider */
  Fts3TokenAndCost **ppTC,        /* Write new entries to *(*ppTC)++ */
  Fts3Expr ***ppOr,               /* Write new OR root to *(*ppOr)++ */
  int *pRc                        /* IN/OUT: Error code */
){
  if( *pRc==SQLITE_OK ){
    if( pExpr->eType==FTSQUERY_PHRASE ){
      Fts3Phrase *pPhrase = pExpr->pPhrase;
      int i;
      for(i=0; *pRc==SQLITE_OK && i<pPhrase->nToken; i++){
        Fts3TokenAndCost *pTC = (*ppTC)++;
        pTC->pPhrase = pPhrase;
        pTC->iToken = i;
        pTC->pRoot = pRoot;
        pTC->pToken = &pPhrase->aToken[i];
        pTC->iCol = pPhrase->iColumn;
        *pRc = sqlite3Fts3MsrOvfl(pCsr, pTC->pToken->pSegcsr, &pTC->nOvfl);
      }
    }else if( pExpr->eType!=FTSQUERY_NOT ){
      assert( pExpr->eType==FTSQUERY_OR
           || pExpr->eType==FTSQUERY_AND
           || pExpr->eType==FTSQUERY_NEAR
      );
      assert( pExpr->pLeft && pExpr->pRight );
      if( pExpr->eType==FTSQUERY_OR ){
        pRoot = pExpr->pLeft;
        **ppOr = pRoot;
        (*ppOr)++;
      }
      fts3EvalTokenCosts(pCsr, pRoot, pExpr->pLeft, ppTC, ppOr, pRc);
      if( pExpr->eType==FTSQUERY_OR ){
        pRoot = pExpr->pRight;
        **ppOr = pRoot;
        (*ppOr)++;
      }
      fts3EvalTokenCosts(pCsr, pRoot, pExpr->pRight, ppTC, ppOr, pRc);
    }
  }
}