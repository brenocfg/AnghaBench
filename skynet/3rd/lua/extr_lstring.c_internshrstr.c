#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_13__ {int size; int nuse; TYPE_4__** hash; } ;
struct TYPE_14__ {TYPE_2__ strt; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_12__ {TYPE_4__* hnext; } ;
struct TYPE_15__ {size_t shrlen; TYPE_1__ u; } ;
typedef  TYPE_4__ TString ;

/* Variables and functions */
 TYPE_3__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LUA_TSHRSTR ; 
 int MAX_INT ; 
 int /*<<< orphan*/  STRSEED ; 
 size_t cast_byte (size_t) ; 
 int /*<<< orphan*/  changewhite (TYPE_4__*) ; 
 TYPE_4__* createstrobj (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  getstr (TYPE_4__*) ; 
 scalar_t__ isdead (TYPE_3__*,TYPE_4__*) ; 
 size_t lmod (unsigned int,int) ; 
 unsigned int luaS_hash (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_resize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static TString *internshrstr (lua_State *L, const char *str, size_t l) {
  TString *ts;
  global_State *g = G(L);
  unsigned int h = luaS_hash(str, l, STRSEED);
  TString **list = &g->strt.hash[lmod(h, g->strt.size)];
  lua_assert(str != NULL);  /* otherwise 'memcmp'/'memcpy' are undefined */
  for (ts = *list; ts != NULL; ts = ts->u.hnext) {
    if (l == ts->shrlen &&
        (memcmp(str, getstr(ts), l * sizeof(char)) == 0)) {
      /* found! */
      if (isdead(g, ts))  /* dead (but not collected yet)? */
        changewhite(ts);  /* resurrect it */
      return ts;
    }
  }
  if (g->strt.nuse >= g->strt.size && g->strt.size <= MAX_INT/2) {
    luaS_resize(L, g->strt.size * 2);
    list = &g->strt.hash[lmod(h, g->strt.size)];  /* recompute with new size */
  }
  ts = createstrobj(L, l, LUA_TSHRSTR, h);
  memcpy(getstr(ts), str, l * sizeof(char));
  ts->shrlen = cast_byte(l);
  ts->u.hnext = *list;
  *list = ts;
  g->strt.nuse++;
  return ts;
}