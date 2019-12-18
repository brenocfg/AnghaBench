#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_52__   TYPE_8__ ;
typedef  struct TYPE_51__   TYPE_7__ ;
typedef  struct TYPE_50__   TYPE_6__ ;
typedef  struct TYPE_49__   TYPE_5__ ;
typedef  struct TYPE_48__   TYPE_4__ ;
typedef  struct TYPE_47__   TYPE_3__ ;
typedef  struct TYPE_46__   TYPE_36__ ;
typedef  struct TYPE_45__   TYPE_2__ ;
typedef  struct TYPE_44__   TYPE_1__ ;

/* Type definitions */
struct TYPE_47__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_3__ sqlite3 ;
struct TYPE_48__ {scalar_t__ iEphCsr; scalar_t__ regAccum; scalar_t__ regResult; int /*<<< orphan*/  pFilter; TYPE_2__* pOwner; scalar_t__ iArgCol; struct TYPE_48__* pNextWin; int /*<<< orphan*/  pOrderBy; int /*<<< orphan*/  pPartition; scalar_t__ nBufferCol; } ;
typedef  TYPE_4__ Window ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_52__ {scalar_t__ nExpr; } ;
struct TYPE_51__ {scalar_t__ nMem; scalar_t__ nTab; TYPE_3__* db; } ;
struct TYPE_50__ {scalar_t__ pPrior; int /*<<< orphan*/  selFlags; TYPE_5__* pSrc; scalar_t__ pOrderBy; scalar_t__ pEList; int /*<<< orphan*/ * pHaving; TYPE_8__* pGroupBy; int /*<<< orphan*/ * pWhere; TYPE_4__* pWin; } ;
struct TYPE_49__ {TYPE_36__* a; } ;
struct TYPE_46__ {TYPE_6__* pSelect; } ;
struct TYPE_44__ {int /*<<< orphan*/  pList; } ;
struct TYPE_45__ {TYPE_1__ x; } ;
typedef  TYPE_5__ SrcList ;
typedef  TYPE_6__ Select ;
typedef  TYPE_7__ Parse ;
typedef  TYPE_8__ ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Null ; 
 int /*<<< orphan*/  OP_OpenDup ; 
 int /*<<< orphan*/  OP_OpenEphemeral ; 
 int /*<<< orphan*/  SF_Aggregate ; 
 int /*<<< orphan*/  SF_Expanded ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TK_INTEGER ; 
 TYPE_8__* exprListAppendList (TYPE_7__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectWindowRewriteEList (TYPE_7__*,TYPE_4__*,TYPE_5__*,scalar_t__,TYPE_8__**) ; 
 scalar_t__ sqlite3ExpandSubquery (TYPE_7__*,TYPE_36__*) ; 
 int /*<<< orphan*/ * sqlite3ExprAlloc (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3ExprDup (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* sqlite3ExprListAppend (TYPE_7__*,TYPE_8__*,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3ExprListCompare (TYPE_8__*,scalar_t__,int) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (TYPE_3__*,scalar_t__) ; 
 TYPE_8__* sqlite3ExprListDup (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_7__*) ; 
 int /*<<< orphan*/ * sqlite3IntTokens ; 
 int /*<<< orphan*/  sqlite3SelectDelete (TYPE_3__*,TYPE_6__*) ; 
 TYPE_6__* sqlite3SelectNew (TYPE_7__*,TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SelectPrep (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* sqlite3SrcListAppend (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListAssignCursors (TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int sqlite3WindowRewrite(Parse *pParse, Select *p){
  int rc = SQLITE_OK;
  if( p->pWin && p->pPrior==0 ){
    Vdbe *v = sqlite3GetVdbe(pParse);
    sqlite3 *db = pParse->db;
    Select *pSub = 0;             /* The subquery */
    SrcList *pSrc = p->pSrc;
    Expr *pWhere = p->pWhere;
    ExprList *pGroupBy = p->pGroupBy;
    Expr *pHaving = p->pHaving;
    ExprList *pSort = 0;

    ExprList *pSublist = 0;       /* Expression list for sub-query */
    Window *pMWin = p->pWin;      /* Master window object */
    Window *pWin;                 /* Window object iterator */

    p->pSrc = 0;
    p->pWhere = 0;
    p->pGroupBy = 0;
    p->pHaving = 0;

    /* Create the ORDER BY clause for the sub-select. This is the concatenation
    ** of the window PARTITION and ORDER BY clauses. Then, if this makes it
    ** redundant, remove the ORDER BY from the parent SELECT.  */
    pSort = sqlite3ExprListDup(db, pMWin->pPartition, 0);
    pSort = exprListAppendList(pParse, pSort, pMWin->pOrderBy);
    if( pSort && p->pOrderBy ){
      if( sqlite3ExprListCompare(pSort, p->pOrderBy, -1)==0 ){
        sqlite3ExprListDelete(db, p->pOrderBy);
        p->pOrderBy = 0;
      }
    }

    /* Assign a cursor number for the ephemeral table used to buffer rows.
    ** The OpenEphemeral instruction is coded later, after it is known how
    ** many columns the table will have.  */
    pMWin->iEphCsr = pParse->nTab++;
    pParse->nTab += 3;

    selectWindowRewriteEList(pParse, pMWin, pSrc, p->pEList, &pSublist);
    selectWindowRewriteEList(pParse, pMWin, pSrc, p->pOrderBy, &pSublist);
    pMWin->nBufferCol = (pSublist ? pSublist->nExpr : 0);

    /* Append the PARTITION BY and ORDER BY expressions to the to the 
    ** sub-select expression list. They are required to figure out where 
    ** boundaries for partitions and sets of peer rows lie.  */
    pSublist = exprListAppendList(pParse, pSublist, pMWin->pPartition);
    pSublist = exprListAppendList(pParse, pSublist, pMWin->pOrderBy);

    /* Append the arguments passed to each window function to the
    ** sub-select expression list. Also allocate two registers for each
    ** window function - one for the accumulator, another for interim
    ** results.  */
    for(pWin=pMWin; pWin; pWin=pWin->pNextWin){
      pWin->iArgCol = (pSublist ? pSublist->nExpr : 0);
      pSublist = exprListAppendList(pParse, pSublist, pWin->pOwner->x.pList);
      if( pWin->pFilter ){
        Expr *pFilter = sqlite3ExprDup(db, pWin->pFilter, 0);
        pSublist = sqlite3ExprListAppend(pParse, pSublist, pFilter);
      }
      pWin->regAccum = ++pParse->nMem;
      pWin->regResult = ++pParse->nMem;
      sqlite3VdbeAddOp2(v, OP_Null, 0, pWin->regAccum);
    }

    /* If there is no ORDER BY or PARTITION BY clause, and the window
    ** function accepts zero arguments, and there are no other columns
    ** selected (e.g. "SELECT row_number() OVER () FROM t1"), it is possible
    ** that pSublist is still NULL here. Add a constant expression here to 
    ** keep everything legal in this case. 
    */
    if( pSublist==0 ){
      pSublist = sqlite3ExprListAppend(pParse, 0, 
          sqlite3ExprAlloc(db, TK_INTEGER, &sqlite3IntTokens[0], 0)
      );
    }

    pSub = sqlite3SelectNew(
        pParse, pSublist, pSrc, pWhere, pGroupBy, pHaving, pSort, 0, 0
    );
    p->pSrc = sqlite3SrcListAppend(pParse, 0, 0, 0);
    if( p->pSrc ){
      p->pSrc->a[0].pSelect = pSub;
      sqlite3SrcListAssignCursors(pParse, p->pSrc);
      if( sqlite3ExpandSubquery(pParse, &p->pSrc->a[0]) ){
        rc = SQLITE_NOMEM;
      }else{
        pSub->selFlags |= SF_Expanded;
        p->selFlags &= ~SF_Aggregate;
        sqlite3SelectPrep(pParse, pSub, 0);
      }

      sqlite3VdbeAddOp2(v, OP_OpenEphemeral, pMWin->iEphCsr, pSublist->nExpr);
      sqlite3VdbeAddOp2(v, OP_OpenDup, pMWin->iEphCsr+1, pMWin->iEphCsr);
      sqlite3VdbeAddOp2(v, OP_OpenDup, pMWin->iEphCsr+2, pMWin->iEphCsr);
      sqlite3VdbeAddOp2(v, OP_OpenDup, pMWin->iEphCsr+3, pMWin->iEphCsr);
    }else{
      sqlite3SelectDelete(db, pSub);
    }
    if( db->mallocFailed ) rc = SQLITE_NOMEM;
  }

  return rc;
}