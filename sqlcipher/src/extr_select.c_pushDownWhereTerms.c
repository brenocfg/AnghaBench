#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ op; int iRightJoinTable; struct TYPE_20__* pLeft; struct TYPE_20__* pRight; } ;
struct TYPE_19__ {int /*<<< orphan*/  db; } ;
struct TYPE_18__ {int selFlags; scalar_t__ pLimit; struct TYPE_18__* pPrior; void* pWhere; void* pHaving; int /*<<< orphan*/  pEList; scalar_t__ pWin; } ;
struct TYPE_17__ {int iTable; int iNewTable; int /*<<< orphan*/  pEList; scalar_t__ isLeftJoin; TYPE_3__* pParse; } ;
typedef  TYPE_1__ SubstContext ;
typedef  TYPE_2__ Select ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 scalar_t__ ExprHasProperty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int SF_Aggregate ; 
 int SF_Recursive ; 
 scalar_t__ TK_AND ; 
 int /*<<< orphan*/  assert (int) ; 
 void* sqlite3ExprAnd (int /*<<< orphan*/ ,void*,TYPE_4__*) ; 
 TYPE_4__* sqlite3ExprDup (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3ExprIsTableConstant (TYPE_4__*,int) ; 
 TYPE_4__* substExpr (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  unsetJoinExpr (TYPE_4__*,int) ; 

__attribute__((used)) static int pushDownWhereTerms(
  Parse *pParse,        /* Parse context (for malloc() and error reporting) */
  Select *pSubq,        /* The subquery whose WHERE clause is to be augmented */
  Expr *pWhere,         /* The WHERE clause of the outer query */
  int iCursor,          /* Cursor number of the subquery */
  int isLeftJoin        /* True if pSubq is the right term of a LEFT JOIN */
){
  Expr *pNew;
  int nChng = 0;
  if( pWhere==0 ) return 0;
  if( pSubq->selFlags & SF_Recursive ) return 0;  /* restriction (2) */

#ifndef SQLITE_OMIT_WINDOWFUNC
  if( pSubq->pWin ) return 0;    /* restriction (6) */
#endif

#ifdef SQLITE_DEBUG
  /* Only the first term of a compound can have a WITH clause.  But make
  ** sure no other terms are marked SF_Recursive in case something changes
  ** in the future.
  */
  {
    Select *pX;  
    for(pX=pSubq; pX; pX=pX->pPrior){
      assert( (pX->selFlags & (SF_Recursive))==0 );
    }
  }
#endif

  if( pSubq->pLimit!=0 ){
    return 0; /* restriction (3) */
  }
  while( pWhere->op==TK_AND ){
    nChng += pushDownWhereTerms(pParse, pSubq, pWhere->pRight,
                                iCursor, isLeftJoin);
    pWhere = pWhere->pLeft;
  }
  if( isLeftJoin
   && (ExprHasProperty(pWhere,EP_FromJoin)==0
         || pWhere->iRightJoinTable!=iCursor)
  ){
    return 0; /* restriction (4) */
  }
  if( ExprHasProperty(pWhere,EP_FromJoin) && pWhere->iRightJoinTable!=iCursor ){
    return 0; /* restriction (5) */
  }
  if( sqlite3ExprIsTableConstant(pWhere, iCursor) ){
    nChng++;
    while( pSubq ){
      SubstContext x;
      pNew = sqlite3ExprDup(pParse->db, pWhere, 0);
      unsetJoinExpr(pNew, -1);
      x.pParse = pParse;
      x.iTable = iCursor;
      x.iNewTable = iCursor;
      x.isLeftJoin = 0;
      x.pEList = pSubq->pEList;
      pNew = substExpr(&x, pNew);
      if( pSubq->selFlags & SF_Aggregate ){
        pSubq->pHaving = sqlite3ExprAnd(pParse->db, pSubq->pHaving, pNew);
      }else{
        pSubq->pWhere = sqlite3ExprAnd(pParse->db, pSubq->pWhere, pNew);
      }
      pSubq = pSubq->pPrior;
    }
  }
  return nChng;
}