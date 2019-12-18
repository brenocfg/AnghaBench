#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_5__ {int nPtr; scalar_t__ pBtCsr; scalar_t__* apTreeCsr; int /*<<< orphan*/ * pSystemVal; int /*<<< orphan*/ * aTree; scalar_t__ nTree; int /*<<< orphan*/ * aPtr; TYPE_1__* pDb; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pEnv; } ;
typedef  TYPE_2__ MultiCursor ;

/* Variables and functions */
 int /*<<< orphan*/  btreeCursorFree (scalar_t__) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmTreeCursorDestroy (scalar_t__) ; 
 int /*<<< orphan*/  segmentPtrReset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcursorFreeComponents(MultiCursor *pCsr){
  int i;
  lsm_env *pEnv = pCsr->pDb->pEnv;

  /* Close the tree cursor, if any. */
  lsmTreeCursorDestroy(pCsr->apTreeCsr[0]);
  lsmTreeCursorDestroy(pCsr->apTreeCsr[1]);

  /* Reset the segment pointers */
  for(i=0; i<pCsr->nPtr; i++){
    segmentPtrReset(&pCsr->aPtr[i], 0);
  }

  /* And the b-tree cursor, if any */
  btreeCursorFree(pCsr->pBtCsr);

  /* Free allocations */
  lsmFree(pEnv, pCsr->aPtr);
  lsmFree(pEnv, pCsr->aTree);
  lsmFree(pEnv, pCsr->pSystemVal);

  /* Zero fields */
  pCsr->nPtr = 0;
  pCsr->aPtr = 0;
  pCsr->nTree = 0;
  pCsr->aTree = 0;
  pCsr->pSystemVal = 0;
  pCsr->apTreeCsr[0] = 0;
  pCsr->apTreeCsr[1] = 0;
  pCsr->pBtCsr = 0;
}