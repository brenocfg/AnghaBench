#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_7__* L; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_10__ {int /*<<< orphan*/ * base; } ;
struct TYPE_9__ {int /*<<< orphan*/  keyv; int /*<<< orphan*/  valv; int /*<<< orphan*/  mobjv; int /*<<< orphan*/  key; int /*<<< orphan*/  val; int /*<<< orphan*/  mobj; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TRef ;
typedef  TYPE_2__ RecordIndex ;
typedef  int BCReg ;

/* Variables and functions */
 int LJ_FR2 ; 
 int /*<<< orphan*/  copyTV (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_cont_condf ; 
 int /*<<< orphan*/  lj_cont_condt ; 
 int /*<<< orphan*/  lj_record_call (TYPE_1__*,int,int) ; 
 int rec_mm_prep (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rec_mm_callcomp(jit_State *J, RecordIndex *ix, int op)
{
  BCReg func = rec_mm_prep(J, (op&1) ? lj_cont_condf : lj_cont_condt);
  TRef *base = J->base + func + LJ_FR2;
  TValue *tv = J->L->base + func + LJ_FR2;
  base[-LJ_FR2] = ix->mobj; base[1] = ix->val; base[2] = ix->key;
  copyTV(J->L, tv-LJ_FR2, &ix->mobjv);
  copyTV(J->L, tv+1, &ix->valv);
  copyTV(J->L, tv+2, &ix->keyv);
  lj_record_call(J, func, 2);
}