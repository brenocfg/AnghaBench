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
struct TYPE_4__ {scalar_t__ sizetrace; } ;
typedef  TYPE_1__ jit_State ;
typedef  scalar_t__ TraceNo ;
typedef  int /*<<< orphan*/  GCtrace ;

/* Variables and functions */
 TYPE_1__* L2J (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_lib_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * traceref (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static GCtrace *jit_checktrace(lua_State *L)
{
  TraceNo tr = (TraceNo)lj_lib_checkint(L, 1);
  jit_State *J = L2J(L);
  if (tr > 0 && tr < J->sizetrace)
    return traceref(J, tr);
  return NULL;
}