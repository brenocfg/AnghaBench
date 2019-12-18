#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ lua_Number ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_12__ {scalar_t__ nomm; } ;
struct TYPE_11__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ Node ;
typedef  TYPE_2__ GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_NANIDX ; 
 int /*<<< orphan*/  LJ_ERR_NILIDX ; 
 TYPE_1__* hashkey (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ intV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_err_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_num2int (scalar_t__) ; 
 scalar_t__ lj_obj_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_tab_newkey (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_tab_setint (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/ * lj_tab_setstr (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* nextnode (TYPE_1__*) ; 
 scalar_t__ numV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnan (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnum (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

TValue *lj_tab_set(lua_State *L, GCtab *t, cTValue *key)
{
  Node *n;
  t->nomm = 0;  /* Invalidate negative metamethod cache. */
  if (tvisstr(key)) {
    return lj_tab_setstr(L, t, strV(key));
  } else if (tvisint(key)) {
    return lj_tab_setint(L, t, intV(key));
  } else if (tvisnum(key)) {
    lua_Number nk = numV(key);
    int32_t k = lj_num2int(nk);
    if (nk == (lua_Number)k)
      return lj_tab_setint(L, t, k);
    if (tvisnan(key))
      lj_err_msg(L, LJ_ERR_NANIDX);
    /* Else use the generic lookup. */
  } else if (tvisnil(key)) {
    lj_err_msg(L, LJ_ERR_NILIDX);
  }
  n = hashkey(t, key);
  do {
    if (lj_obj_equal(&n->key, key))
      return &n->val;
  } while ((n = nextnode(n)));
  return lj_tab_newkey(L, t, key);
}