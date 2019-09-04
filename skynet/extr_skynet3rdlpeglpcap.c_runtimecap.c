#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_13__ {char const* s; scalar_t__ valuecached; TYPE_1__* cap; int /*<<< orphan*/ * L; } ;
struct TYPE_12__ {char const* s; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ Capture ;
typedef  TYPE_2__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  Cclose ; 
 scalar_t__ Cgroup ; 
 int /*<<< orphan*/  LUA_MULTRET ; 
 int /*<<< orphan*/  SUBJIDX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ captype (TYPE_1__*) ; 
 int finddyncap (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* findopen (TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pushluaval (TYPE_2__*) ; 
 int pushnestedvalues (TYPE_2__*,int /*<<< orphan*/ ) ; 

int runtimecap (CapState *cs, Capture *close, const char *s, int *rem) {
  int n, id;
  lua_State *L = cs->L;
  int otop = lua_gettop(L);
  Capture *open = findopen(close);
  assert(captype(open) == Cgroup);
  id = finddyncap(open, close);  /* get first dynamic capture argument */
  close->kind = Cclose;  /* closes the group */
  close->s = s;
  cs->cap = open; cs->valuecached = 0;  /* prepare capture state */
  luaL_checkstack(L, 4, "too many runtime captures");
  pushluaval(cs);  /* push function to be called */
  lua_pushvalue(L, SUBJIDX);  /* push original subject */
  lua_pushinteger(L, s - cs->s + 1);  /* push current position */
  n = pushnestedvalues(cs, 0);  /* push nested captures */
  lua_call(L, n + 2, LUA_MULTRET);  /* call dynamic function */
  if (id > 0) {  /* are there old dynamic captures to be removed? */
    int i;
    for (i = id; i <= otop; i++)
      lua_remove(L, id);  /* remove old dynamic captures */
    *rem = otop - id + 1;  /* total number of dynamic captures removed */
  }
  else
    *rem = 0;  /* no dynamic captures removed */
  return close - open;  /* number of captures of all kinds removed */
}