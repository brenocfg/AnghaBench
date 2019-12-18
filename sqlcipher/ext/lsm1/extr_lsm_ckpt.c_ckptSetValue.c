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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int nAlloc; int /*<<< orphan*/ * aCkpt; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ CkptBuffer ;

/* Variables and functions */
 int LSM_MAX (int,int) ; 
 int LSM_NOMEM_BKPT ; 
 scalar_t__ lsmReallocOrFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ckptSetValue(CkptBuffer *p, int iIdx, u32 iVal, int *pRc){
  if( *pRc ) return;
  if( iIdx>=p->nAlloc ){
    int nNew = LSM_MAX(8, iIdx*2);
    p->aCkpt = (u32 *)lsmReallocOrFree(p->pEnv, p->aCkpt, nNew*sizeof(u32));
    if( !p->aCkpt ){
      *pRc = LSM_NOMEM_BKPT;
      return;
    }
    p->nAlloc = nNew;
  }
  p->aCkpt[iIdx] = iVal;
}