#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_12__ {int /*<<< orphan*/  size; TYPE_4__** hash; } ;
struct TYPE_13__ {TYPE_2__ strt; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_11__ {TYPE_4__* hnext; } ;
struct TYPE_14__ {size_t shrlen; TYPE_1__ u; } ;
typedef  TYPE_4__ TString ;

/* Variables and functions */
 TYPE_3__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  changewhite (TYPE_4__*) ; 
 int /*<<< orphan*/  getstr (TYPE_4__*) ; 
 scalar_t__ isdead (TYPE_3__*,TYPE_4__*) ; 
 size_t lmod (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static TString *queryshrstr (lua_State *L, const char *str, size_t l, unsigned int h) {
  TString *ts;
  global_State *g = G(L);
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
  return NULL;
}