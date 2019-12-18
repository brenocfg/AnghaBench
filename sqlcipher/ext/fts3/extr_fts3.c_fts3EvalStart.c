#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ pVtab; } ;
struct TYPE_11__ {int /*<<< orphan*/  pExpr; TYPE_1__ base; } ;
struct TYPE_10__ {scalar_t__ bFts4; } ;
typedef  int /*<<< orphan*/  Fts3TokenAndCost ;
typedef  TYPE_2__ Fts3Table ;
typedef  int /*<<< orphan*/  Fts3Expr ;
typedef  TYPE_3__ Fts3Cursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts3EvalAllocateReaders (TYPE_3__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int fts3EvalSelectDeferred (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts3EvalStartReaders (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fts3EvalTokenCosts (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 

__attribute__((used)) static int fts3EvalStart(Fts3Cursor *pCsr){
  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
  int rc = SQLITE_OK;
  int nToken = 0;
  int nOr = 0;

  /* Allocate a MultiSegReader for each token in the expression. */
  fts3EvalAllocateReaders(pCsr, pCsr->pExpr, &nToken, &nOr, &rc);

  /* Determine which, if any, tokens in the expression should be deferred. */
#ifndef SQLITE_DISABLE_FTS4_DEFERRED
  if( rc==SQLITE_OK && nToken>1 && pTab->bFts4 ){
    Fts3TokenAndCost *aTC;
    Fts3Expr **apOr;
    aTC = (Fts3TokenAndCost *)sqlite3_malloc64(
        sizeof(Fts3TokenAndCost) * nToken
      + sizeof(Fts3Expr *) * nOr * 2
    );
    apOr = (Fts3Expr **)&aTC[nToken];

    if( !aTC ){
      rc = SQLITE_NOMEM;
    }else{
      int ii;
      Fts3TokenAndCost *pTC = aTC;
      Fts3Expr **ppOr = apOr;

      fts3EvalTokenCosts(pCsr, 0, pCsr->pExpr, &pTC, &ppOr, &rc);
      nToken = (int)(pTC-aTC);
      nOr = (int)(ppOr-apOr);

      if( rc==SQLITE_OK ){
        rc = fts3EvalSelectDeferred(pCsr, 0, aTC, nToken);
        for(ii=0; rc==SQLITE_OK && ii<nOr; ii++){
          rc = fts3EvalSelectDeferred(pCsr, apOr[ii], aTC, nToken);
        }
      }

      sqlite3_free(aTC);
    }
  }
#endif

  fts3EvalStartReaders(pCsr, pCsr->pExpr, &rc);
  return rc;
}