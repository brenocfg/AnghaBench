#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct SrcList_item {int iCursor; int /*<<< orphan*/  pTab; } ;
typedef  int /*<<< orphan*/  sSum ;
struct TYPE_27__ {TYPE_3__* pAndInfo; TYPE_2__* pOrInfo; } ;
struct TYPE_29__ {int eOperator; int leftCursor; TYPE_4__ u; } ;
typedef  TYPE_6__ WhereTerm ;
struct TYPE_30__ {int n; TYPE_5__* a; } ;
typedef  TYPE_7__ WhereOrSet ;
struct TYPE_31__ {TYPE_11__* pWC; TYPE_7__* pOrSet; scalar_t__ pOrderBy; TYPE_9__* pNew; TYPE_10__* pWInfo; } ;
typedef  TYPE_8__ WhereLoopBuilder ;
struct TYPE_32__ {int iTab; int maskSelf; int nLTerm; int prereq; scalar_t__ nOut; scalar_t__ rRun; TYPE_7__ u; scalar_t__ iSortIdx; scalar_t__ rSetup; int /*<<< orphan*/  wsFlags; TYPE_6__** aLTerm; } ;
typedef  TYPE_9__ WhereLoop ;
struct TYPE_22__ {TYPE_1__* pTabList; } ;
typedef  TYPE_10__ WhereInfo ;
struct TYPE_23__ {int nTerm; TYPE_6__* a; int /*<<< orphan*/  op; struct TYPE_23__* pOuter; int /*<<< orphan*/  pWInfo; } ;
typedef  TYPE_11__ WhereClause ;
struct TYPE_28__ {int prereq; scalar_t__ nOut; scalar_t__ rRun; } ;
struct TYPE_26__ {TYPE_11__ wc; } ;
struct TYPE_25__ {int indexable; TYPE_11__ wc; } ;
struct TYPE_24__ {struct SrcList_item* a; } ;
typedef  int /*<<< orphan*/  Bitmask ;

/* Variables and functions */
 scalar_t__ IsVirtual (int /*<<< orphan*/ ) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TK_AND ; 
 int /*<<< orphan*/  WHERETRACE (int,char*) ; 
 int /*<<< orphan*/  WHERE_MULTI_OR ; 
 int WO_AND ; 
 int WO_OR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3LogEstAdd (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3WhereClausePrint (TYPE_11__*) ; 
 int sqlite3WhereTrace ; 
 int whereLoopAddBtree (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int whereLoopAddVirtual (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int whereLoopInsert (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  whereOrInsert (TYPE_7__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whereOrMove (TYPE_7__*,TYPE_7__*) ; 

__attribute__((used)) static int whereLoopAddOr(
  WhereLoopBuilder *pBuilder, 
  Bitmask mPrereq, 
  Bitmask mUnusable
){
  WhereInfo *pWInfo = pBuilder->pWInfo;
  WhereClause *pWC;
  WhereLoop *pNew;
  WhereTerm *pTerm, *pWCEnd;
  int rc = SQLITE_OK;
  int iCur;
  WhereClause tempWC;
  WhereLoopBuilder sSubBuild;
  WhereOrSet sSum, sCur;
  struct SrcList_item *pItem;
  
  pWC = pBuilder->pWC;
  pWCEnd = pWC->a + pWC->nTerm;
  pNew = pBuilder->pNew;
  memset(&sSum, 0, sizeof(sSum));
  pItem = pWInfo->pTabList->a + pNew->iTab;
  iCur = pItem->iCursor;

  for(pTerm=pWC->a; pTerm<pWCEnd && rc==SQLITE_OK; pTerm++){
    if( (pTerm->eOperator & WO_OR)!=0
     && (pTerm->u.pOrInfo->indexable & pNew->maskSelf)!=0 
    ){
      WhereClause * const pOrWC = &pTerm->u.pOrInfo->wc;
      WhereTerm * const pOrWCEnd = &pOrWC->a[pOrWC->nTerm];
      WhereTerm *pOrTerm;
      int once = 1;
      int i, j;
    
      sSubBuild = *pBuilder;
      sSubBuild.pOrderBy = 0;
      sSubBuild.pOrSet = &sCur;

      WHERETRACE(0x200, ("Begin processing OR-clause %p\n", pTerm));
      for(pOrTerm=pOrWC->a; pOrTerm<pOrWCEnd; pOrTerm++){
        if( (pOrTerm->eOperator & WO_AND)!=0 ){
          sSubBuild.pWC = &pOrTerm->u.pAndInfo->wc;
        }else if( pOrTerm->leftCursor==iCur ){
          tempWC.pWInfo = pWC->pWInfo;
          tempWC.pOuter = pWC;
          tempWC.op = TK_AND;
          tempWC.nTerm = 1;
          tempWC.a = pOrTerm;
          sSubBuild.pWC = &tempWC;
        }else{
          continue;
        }
        sCur.n = 0;
#ifdef WHERETRACE_ENABLED
        WHERETRACE(0x200, ("OR-term %d of %p has %d subterms:\n", 
                   (int)(pOrTerm-pOrWC->a), pTerm, sSubBuild.pWC->nTerm));
        if( sqlite3WhereTrace & 0x400 ){
          sqlite3WhereClausePrint(sSubBuild.pWC);
        }
#endif
#ifndef SQLITE_OMIT_VIRTUALTABLE
        if( IsVirtual(pItem->pTab) ){
          rc = whereLoopAddVirtual(&sSubBuild, mPrereq, mUnusable);
        }else
#endif
        {
          rc = whereLoopAddBtree(&sSubBuild, mPrereq);
        }
        if( rc==SQLITE_OK ){
          rc = whereLoopAddOr(&sSubBuild, mPrereq, mUnusable);
        }
        assert( rc==SQLITE_OK || sCur.n==0 );
        if( sCur.n==0 ){
          sSum.n = 0;
          break;
        }else if( once ){
          whereOrMove(&sSum, &sCur);
          once = 0;
        }else{
          WhereOrSet sPrev;
          whereOrMove(&sPrev, &sSum);
          sSum.n = 0;
          for(i=0; i<sPrev.n; i++){
            for(j=0; j<sCur.n; j++){
              whereOrInsert(&sSum, sPrev.a[i].prereq | sCur.a[j].prereq,
                            sqlite3LogEstAdd(sPrev.a[i].rRun, sCur.a[j].rRun),
                            sqlite3LogEstAdd(sPrev.a[i].nOut, sCur.a[j].nOut));
            }
          }
        }
      }
      pNew->nLTerm = 1;
      pNew->aLTerm[0] = pTerm;
      pNew->wsFlags = WHERE_MULTI_OR;
      pNew->rSetup = 0;
      pNew->iSortIdx = 0;
      memset(&pNew->u, 0, sizeof(pNew->u));
      for(i=0; rc==SQLITE_OK && i<sSum.n; i++){
        /* TUNING: Currently sSum.a[i].rRun is set to the sum of the costs
        ** of all sub-scans required by the OR-scan. However, due to rounding
        ** errors, it may be that the cost of the OR-scan is equal to its
        ** most expensive sub-scan. Add the smallest possible penalty 
        ** (equivalent to multiplying the cost by 1.07) to ensure that 
        ** this does not happen. Otherwise, for WHERE clauses such as the
        ** following where there is an index on "y":
        **
        **     WHERE likelihood(x=?, 0.99) OR y=?
        **
        ** the planner may elect to "OR" together a full-table scan and an
        ** index lookup. And other similarly odd results.  */
        pNew->rRun = sSum.a[i].rRun + 1;
        pNew->nOut = sSum.a[i].nOut;
        pNew->prereq = sSum.a[i].prereq;
        rc = whereLoopInsert(pBuilder, pNew);
      }
      WHERETRACE(0x200, ("End processing OR-clause %p\n", pTerm));
    }
  }
  return rc;
}