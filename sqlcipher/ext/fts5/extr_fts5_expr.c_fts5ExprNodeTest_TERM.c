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
struct TYPE_18__ {TYPE_3__* pConfig; } ;
struct TYPE_17__ {scalar_t__ eType; int bNomatch; int /*<<< orphan*/  iRowid; TYPE_1__* pNear; } ;
struct TYPE_14__ {scalar_t__ n; int /*<<< orphan*/ * p; } ;
struct TYPE_16__ {int nTerm; TYPE_4__ poslist; TYPE_2__* aTerm; } ;
struct TYPE_15__ {scalar_t__ nData; int /*<<< orphan*/  iRowid; scalar_t__ pData; } ;
struct TYPE_13__ {scalar_t__ eDetail; } ;
struct TYPE_12__ {scalar_t__ pSynonym; TYPE_5__* pIter; } ;
struct TYPE_11__ {int nPhrase; TYPE_6__** apPhrase; } ;
typedef  TYPE_5__ Fts5IndexIter ;
typedef  TYPE_6__ Fts5ExprPhrase ;
typedef  TYPE_7__ Fts5ExprNode ;
typedef  TYPE_8__ Fts5Expr ;

/* Variables and functions */
 scalar_t__ FTS5_DETAIL_FULL ; 
 scalar_t__ FTS5_TERM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int fts5ExprNodeTest_TERM(
  Fts5Expr *pExpr,                /* Expression that pNear is a part of */
  Fts5ExprNode *pNode             /* The "NEAR" node (FTS5_TERM) */
){
  /* As this "NEAR" object is actually a single phrase that consists 
  ** of a single term only, grab pointers into the poslist managed by the
  ** fts5_index.c iterator object. This is much faster than synthesizing 
  ** a new poslist the way we have to for more complicated phrase or NEAR
  ** expressions.  */
  Fts5ExprPhrase *pPhrase = pNode->pNear->apPhrase[0];
  Fts5IndexIter *pIter = pPhrase->aTerm[0].pIter;

  assert( pNode->eType==FTS5_TERM );
  assert( pNode->pNear->nPhrase==1 && pPhrase->nTerm==1 );
  assert( pPhrase->aTerm[0].pSynonym==0 );

  pPhrase->poslist.n = pIter->nData;
  if( pExpr->pConfig->eDetail==FTS5_DETAIL_FULL ){
    pPhrase->poslist.p = (u8*)pIter->pData;
  }
  pNode->iRowid = pIter->iRowid;
  pNode->bNomatch = (pPhrase->poslist.n==0);
  return SQLITE_OK;
}