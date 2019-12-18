#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nHier; scalar_t__* apHier; } ;
struct TYPE_7__ {TYPE_2__ hier; TYPE_1__* pDb; scalar_t__ pPage; } ;
struct TYPE_5__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_3__ MergeWorker ;

/* Variables and functions */
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  lsmFsPageRelease (scalar_t__) ; 

__attribute__((used)) static void mergeWorkerReleaseAll(MergeWorker *pMW){
  int i;
  lsmFsPageRelease(pMW->pPage);
  pMW->pPage = 0;

  for(i=0; i<pMW->hier.nHier; i++){
    lsmFsPageRelease(pMW->hier.apHier[i]);
    pMW->hier.apHier[i] = 0;
  }
  lsmFree(pMW->pDb->pEnv, pMW->hier.apHier);
  pMW->hier.apHier = 0;
  pMW->hier.nHier = 0;
}