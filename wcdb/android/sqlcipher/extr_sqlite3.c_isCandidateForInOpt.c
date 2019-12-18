#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ pSelect; } ;
typedef  TYPE_4__ Table ;
struct TYPE_13__ {TYPE_6__* pSelect; } ;
struct TYPE_20__ {scalar_t__ op; scalar_t__ iTable; TYPE_1__ x; } ;
struct TYPE_19__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_18__ {int selFlags; scalar_t__ pGroupBy; TYPE_7__* pEList; TYPE_5__* pSrc; scalar_t__ pWhere; scalar_t__ pLimit; scalar_t__ pPrior; } ;
struct TYPE_17__ {int nSrc; TYPE_3__* a; } ;
struct TYPE_15__ {scalar_t__ iCursor; TYPE_4__* pTab; scalar_t__ pSelect; } ;
struct TYPE_14__ {TYPE_8__* pExpr; } ;
typedef  TYPE_5__ SrcList ;
typedef  TYPE_6__ Select ;
typedef  TYPE_7__ ExprList ;
typedef  TYPE_8__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_VarSelect ; 
 int /*<<< orphan*/  EP_xIsSelect ; 
 scalar_t__ ExprHasProperty (TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IsVirtual (TYPE_4__*) ; 
 int SF_Aggregate ; 
 int SF_Distinct ; 
 scalar_t__ TK_COLUMN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static Select *isCandidateForInOpt(Expr *pX){
  Select *p;
  SrcList *pSrc;
  ExprList *pEList;
  Table *pTab;
  int i;
  if( !ExprHasProperty(pX, EP_xIsSelect) ) return 0;  /* Not a subquery */
  if( ExprHasProperty(pX, EP_VarSelect)  ) return 0;  /* Correlated subq */
  p = pX->x.pSelect;
  if( p->pPrior ) return 0;              /* Not a compound SELECT */
  if( p->selFlags & (SF_Distinct|SF_Aggregate) ){
    testcase( (p->selFlags & (SF_Distinct|SF_Aggregate))==SF_Distinct );
    testcase( (p->selFlags & (SF_Distinct|SF_Aggregate))==SF_Aggregate );
    return 0; /* No DISTINCT keyword and no aggregate functions */
  }
  assert( p->pGroupBy==0 );              /* Has no GROUP BY clause */
  if( p->pLimit ) return 0;              /* Has no LIMIT clause */
  if( p->pWhere ) return 0;              /* Has no WHERE clause */
  pSrc = p->pSrc;
  assert( pSrc!=0 );
  if( pSrc->nSrc!=1 ) return 0;          /* Single term in FROM clause */
  if( pSrc->a[0].pSelect ) return 0;     /* FROM is not a subquery or view */
  pTab = pSrc->a[0].pTab;
  assert( pTab!=0 );
  assert( pTab->pSelect==0 );            /* FROM clause is not a view */
  if( IsVirtual(pTab) ) return 0;        /* FROM clause not a virtual table */
  pEList = p->pEList;
  assert( pEList!=0 );
  /* All SELECT results must be columns. */
  for(i=0; i<pEList->nExpr; i++){
    Expr *pRes = pEList->a[i].pExpr;
    if( pRes->op!=TK_COLUMN ) return 0;
    assert( pRes->iTable==pSrc->a[0].iCursor );  /* Not a correlated subquery */
  }
  return p;
}