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
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_10__* L; scalar_t__* base; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_13__ {int /*<<< orphan*/  mobjv; scalar_t__ mobj; int /*<<< orphan*/  keyv; int /*<<< orphan*/  tabv; scalar_t__ key; scalar_t__ tab; } ;
struct TYPE_11__ {int /*<<< orphan*/ * base; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  scalar_t__ TRef ;
typedef  TYPE_2__ RecordIndex ;
typedef  scalar_t__ MMS ;
typedef  int BCReg ;

/* Variables and functions */
 int LJ_FR2 ; 
 int /*<<< orphan*/  LJ_TRERR_NOMM ; 
 scalar_t__ MM_concat ; 
 scalar_t__ MM_unm ; 
 int /*<<< orphan*/  copyTV (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_cont_cat ; 
 int /*<<< orphan*/  lj_cont_ra ; 
 int /*<<< orphan*/  lj_record_call (TYPE_1__*,int,int) ; 
 scalar_t__ lj_record_mm_lookup (TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int rec_mm_prep (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TRef rec_mm_arith(jit_State *J, RecordIndex *ix, MMS mm)
{
  /* Set up metamethod call first to save ix->tab and ix->tabv. */
  BCReg func = rec_mm_prep(J, mm == MM_concat ? lj_cont_cat : lj_cont_ra);
  TRef *base = J->base + func;
  TValue *basev = J->L->base + func;
  base[1+LJ_FR2] = ix->tab; base[2+LJ_FR2] = ix->key;
  copyTV(J->L, basev+1+LJ_FR2, &ix->tabv);
  copyTV(J->L, basev+2+LJ_FR2, &ix->keyv);
  if (!lj_record_mm_lookup(J, ix, mm)) {  /* Lookup mm on 1st operand. */
    if (mm != MM_unm) {
      ix->tab = ix->key;
      copyTV(J->L, &ix->tabv, &ix->keyv);
      if (lj_record_mm_lookup(J, ix, mm))  /* Lookup mm on 2nd operand. */
	goto ok;
    }
    lj_trace_err(J, LJ_TRERR_NOMM);
  }
ok:
  base[0] = ix->mobj;
#if LJ_FR2
  base[1] = 0;
#endif
  copyTV(J->L, basev+0, &ix->mobjv);
  lj_record_call(J, func, 2);
  return 0;  /* No result yet. */
}