#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_7__ {TYPE_3__* a; } ;
struct TYPE_6__ {TYPE_3__* aEntry; } ;
struct TYPE_8__ {TYPE_2__ redirect; TYPE_1__ freelist; int /*<<< orphan*/  pLevel; } ;
typedef  TYPE_3__ Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  lsmSortedFreeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lsmFreeSnapshot(lsm_env *pEnv, Snapshot *p){
  if( p ){
    lsmSortedFreeLevel(pEnv, p->pLevel);
    lsmFree(pEnv, p->freelist.aEntry);
    lsmFree(pEnv, p->redirect.a);
    lsmFree(pEnv, p);
  }
}