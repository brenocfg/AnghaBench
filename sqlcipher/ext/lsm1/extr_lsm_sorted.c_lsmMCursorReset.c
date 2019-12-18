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
struct TYPE_4__ {scalar_t__ nData; } ;
struct TYPE_5__ {int nPtr; TYPE_1__ key; int /*<<< orphan*/ * aPtr; int /*<<< orphan*/ * apTreeCsr; } ;
typedef  TYPE_2__ MultiCursor ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_SEGMENTPTR_FREE_THRESHOLD ; 
 int /*<<< orphan*/  lsmTreeCursorReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  segmentPtrReset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lsmMCursorReset(MultiCursor *pCsr){
  int i;
  lsmTreeCursorReset(pCsr->apTreeCsr[0]);
  lsmTreeCursorReset(pCsr->apTreeCsr[1]);
  for(i=0; i<pCsr->nPtr; i++){
    segmentPtrReset(&pCsr->aPtr[i], LSM_SEGMENTPTR_FREE_THRESHOLD);
  }
  pCsr->key.nData = 0;
}