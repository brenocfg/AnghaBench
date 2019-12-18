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
struct TYPE_12__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_13__ {int /*<<< orphan*/  metatable; } ;
typedef  TYPE_2__ GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_GETLOOP ; 
 int /*<<< orphan*/  LJ_ERR_OPINDEX ; 
 scalar_t__ LJ_LIKELY (int /*<<< orphan*/ ) ; 
 int LJ_MAX_IDXCHAIN ; 
 int /*<<< orphan*/  MM_index ; 
 int /*<<< orphan*/  lj_cont_ra ; 
 int /*<<< orphan*/  lj_err_msg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_optype (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_meta_fast (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_meta_lookup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_tab_get (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmcall (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* tabV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tabref (int /*<<< orphan*/ ) ; 
 scalar_t__ tvisfunc (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvistab (int /*<<< orphan*/ *) ; 

cTValue *lj_meta_tget(lua_State *L, cTValue *o, cTValue *k)
{
  int loop;
  for (loop = 0; loop < LJ_MAX_IDXCHAIN; loop++) {
    cTValue *mo;
    if (LJ_LIKELY(tvistab(o))) {
      GCtab *t = tabV(o);
      cTValue *tv = lj_tab_get(L, t, k);
      if (!tvisnil(tv) ||
	  !(mo = lj_meta_fast(L, tabref(t->metatable), MM_index)))
	return tv;
    } else if (tvisnil(mo = lj_meta_lookup(L, o, MM_index))) {
      lj_err_optype(L, o, LJ_ERR_OPINDEX);
      return NULL;  /* unreachable */
    }
    if (tvisfunc(mo)) {
      L->top = mmcall(L, lj_cont_ra, mo, o, k);
      return NULL;  /* Trigger metamethod call. */
    }
    o = mo;
  }
  lj_err_msg(L, LJ_ERR_GETLOOP);
  return NULL;  /* unreachable */
}