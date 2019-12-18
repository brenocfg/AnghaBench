#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  w ;
struct IdxCover {int iCur; int /*<<< orphan*/ * pIdx; } ;
struct TYPE_5__ {struct IdxCover* pIdxCover; } ;
struct TYPE_6__ {int /*<<< orphan*/  eCode; TYPE_1__ u; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_2__ Walker ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  exprIdxCover ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_2__*,int /*<<< orphan*/ *) ; 

int sqlite3ExprCoveredByIndex(
  Expr *pExpr,        /* The index to be tested */
  int iCur,           /* The cursor number for the corresponding table */
  Index *pIdx         /* The index that might be used for coverage */
){
  Walker w;
  struct IdxCover xcov;
  memset(&w, 0, sizeof(w));
  xcov.iCur = iCur;
  xcov.pIdx = pIdx;
  w.xExprCallback = exprIdxCover;
  w.u.pIdxCover = &xcov;
  sqlite3WalkExpr(&w, pExpr);
  return !w.eCode;
}