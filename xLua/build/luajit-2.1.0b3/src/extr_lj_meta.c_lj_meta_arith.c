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
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  TValue ;
typedef  scalar_t__ MMS ;
typedef  int /*<<< orphan*/  BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_OPARITH ; 
 scalar_t__ MM_add ; 
 scalar_t__ bcmode_mm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_cont_ra ; 
 int /*<<< orphan*/  lj_err_optype (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_meta_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lj_vm_foldarith (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * mmcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnumV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * str2num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 

TValue *lj_meta_arith(lua_State *L, TValue *ra, cTValue *rb, cTValue *rc,
		      BCReg op)
{
  MMS mm = bcmode_mm(op);
  TValue tempb, tempc;
  cTValue *b, *c;
  if ((b = str2num(rb, &tempb)) != NULL &&
      (c = str2num(rc, &tempc)) != NULL) {  /* Try coercion first. */
    setnumV(ra, lj_vm_foldarith(numV(b), numV(c), (int)mm-MM_add));
    return NULL;
  } else {
    cTValue *mo = lj_meta_lookup(L, rb, mm);
    if (tvisnil(mo)) {
      mo = lj_meta_lookup(L, rc, mm);
      if (tvisnil(mo)) {
	if (str2num(rb, &tempb) == NULL) rc = rb;
	lj_err_optype(L, rc, LJ_ERR_OPARITH);
	return NULL;  /* unreachable */
      }
    }
    return mmcall(L, lj_cont_ra, mo, rb, rc);
  }
}