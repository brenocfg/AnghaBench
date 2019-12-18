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
typedef  int /*<<< orphan*/  WhereInfo ;
struct TYPE_3__ {int /*<<< orphan*/  aStatic; int /*<<< orphan*/  a; int /*<<< orphan*/  nSlot; scalar_t__ nTerm; scalar_t__ pOuter; scalar_t__ hasOr; int /*<<< orphan*/ * pWInfo; } ;
typedef  TYPE_1__ WhereClause ;

/* Variables and functions */
 int /*<<< orphan*/  ArraySize (int /*<<< orphan*/ ) ; 

void sqlite3WhereClauseInit(
  WhereClause *pWC,        /* The WhereClause to be initialized */
  WhereInfo *pWInfo        /* The WHERE processing context */
){
  pWC->pWInfo = pWInfo;
  pWC->hasOr = 0;
  pWC->pOuter = 0;
  pWC->nTerm = 0;
  pWC->nSlot = ArraySize(pWC->aStatic);
  pWC->a = pWC->aStatic;
}