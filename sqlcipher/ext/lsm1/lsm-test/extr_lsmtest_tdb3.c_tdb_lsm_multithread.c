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
struct TYPE_2__ {scalar_t__ eMode; } ;
typedef  TYPE_1__ LsmDb ;

/* Variables and functions */
 scalar_t__ LSMTEST_MODE_SINGLETHREAD ; 
 scalar_t__ tdb_lsm (int /*<<< orphan*/ *) ; 

int tdb_lsm_multithread(TestDb *pDb){
  int ret = 0;
  if( tdb_lsm(pDb) ){
    ret = ((LsmDb*)pDb)->eMode!=LSMTEST_MODE_SINGLETHREAD;
  }
  return ret;
}