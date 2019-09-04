#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_10__ {int size; int nuse; TYPE_4__** hash; } ;
struct TYPE_11__ {TYPE_2__ strt; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_9__ {TYPE_4__* hnext; } ;
struct TYPE_12__ {TYPE_1__ u; int /*<<< orphan*/  shrlen; } ;
typedef  TYPE_4__ TString ;

/* Variables and functions */
 TYPE_3__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LUA_TSHRSTR ; 
 int MAX_INT ; 
 int /*<<< orphan*/  cast_byte (size_t) ; 
 TYPE_4__* createstrobj (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  getstr (TYPE_4__*) ; 
 size_t lmod (unsigned int,int) ; 
 int /*<<< orphan*/  luaS_resize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static TString *addshrstr (lua_State *L, const char *str, size_t l, unsigned int h) {
  TString *ts;
  global_State *g = G(L);
  TString **list = &g->strt.hash[lmod(h, g->strt.size)];
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