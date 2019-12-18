#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_19__ {scalar_t__ nomm; int /*<<< orphan*/  metatable; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_2__ GCtab ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_NANIDX ; 
 int /*<<< orphan*/  LJ_ERR_NILIDX ; 
 int /*<<< orphan*/  LJ_ERR_OPINDEX ; 
 int /*<<< orphan*/  LJ_ERR_SETLOOP ; 
 scalar_t__ LJ_LIKELY (int) ; 
 int LJ_MAX_IDXCHAIN ; 
 int /*<<< orphan*/  MM_newindex ; 
 int /*<<< orphan*/  copyTV (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ intV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_cont_nop ; 
 int /*<<< orphan*/  lj_err_msg (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_optype (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_gc_anybarriert (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * lj_meta_fast (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_meta_lookup (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_tab_get (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_tab_newkey (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmcall (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * niltv (TYPE_1__*) ; 
 int /*<<< orphan*/  setnumV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* tabV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tabref (int /*<<< orphan*/ ) ; 
 scalar_t__ tvisfunc (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisint (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnan (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnum (int /*<<< orphan*/ *) ; 
 int tvistab (int /*<<< orphan*/ *) ; 

TValue *lj_meta_tset(lua_State *L, cTValue *o, cTValue *k)
{
  TValue tmp;
  int loop;
  for (loop = 0; loop < LJ_MAX_IDXCHAIN; loop++) {
    cTValue *mo;
    if (LJ_LIKELY(tvistab(o))) {
      GCtab *t = tabV(o);
      cTValue *tv = lj_tab_get(L, t, k);
      if (LJ_LIKELY(!tvisnil(tv))) {
	t->nomm = 0;  /* Invalidate negative metamethod cache. */
	lj_gc_anybarriert(L, t);
	return (TValue *)tv;
      } else if (!(mo = lj_meta_fast(L, tabref(t->metatable), MM_newindex))) {
	t->nomm = 0;  /* Invalidate negative metamethod cache. */
	lj_gc_anybarriert(L, t);
	if (tv != niltv(L))
	  return (TValue *)tv;
	if (tvisnil(k)) lj_err_msg(L, LJ_ERR_NILIDX);
	else if (tvisint(k)) { setnumV(&tmp, (lua_Number)intV(k)); k = &tmp; }
	else if (tvisnum(k) && tvisnan(k)) lj_err_msg(L, LJ_ERR_NANIDX);
	return lj_tab_newkey(L, t, k);
      }
    } else if (tvisnil(mo = lj_meta_lookup(L, o, MM_newindex))) {
      lj_err_optype(L, o, LJ_ERR_OPINDEX);
      return NULL;  /* unreachable */
    }
    if (tvisfunc(mo)) {
      L->top = mmcall(L, lj_cont_nop, mo, o, k);
      /* L->top+2 = v filled in by caller. */
      return NULL;  /* Trigger metamethod call. */
    }
    copyTV(L, &tmp, mo);
    o = &tmp;
  }
  lj_err_msg(L, LJ_ERR_SETLOOP);
  return NULL;  /* unreachable */
}