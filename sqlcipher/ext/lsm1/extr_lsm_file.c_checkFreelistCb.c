#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_2__ {int nBlock; scalar_t__* aUsed; } ;
typedef  TYPE_1__ CheckFreelistCtx ;

/* Variables and functions */
 scalar_t__ INTEGRITY_CHECK_FREE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int checkFreelistCb(void *pCtx, int iBlk, i64 iSnapshot){
  CheckFreelistCtx *p = (CheckFreelistCtx *)pCtx;

  assert( iBlk>=1 );
  assert( iBlk<=p->nBlock );
  assert( p->aUsed[iBlk-1]==0 );
  p->aUsed[iBlk-1] = INTEGRITY_CHECK_FREE;
  return 0;
}