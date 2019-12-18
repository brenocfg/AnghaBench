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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {unsigned int sizearray; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  StkId ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 unsigned int arrayindex (int /*<<< orphan*/ ) ; 
 unsigned int cast_int (int /*<<< orphan*/ *) ; 
 scalar_t__ deadvalue (int /*<<< orphan*/ ) ; 
 scalar_t__ gcvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gkey (int /*<<< orphan*/ *) ; 
 int gnext (int /*<<< orphan*/ *) ; 
 int gnode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ iscollectable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaG_runerror (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaV_rawequalobj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mainposition (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ttisdeadkey (int /*<<< orphan*/ ) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int findindex (lua_State *L, Table *t, StkId key) {
  unsigned int i;
  if (ttisnil(key)) return 0;  /* first iteration */
  i = arrayindex(key);
  if (i != 0 && i <= t->sizearray)  /* is 'key' inside array part? */
    return i;  /* yes; that's the index */
  else {
    int nx;
    Node *n = mainposition(t, key);
    for (;;) {  /* check whether 'key' is somewhere in the chain */
      /* key may be dead already, but it is ok to use it in 'next' */
      if (luaV_rawequalobj(gkey(n), key) ||
            (ttisdeadkey(gkey(n)) && iscollectable(key) &&
             deadvalue(gkey(n)) == gcvalue(key))) {
        i = cast_int(n - gnode(t, 0));  /* key index in hash table */
        /* hash elements are numbered after array ones */
        return (i + 1) + t->sizearray;
      }
      nx = gnext(n);
      if (nx == 0)
        luaG_runerror(L, "invalid key to 'next'");  /* key not found */
      else n += nx;
    }
  }
}