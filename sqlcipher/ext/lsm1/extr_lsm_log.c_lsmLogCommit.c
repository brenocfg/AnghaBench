#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bUseLog; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_LOG_COMMIT ; 
 int LSM_OK ; 
 int logFlush (TYPE_1__*,int /*<<< orphan*/ ) ; 

int lsmLogCommit(lsm_db *pDb){
  if( pDb->bUseLog==0 ) return LSM_OK;
  return logFlush(pDb, LSM_LOG_COMMIT);
}