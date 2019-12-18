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
typedef  int /*<<< orphan*/  pStr ;
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_4__ {int /*<<< orphan*/ * pEnv; } ;
typedef  TYPE_1__ LsmString ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void lsmStringInit(LsmString *pStr, lsm_env *pEnv){
  memset(pStr, 0, sizeof(pStr[0]));
  pStr->pEnv = pEnv;
}