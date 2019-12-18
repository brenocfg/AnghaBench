#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Table ;
struct TYPE_5__ {scalar_t__ tt; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ TString ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ LUA_TSHRSTR ; 
 scalar_t__ eqshrstr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * gkey (int /*<<< orphan*/ *) ; 
 int gnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* gval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hashstr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  const* luaO_nilobject ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  tsvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisshrstring (int /*<<< orphan*/  const*) ; 

const TValue *luaH_getshortstr (Table *t, TString *key) {
  Node *n = hashstr(t, key);
  lua_assert(key->tt == LUA_TSHRSTR);
  for (;;) {  /* check whether 'key' is somewhere in the chain */
    const TValue *k = gkey(n);
    if (ttisshrstring(k) && eqshrstr(tsvalue(k), key))
      return gval(n);  /* that's it */
    else {
      int nx = gnext(n);
      if (nx == 0)
        return luaO_nilobject;  /* not found */
      n += nx;
    }
  }
}