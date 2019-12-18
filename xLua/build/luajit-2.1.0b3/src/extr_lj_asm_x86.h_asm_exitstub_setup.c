#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ ** exitstubgroup; } ;
struct TYPE_5__ {TYPE_2__* J; } ;
typedef  int ExitNo ;
typedef  TYPE_1__ ASMState ;

/* Variables and functions */
 int EXITSTUBS_PER_GROUP ; 
 int LJ_MAX_EXITSTUBGR ; 
 int /*<<< orphan*/  LJ_TRERR_SNAPOV ; 
 int /*<<< orphan*/ * asm_exitstub_gen (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_exitstub_setup(ASMState *as, ExitNo nexits)
{
  ExitNo i;
  if (nexits >= EXITSTUBS_PER_GROUP*LJ_MAX_EXITSTUBGR)
    lj_trace_err(as->J, LJ_TRERR_SNAPOV);
  for (i = 0; i < (nexits+EXITSTUBS_PER_GROUP-1)/EXITSTUBS_PER_GROUP; i++)
    if (as->J->exitstubgroup[i] == NULL)
      as->J->exitstubgroup[i] = asm_exitstub_gen(as, i);
}