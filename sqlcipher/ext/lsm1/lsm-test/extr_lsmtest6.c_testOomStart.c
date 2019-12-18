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
struct TYPE_4__ {int iNext; int bEnable; int nFail; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ OomTest ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tdb_lsm_env () ; 

__attribute__((used)) static void testOomStart(OomTest *p){
  memset(p, 0, sizeof(OomTest));
  p->iNext = 1;
  p->bEnable = 1;
  p->nFail = 1;
  p->pEnv = tdb_lsm_env();
}