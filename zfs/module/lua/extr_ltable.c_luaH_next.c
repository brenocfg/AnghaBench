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
struct TYPE_6__ {int sizearray; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ Table ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 int /*<<< orphan*/  cast_num (int) ; 
 int findindex (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * gkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnode (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * gval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnvalue (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj2s (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int sizenode (TYPE_1__*) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ *) ; 

int luaH_next (lua_State *L, Table *t, StkId key) {
  int i = findindex(L, t, key);  /* find original element */
  for (i++; i < t->sizearray; i++) {  /* try first array part */
    if (!ttisnil(&t->array[i])) {  /* a non-nil value? */
      setnvalue(key, cast_num(i+1));
      setobj2s(L, key+1, &t->array[i]);
      return 1;
    }
  }
  for (i -= t->sizearray; i < sizenode(t); i++) {  /* then hash part */
    if (!ttisnil(gval(gnode(t, i)))) {  /* a non-nil value? */
      setobj2s(L, key, gkey(gnode(t, i)));
      setobj2s(L, key+1, gval(gnode(t, i)));
      return 1;
    }
  }
  return 0;  /* no more elements */
}