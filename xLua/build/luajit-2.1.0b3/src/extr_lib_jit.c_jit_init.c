#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  param; } ;
typedef  TYPE_1__ jit_State ;

/* Variables and functions */
 int /*<<< orphan*/  G (int /*<<< orphan*/ *) ; 
 int JIT_F_ON ; 
 int JIT_F_OPT_DEFAULT ; 
 TYPE_1__* L2J (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int jit_cpudetect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jit_param_default ; 
 int /*<<< orphan*/  lj_dispatch_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void jit_init(lua_State *L)
{
  uint32_t flags = jit_cpudetect(L);
#if LJ_HASJIT
  jit_State *J = L2J(L);
  J->flags = flags | JIT_F_ON | JIT_F_OPT_DEFAULT;
  memcpy(J->param, jit_param_default, sizeof(J->param));
  lj_dispatch_update(G(L));
#else
  UNUSED(flags);
#endif
}