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
struct TYPE_6__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ TestDb ;
struct TYPE_7__ {scalar_t__ bCrash; int nCrashSync; } ;
struct TYPE_5__ {scalar_t__ xClose; } ;
typedef  TYPE_3__ BtDb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bt_close ; 

void tdb_bt_prepare_sync_crash(TestDb *pTestDb, int iSync){
  BtDb *p = (BtDb*)pTestDb;
  assert( pTestDb->pMethods->xClose==bt_close );
  assert( p->bCrash==0 );
  p->nCrashSync = iSync;
}