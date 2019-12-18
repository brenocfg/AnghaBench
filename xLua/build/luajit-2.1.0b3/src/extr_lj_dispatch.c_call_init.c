#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ base; scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_7__ {int numparams; int framesize; int flags; } ;
typedef  int /*<<< orphan*/  MSize ;
typedef  TYPE_2__ GCproto ;
typedef  int /*<<< orphan*/  GCfunc ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_MINSTACK ; 
 int PROTO_VARARG ; 
 TYPE_2__* funcproto (int /*<<< orphan*/ *) ; 
 scalar_t__ isluafunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_state_checkstack (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int call_init(lua_State *L, GCfunc *fn)
{
  if (isluafunc(fn)) {
    GCproto *pt = funcproto(fn);
    int numparams = pt->numparams;
    int gotparams = (int)(L->top - L->base);
    int need = pt->framesize;
    if ((pt->flags & PROTO_VARARG)) need += 1+gotparams;
    lj_state_checkstack(L, (MSize)need);
    numparams -= gotparams;
    return numparams >= 0 ? numparams : 0;
  } else {
    lj_state_checkstack(L, LUA_MINSTACK);
    return 0;
  }
}