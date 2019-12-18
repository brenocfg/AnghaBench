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
struct TYPE_2__ {int* nowValue; } ;

/* Variables and functions */
 int ArraySize (int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3MallocMutex () ; 
 int /*<<< orphan*/  sqlite3Pcache1Mutex () ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int* statMutex ; 
 TYPE_1__ wsdStat ; 
 int /*<<< orphan*/  wsdStatInit ; 

void sqlite3StatusDown(int op, int N){
  wsdStatInit;
  assert( N>=0 );
  assert( op>=0 && op<ArraySize(statMutex) );
  assert( sqlite3_mutex_held(statMutex[op] ? sqlite3Pcache1Mutex()
                                           : sqlite3MallocMutex()) );
  assert( op>=0 && op<ArraySize(wsdStat.nowValue) );
  wsdStat.nowValue[op] -= N;
}