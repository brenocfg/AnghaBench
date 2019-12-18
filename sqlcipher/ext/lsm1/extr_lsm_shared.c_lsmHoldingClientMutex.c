#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pDatabase; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_4__ {int /*<<< orphan*/  pClientMutex; } ;

/* Variables and functions */
 int lsmMutexHeld (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lsmHoldingClientMutex(lsm_db *pDb){
  return lsmMutexHeld(pDb->pEnv, pDb->pDatabase->pClientMutex);
}