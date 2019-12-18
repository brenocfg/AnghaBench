#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zName; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_1__ CollSeq ;

/* Variables and functions */
 TYPE_1__* sqlite3ExprNNCollSeq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3ExprCollSeqMatch(Parse *pParse, Expr *pE1, Expr *pE2){
  CollSeq *pColl1 = sqlite3ExprNNCollSeq(pParse, pE1);
  CollSeq *pColl2 = sqlite3ExprNNCollSeq(pParse, pE2);
  return sqlite3StrICmp(pColl1->zName, pColl2->zName)==0;
}