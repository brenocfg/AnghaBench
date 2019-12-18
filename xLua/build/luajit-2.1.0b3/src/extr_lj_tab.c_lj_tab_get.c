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
typedef  scalar_t__ lua_Number ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_5__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Node ;
typedef  int /*<<< orphan*/  GCtab ;

/* Variables and functions */
 TYPE_1__* hashkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ intV (int /*<<< orphan*/ *) ; 
 scalar_t__ lj_num2int (scalar_t__) ; 
 scalar_t__ lj_obj_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_tab_getint (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * lj_tab_getstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* nextnode (TYPE_1__*) ; 
 int /*<<< orphan*/ * niltv (int /*<<< orphan*/ *) ; 
 scalar_t__ numV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnum (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

cTValue *lj_tab_get(lua_State *L, GCtab *t, cTValue *key)
{
  if (tvisstr(key)) {
    cTValue *tv = lj_tab_getstr(t, strV(key));
    if (tv)
      return tv;
  } else if (tvisint(key)) {
    cTValue *tv = lj_tab_getint(t, intV(key));
    if (tv)
      return tv;
  } else if (tvisnum(key)) {
    lua_Number nk = numV(key);
    int32_t k = lj_num2int(nk);
    if (nk == (lua_Number)k) {
      cTValue *tv = lj_tab_getint(t, k);
      if (tv)
	return tv;
    } else {
      goto genlookup;  /* Else use the generic lookup. */
    }
  } else if (!tvisnil(key)) {
    Node *n;
  genlookup:
    n = hashkey(t, key);
    do {
      if (lj_obj_equal(&n->key, key))
	return &n->val;
    } while ((n = nextnode(n)));
  }
  return niltv(L);
}