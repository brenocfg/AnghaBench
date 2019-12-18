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
struct TYPE_3__ {int n; int nAlloc; char* z; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ LsmString ;

/* Variables and functions */
 int LSM_NOMEM ; 
 int LSM_NOMEM_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,char*) ; 
 char* lsmRealloc (int /*<<< orphan*/ ,char*,int) ; 

int lsmStringExtend(LsmString *pStr, int nNew){
  assert( nNew>0 );
  if( pStr->n<0 ) return LSM_NOMEM;
  if( pStr->n + nNew >= pStr->nAlloc ){
    int nAlloc = pStr->n + nNew + 100;
    char *zNew = lsmRealloc(pStr->pEnv, pStr->z, nAlloc);
    if( zNew==0 ){
      lsmFree(pStr->pEnv, pStr->z);
      nAlloc = 0;
      pStr->n = -1;
    }
    pStr->nAlloc = nAlloc;
    pStr->z = zNew;
  }
  return (pStr->z ? LSM_OK : LSM_NOMEM_BKPT);
}