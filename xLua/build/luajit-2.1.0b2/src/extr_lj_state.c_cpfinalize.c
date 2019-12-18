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
typedef  int /*<<< orphan*/  lua_State ;
typedef  void* lua_CFunction ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  lj_gc_finalize_cdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_gc_finalize_udata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TValue *cpfinalize(lua_State *L, lua_CFunction dummy, void *ud)
{
  UNUSED(dummy);
  UNUSED(ud);
  lj_gc_finalize_cdata(L);
  lj_gc_finalize_udata(L);
  /* Frame pop omitted. */
  return NULL;
}