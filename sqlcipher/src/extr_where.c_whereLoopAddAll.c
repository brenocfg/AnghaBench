#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_17__ {int jointype; } ;
struct SrcList_item {int /*<<< orphan*/  iCursor; TYPE_2__ fg; int /*<<< orphan*/  pTab; } ;
struct TYPE_19__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_4__ sqlite3 ;
struct TYPE_20__ {TYPE_3__* pWC; int /*<<< orphan*/  iPlanLimit; TYPE_6__* pNew; TYPE_7__* pWInfo; } ;
typedef  TYPE_5__ WhereLoopBuilder ;
struct TYPE_21__ {int iTab; int /*<<< orphan*/  maskSelf; } ;
typedef  TYPE_6__ WhereLoop ;
struct TYPE_22__ {size_t nLevel; int /*<<< orphan*/  sMaskSet; TYPE_1__* pParse; TYPE_8__* pTabList; } ;
typedef  TYPE_7__ WhereInfo ;
struct TYPE_23__ {struct SrcList_item* a; } ;
struct TYPE_18__ {scalar_t__ hasOr; } ;
struct TYPE_16__ {TYPE_4__* db; } ;
typedef  TYPE_8__ SrcList ;
typedef  int /*<<< orphan*/  Bitmask ;

/* Variables and functions */
 scalar_t__ IsVirtual (int /*<<< orphan*/ ) ; 
 int JT_CROSS ; 
 int JT_LEFT ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_QUERY_PLANNER_LIMIT ; 
 scalar_t__ SQLITE_QUERY_PLANNER_LIMIT_INCR ; 
 int /*<<< orphan*/  SQLITE_WARNING ; 
 int /*<<< orphan*/  sqlite3WhereGetMask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*) ; 
 int whereLoopAddBtree (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int whereLoopAddOr (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int whereLoopAddVirtual (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whereLoopClear (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  whereLoopInit (TYPE_6__*) ; 

__attribute__((used)) static int whereLoopAddAll(WhereLoopBuilder *pBuilder){
  WhereInfo *pWInfo = pBuilder->pWInfo;
  Bitmask mPrereq = 0;
  Bitmask mPrior = 0;
  int iTab;
  SrcList *pTabList = pWInfo->pTabList;
  struct SrcList_item *pItem;
  struct SrcList_item *pEnd = &pTabList->a[pWInfo->nLevel];
  sqlite3 *db = pWInfo->pParse->db;
  int rc = SQLITE_OK;
  WhereLoop *pNew;
  u8 priorJointype = 0;

  /* Loop over the tables in the join, from left to right */
  pNew = pBuilder->pNew;
  whereLoopInit(pNew);
  pBuilder->iPlanLimit = SQLITE_QUERY_PLANNER_LIMIT;
  for(iTab=0, pItem=pTabList->a; pItem<pEnd; iTab++, pItem++){
    Bitmask mUnusable = 0;
    pNew->iTab = iTab;
    pBuilder->iPlanLimit += SQLITE_QUERY_PLANNER_LIMIT_INCR;
    pNew->maskSelf = sqlite3WhereGetMask(&pWInfo->sMaskSet, pItem->iCursor);
    if( ((pItem->fg.jointype|priorJointype) & (JT_LEFT|JT_CROSS))!=0 ){
      /* This condition is true when pItem is the FROM clause term on the
      ** right-hand-side of a LEFT or CROSS JOIN.  */
      mPrereq = mPrior;
    }
    priorJointype = pItem->fg.jointype;
#ifndef SQLITE_OMIT_VIRTUALTABLE
    if( IsVirtual(pItem->pTab) ){
      struct SrcList_item *p;
      for(p=&pItem[1]; p<pEnd; p++){
        if( mUnusable || (p->fg.jointype & (JT_LEFT|JT_CROSS)) ){
          mUnusable |= sqlite3WhereGetMask(&pWInfo->sMaskSet, p->iCursor);
        }
      }
      rc = whereLoopAddVirtual(pBuilder, mPrereq, mUnusable);
    }else
#endif /* SQLITE_OMIT_VIRTUALTABLE */
    {
      rc = whereLoopAddBtree(pBuilder, mPrereq);
    }
    if( rc==SQLITE_OK && pBuilder->pWC->hasOr ){
      rc = whereLoopAddOr(pBuilder, mPrereq, mUnusable);
    }
    mPrior |= pNew->maskSelf;
    if( rc || db->mallocFailed ){
      if( rc==SQLITE_DONE ){
        /* We hit the query planner search limit set by iPlanLimit */
        sqlite3_log(SQLITE_WARNING, "abbreviated query algorithm search");
        rc = SQLITE_OK;
      }else{
        break;
      }
    }
  }

  whereLoopClear(db, pNew);
  return rc;
}