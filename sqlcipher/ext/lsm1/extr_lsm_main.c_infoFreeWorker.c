#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_db ;

/* Variables and functions */
 int LSM_BUSY ; 
 int /*<<< orphan*/  lsmFinishWork (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void infoFreeWorker(lsm_db *pDb, int bUnlock){
  if( bUnlock ){
    int rcdummy = LSM_BUSY;
    lsmFinishWork(pDb, 0, &rcdummy);
  }
}