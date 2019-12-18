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
struct TYPE_3__ {int /*<<< orphan*/ * pExpr; } ;
typedef  TYPE_1__ Fts5Parse ;
typedef  int /*<<< orphan*/  Fts5ExprNode ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void sqlite3Fts5ParseFinished(Fts5Parse *pParse, Fts5ExprNode *p){
  assert( pParse->pExpr==0 );
  pParse->pExpr = p;
}