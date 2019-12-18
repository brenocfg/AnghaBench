#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  MMS ;
typedef  int /*<<< orphan*/  ASMFunction ;

/* Variables and functions */
 scalar_t__ LJ_52 ; 
 scalar_t__ LJ_HASFFI ; 
 scalar_t__ LJ_UNLIKELY (scalar_t__) ; 
 int /*<<< orphan*/  MM_le ; 
 int /*<<< orphan*/  MM_lt ; 
 scalar_t__ itype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_cont_condf ; 
 int /*<<< orphan*/  lj_cont_condt ; 
 int /*<<< orphan*/  lj_err_comp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_meta_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_obj_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lj_str_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisbool (int /*<<< orphan*/ *) ; 
 scalar_t__ tviscdata (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 
 scalar_t__ tvisstr (int /*<<< orphan*/ *) ; 

TValue *lj_meta_comp(lua_State *L, cTValue *o1, cTValue *o2, int op)
{
  if (LJ_HASFFI && (tviscdata(o1) || tviscdata(o2))) {
    ASMFunction cont = (op & 1) ? lj_cont_condf : lj_cont_condt;
    MMS mm = (op & 2) ? MM_le : MM_lt;
    cTValue *mo = lj_meta_lookup(L, tviscdata(o1) ? o1 : o2, mm);
    if (LJ_UNLIKELY(tvisnil(mo))) goto err;
    return mmcall(L, cont, mo, o1, o2);
  } else if (LJ_52 || itype(o1) == itype(o2)) {
    /* Never called with two numbers. */
    if (tvisstr(o1) && tvisstr(o2)) {
      int32_t res = lj_str_cmp(strV(o1), strV(o2));
      return (TValue *)(intptr_t)(((op&2) ? res <= 0 : res < 0) ^ (op&1));
    } else {
    trymt:
      while (1) {
	ASMFunction cont = (op & 1) ? lj_cont_condf : lj_cont_condt;
	MMS mm = (op & 2) ? MM_le : MM_lt;
	cTValue *mo = lj_meta_lookup(L, o1, mm);
#if LJ_52
	if (tvisnil(mo) && tvisnil((mo = lj_meta_lookup(L, o2, mm))))
#else
	cTValue *mo2 = lj_meta_lookup(L, o2, mm);
	if (tvisnil(mo) || !lj_obj_equal(mo, mo2))
#endif
	{
	  if (op & 2) {  /* MM_le not found: retry with MM_lt. */
	    cTValue *ot = o1; o1 = o2; o2 = ot;  /* Swap operands. */
	    op ^= 3;  /* Use LT and flip condition. */
	    continue;
	  }
	  goto err;
	}
	return mmcall(L, cont, mo, o1, o2);
      }
    }
  } else if (tvisbool(o1) && tvisbool(o2)) {
    goto trymt;
  } else {
  err:
    lj_err_comp(L, o1, o2);
    return NULL;
  }
}