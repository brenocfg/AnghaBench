#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_6__ {int /*<<< orphan*/ * L; int /*<<< orphan*/  cap; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
#define  Cstring 129 
#define  Csubst 128 
 int captype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_addvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int pushcapture (TYPE_1__*) ; 
 int /*<<< orphan*/  stringcap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  substcap (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int addonestring (luaL_Buffer *b, CapState *cs, const char *what) {
  switch (captype(cs->cap)) {
    case Cstring:
      stringcap(b, cs);  /* add capture directly to buffer */
      return 1;
    case Csubst:
      substcap(b, cs);  /* add capture directly to buffer */
      return 1;
    default: {
      lua_State *L = cs->L;
      int n = pushcapture(cs);
      if (n > 0) {
        if (n > 1) lua_pop(L, n - 1);  /* only one result */
        if (!lua_isstring(L, -1))
          luaL_error(L, "invalid %s value (a %s)", what, luaL_typename(L, -1));
        luaL_addvalue(b);
      }
      return n;
    }
  }
}