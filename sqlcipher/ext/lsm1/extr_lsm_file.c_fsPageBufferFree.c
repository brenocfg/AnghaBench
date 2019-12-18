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
struct TYPE_6__ {TYPE_1__* pFS; struct TYPE_6__* aData; } ;
struct TYPE_5__ {int /*<<< orphan*/  pEnv; int /*<<< orphan*/  nCacheAlloc; } ;
typedef  TYPE_2__ Page ;

/* Variables and functions */
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void fsPageBufferFree(Page *pPg){
  pPg->pFS->nCacheAlloc--;
  lsmFree(pPg->pFS->pEnv, pPg->aData);
  lsmFree(pPg->pFS->pEnv, pPg);
}