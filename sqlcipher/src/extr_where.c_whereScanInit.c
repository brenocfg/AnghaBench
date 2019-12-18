#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  WhereTerm ;
struct TYPE_15__ {int* aiCur; int nEquiv; int iEquiv; int* aiColumn; scalar_t__ zCollName; scalar_t__ idxaff; scalar_t__ pIdxExpr; scalar_t__ k; int /*<<< orphan*/  opMask; int /*<<< orphan*/ * pWC; int /*<<< orphan*/ * pOrigWC; } ;
typedef  TYPE_5__ WhereScan ;
typedef  int /*<<< orphan*/  WhereClause ;
struct TYPE_16__ {int* aiColumn; scalar_t__* azColl; TYPE_4__* pTable; TYPE_2__* aColExpr; } ;
struct TYPE_14__ {int iPKey; TYPE_3__* aCol; } ;
struct TYPE_13__ {scalar_t__ affinity; } ;
struct TYPE_12__ {TYPE_1__* a; } ;
struct TYPE_11__ {scalar_t__ pExpr; } ;
typedef  TYPE_6__ Index ;

/* Variables and functions */
 int XN_EXPR ; 
 int XN_ROWID ; 
 int /*<<< orphan*/ * whereScanInitIndexExpr (TYPE_5__*) ; 
 int /*<<< orphan*/ * whereScanNext (TYPE_5__*) ; 

__attribute__((used)) static WhereTerm *whereScanInit(
  WhereScan *pScan,       /* The WhereScan object being initialized */
  WhereClause *pWC,       /* The WHERE clause to be scanned */
  int iCur,               /* Cursor to scan for */
  int iColumn,            /* Column to scan for */
  u32 opMask,             /* Operator(s) to scan for */
  Index *pIdx             /* Must be compatible with this index */
){
  pScan->pOrigWC = pWC;
  pScan->pWC = pWC;
  pScan->pIdxExpr = 0;
  pScan->idxaff = 0;
  pScan->zCollName = 0;
  pScan->opMask = opMask;
  pScan->k = 0;
  pScan->aiCur[0] = iCur;
  pScan->nEquiv = 1;
  pScan->iEquiv = 1;
  if( pIdx ){
    int j = iColumn;
    iColumn = pIdx->aiColumn[j];
    if( iColumn==XN_EXPR ){
      pScan->pIdxExpr = pIdx->aColExpr->a[j].pExpr;
      pScan->zCollName = pIdx->azColl[j];
      pScan->aiColumn[0] = XN_EXPR;
      return whereScanInitIndexExpr(pScan);
    }else if( iColumn==pIdx->pTable->iPKey ){
      iColumn = XN_ROWID;
    }else if( iColumn>=0 ){
      pScan->idxaff = pIdx->pTable->aCol[iColumn].affinity;
      pScan->zCollName = pIdx->azColl[j];
    }
  }else if( iColumn==XN_EXPR ){
    return 0;
  }
  pScan->aiColumn[0] = iColumn;
  return whereScanNext(pScan);
}