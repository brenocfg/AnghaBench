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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_4__ {scalar_t__ sizebc; } ;
typedef  TYPE_1__ GCproto ;
typedef  int /*<<< orphan*/  GCfunc ;
typedef  scalar_t__ BCPos ;
typedef  int BCLine ;

/* Variables and functions */
 scalar_t__ NO_BCPOS ; 
 scalar_t__ debug_framepc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* funcproto (int /*<<< orphan*/ *) ; 
 int lj_debug_line (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static BCLine debug_frameline(lua_State *L, GCfunc *fn, cTValue *nextframe)
{
  BCPos pc = debug_framepc(L, fn, nextframe);
  if (pc != NO_BCPOS) {
    GCproto *pt = funcproto(fn);
    lua_assert(pc <= pt->sizebc);
    return lj_debug_line(pt, pc);
  }
  return -1;
}