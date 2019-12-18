#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_18__ {int nPhrase; TYPE_2__* pRoot; TYPE_1__* pConfig; TYPE_6__** apExprPhrase; } ;
struct TYPE_17__ {scalar_t__ bEof; scalar_t__ iRowid; } ;
struct TYPE_13__ {scalar_t__ n; } ;
struct TYPE_16__ {TYPE_5__* aTerm; TYPE_3__ poslist; TYPE_7__* pNode; } ;
struct TYPE_15__ {TYPE_4__* pIter; int /*<<< orphan*/ * pSynonym; } ;
struct TYPE_14__ {int nData; int /*<<< orphan*/ * pData; } ;
struct TYPE_12__ {scalar_t__ iRowid; } ;
struct TYPE_11__ {scalar_t__ eDetail; } ;
typedef  TYPE_5__ Fts5ExprTerm ;
typedef  TYPE_6__ Fts5ExprPhrase ;
typedef  TYPE_7__ Fts5ExprNode ;
typedef  TYPE_8__ Fts5Expr ;
typedef  int /*<<< orphan*/  Fts5Buffer ;

/* Variables and functions */
 scalar_t__ FTS5_DETAIL_COLUMNS ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts5ExprSynonymList (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 

int sqlite3Fts5ExprPhraseCollist(
  Fts5Expr *pExpr, 
  int iPhrase, 
  const u8 **ppCollist, 
  int *pnCollist
){
  Fts5ExprPhrase *pPhrase = pExpr->apExprPhrase[iPhrase];
  Fts5ExprNode *pNode = pPhrase->pNode;
  int rc = SQLITE_OK;

  assert( iPhrase>=0 && iPhrase<pExpr->nPhrase );
  assert( pExpr->pConfig->eDetail==FTS5_DETAIL_COLUMNS );

  if( pNode->bEof==0 
   && pNode->iRowid==pExpr->pRoot->iRowid 
   && pPhrase->poslist.n>0
  ){
    Fts5ExprTerm *pTerm = &pPhrase->aTerm[0];
    if( pTerm->pSynonym ){
      Fts5Buffer *pBuf = (Fts5Buffer*)&pTerm->pSynonym[1];
      rc = fts5ExprSynonymList(
          pTerm, pNode->iRowid, pBuf, (u8**)ppCollist, pnCollist
      );
    }else{
      *ppCollist = pPhrase->aTerm[0].pIter->pData;
      *pnCollist = pPhrase->aTerm[0].pIter->nData;
    }
  }else{
    *ppCollist = 0;
    *pnCollist = 0;
  }

  return rc;
}