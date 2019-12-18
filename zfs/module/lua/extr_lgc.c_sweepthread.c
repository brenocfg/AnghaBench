#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  openupval; int /*<<< orphan*/ * stack; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_10__ {scalar_t__ gckind; } ;

/* Variables and functions */
 TYPE_7__* G (TYPE_1__*) ; 
 scalar_t__ KGC_EMERGENCY ; 
 int /*<<< orphan*/  luaD_shrinkstack (TYPE_1__*) ; 
 int /*<<< orphan*/  luaE_freeCI (TYPE_1__*) ; 
 int /*<<< orphan*/  sweepwholelist (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sweepthread (lua_State *L, lua_State *L1) {
  if (L1->stack == NULL) return;  /* stack not completely built yet */
  sweepwholelist(L, &L1->openupval);  /* sweep open upvalues */
  luaE_freeCI(L1);  /* free extra CallInfo slots */
  /* should not change the stack during an emergency gc cycle */
  if (G(L)->gckind != KGC_EMERGENCY)
    luaD_shrinkstack(L1);
}