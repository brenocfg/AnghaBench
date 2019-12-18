#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_1__* pConfig; } ;
struct TYPE_21__ {int nPhrase; scalar_t__ pColset; TYPE_4__** apPhrase; } ;
struct TYPE_20__ {scalar_t__ iRowid; TYPE_6__* pNear; } ;
struct TYPE_15__ {int n; } ;
struct TYPE_19__ {int nTerm; TYPE_14__ poslist; TYPE_3__* aTerm; } ;
struct TYPE_18__ {TYPE_2__* pIter; scalar_t__ bFirst; struct TYPE_18__* pSynonym; } ;
struct TYPE_17__ {scalar_t__ iRowid; scalar_t__ nData; int /*<<< orphan*/  pData; } ;
struct TYPE_16__ {scalar_t__ eDetail; } ;
typedef  TYPE_2__ Fts5IndexIter ;
typedef  TYPE_3__ Fts5ExprTerm ;
typedef  TYPE_4__ Fts5ExprPhrase ;
typedef  TYPE_5__ Fts5ExprNode ;
typedef  TYPE_6__ Fts5ExprNearset ;
typedef  TYPE_7__ Fts5Expr ;

/* Variables and functions */
 scalar_t__ FTS5_DETAIL_FULL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5BufferSet (int*,TYPE_14__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fts5ExprNearIsMatch (int*,TYPE_6__*) ; 
 int fts5ExprPhraseIsMatch (TYPE_5__*,TYPE_4__*,int*) ; 
 scalar_t__ sqlite3Fts5IterEof (TYPE_2__*) ; 

__attribute__((used)) static int fts5ExprNearTest(
  int *pRc,
  Fts5Expr *pExpr,                /* Expression that pNear is a part of */
  Fts5ExprNode *pNode             /* The "NEAR" node (FTS5_STRING) */
){
  Fts5ExprNearset *pNear = pNode->pNear;
  int rc = *pRc;

  if( pExpr->pConfig->eDetail!=FTS5_DETAIL_FULL ){
    Fts5ExprTerm *pTerm;
    Fts5ExprPhrase *pPhrase = pNear->apPhrase[0];
    pPhrase->poslist.n = 0;
    for(pTerm=&pPhrase->aTerm[0]; pTerm; pTerm=pTerm->pSynonym){
      Fts5IndexIter *pIter = pTerm->pIter;
      if( sqlite3Fts5IterEof(pIter)==0 ){
        if( pIter->iRowid==pNode->iRowid && pIter->nData>0 ){
          pPhrase->poslist.n = 1;
        }
      }
    }
    return pPhrase->poslist.n;
  }else{
    int i;

    /* Check that each phrase in the nearset matches the current row.
    ** Populate the pPhrase->poslist buffers at the same time. If any
    ** phrase is not a match, break out of the loop early.  */
    for(i=0; rc==SQLITE_OK && i<pNear->nPhrase; i++){
      Fts5ExprPhrase *pPhrase = pNear->apPhrase[i];
      if( pPhrase->nTerm>1 || pPhrase->aTerm[0].pSynonym 
       || pNear->pColset || pPhrase->aTerm[0].bFirst
      ){
        int bMatch = 0;
        rc = fts5ExprPhraseIsMatch(pNode, pPhrase, &bMatch);
        if( bMatch==0 ) break;
      }else{
        Fts5IndexIter *pIter = pPhrase->aTerm[0].pIter;
        fts5BufferSet(&rc, &pPhrase->poslist, pIter->nData, pIter->pData);
      }
    }

    *pRc = rc;
    if( i==pNear->nPhrase && (i==1 || fts5ExprNearIsMatch(pRc, pNear)) ){
      return 1;
    }
    return 0;
  }
}