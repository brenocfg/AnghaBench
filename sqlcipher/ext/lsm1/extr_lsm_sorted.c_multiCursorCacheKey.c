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
struct TYPE_6__ {int /*<<< orphan*/  key; TYPE_1__* pDb; int /*<<< orphan*/  eType; int /*<<< orphan*/ * aTree; } ;
struct TYPE_5__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_2__ MultiCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  multiCursorGetKey (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int*) ; 
 int sortedBlobSet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static void multiCursorCacheKey(MultiCursor *pCsr, int *pRc){
  if( *pRc==LSM_OK ){
    void *pKey;
    int nKey;
    multiCursorGetKey(pCsr, pCsr->aTree[1], &pCsr->eType, &pKey, &nKey);
    *pRc = sortedBlobSet(pCsr->pDb->pEnv, &pCsr->key, pKey, nKey);
  }
}