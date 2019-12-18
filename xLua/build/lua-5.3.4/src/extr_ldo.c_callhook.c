#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {int /*<<< orphan*/ * savedpc; } ;
struct TYPE_11__ {TYPE_3__ l; } ;
struct TYPE_13__ {TYPE_4__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  savedpc; } ;
struct TYPE_9__ {TYPE_1__ l; } ;
struct TYPE_12__ {TYPE_2__ u; int /*<<< orphan*/  callstatus; TYPE_6__* previous; } ;
typedef  TYPE_5__ CallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CIST_TAIL ; 
 scalar_t__ GET_OPCODE (int /*<<< orphan*/ ) ; 
 int LUA_HOOKCALL ; 
 int LUA_HOOKTAILCALL ; 
 scalar_t__ OP_TAILCALL ; 
 scalar_t__ isLua (TYPE_6__*) ; 
 int /*<<< orphan*/  luaD_hook (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void callhook (lua_State *L, CallInfo *ci) {
  int hook = LUA_HOOKCALL;
  ci->u.l.savedpc++;  /* hooks assume 'pc' is already incremented */
  if (isLua(ci->previous) &&
      GET_OPCODE(*(ci->previous->u.l.savedpc - 1)) == OP_TAILCALL) {
    ci->callstatus |= CIST_TAIL;
    hook = LUA_HOOKTAILCALL;
  }
  luaD_hook(L, hook, -1);
  ci->u.l.savedpc--;  /* correct 'pc' */
}