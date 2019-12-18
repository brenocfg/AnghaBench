#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_6__ {scalar_t__ gct; int /*<<< orphan*/  metatable; } ;
struct TYPE_7__ {TYPE_1__ gch; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_2__ GCobj ;

/* Variables and functions */
 scalar_t__ LJ_FR2 ; 
 int /*<<< orphan*/  MM_eq ; 
 int /*<<< orphan*/  copyTV (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curr_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_cont_condf ; 
 int /*<<< orphan*/  lj_cont_condt ; 
 int /*<<< orphan*/ * lj_meta_fast (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_obj_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setcont (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcV (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ ) ; 
 scalar_t__ tabref (int /*<<< orphan*/ ) ; 

TValue *lj_meta_equal(lua_State *L, GCobj *o1, GCobj *o2, int ne)
{
  /* Field metatable must be at same offset for GCtab and GCudata! */
  cTValue *mo = lj_meta_fast(L, tabref(o1->gch.metatable), MM_eq);
  if (mo) {
    TValue *top;
    uint32_t it;
    if (tabref(o1->gch.metatable) != tabref(o2->gch.metatable)) {
      cTValue *mo2 = lj_meta_fast(L, tabref(o2->gch.metatable), MM_eq);
      if (mo2 == NULL || !lj_obj_equal(mo, mo2))
	return (TValue *)(intptr_t)ne;
    }
    top = curr_top(L);
    setcont(top++, ne ? lj_cont_condf : lj_cont_condt);
    if (LJ_FR2) setnilV(top++);
    copyTV(L, top++, mo);
    if (LJ_FR2) setnilV(top++);
    it = ~(uint32_t)o1->gch.gct;
    setgcV(L, top, o1, it);
    setgcV(L, top+1, o2, it);
    return top;  /* Trigger metamethod call. */
  }
  return (TValue *)(intptr_t)ne;
}