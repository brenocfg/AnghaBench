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
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_2__ {int nAutoCrash; int bPrepareCrash; } ;
typedef  TYPE_1__ LsmDb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ tdb_lsm (int /*<<< orphan*/ *) ; 

void tdb_lsm_prepare_sync_crash(TestDb *pDb, int iSync){
  assert( iSync>0 );
  if( tdb_lsm(pDb) ){
    LsmDb *p = (LsmDb *)pDb;
    p->nAutoCrash = iSync;
    p->bPrepareCrash = 1;
  }
}