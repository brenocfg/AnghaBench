#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {char const* src; char const* p; int /*<<< orphan*/ * lastmatch; int /*<<< orphan*/  ms; } ;
typedef  TYPE_1__ GMatchState ;

/* Variables and functions */
 int /*<<< orphan*/  gmatch_aux ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prepstate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,size_t,char const*,size_t) ; 

__attribute__((used)) static int gmatch (lua_State *L) {
  size_t ls, lp;
  const char *s = luaL_checklstring(L, 1, &ls);
  const char *p = luaL_checklstring(L, 2, &lp);
  GMatchState *gm;
  lua_settop(L, 2);  /* keep them on closure to avoid being collected */
  gm = (GMatchState *)lua_newuserdata(L, sizeof(GMatchState));
  prepstate(&gm->ms, L, s, ls, p, lp);
  gm->src = s; gm->p = p; gm->lastmatch = NULL;
  lua_pushcclosure(L, gmatch_aux, 3);
  return 1;
}