#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  info; } ;
struct TYPE_18__ {TYPE_1__ s; } ;
struct TYPE_20__ {scalar_t__ k; TYPE_2__ u; void* t; void* f; } ;
struct TYPE_19__ {void* lasttarget; void* pc; int /*<<< orphan*/  freereg; } ;
typedef  TYPE_3__ FuncState ;
typedef  TYPE_4__ ExpDesc ;
typedef  int /*<<< orphan*/  BCReg ;
typedef  void* BCPos ;

/* Variables and functions */
 int /*<<< orphan*/  BC_JMP ; 
 int /*<<< orphan*/  BC_KPRI ; 
 void* NO_JMP ; 
 scalar_t__ VJMP ; 
 int /*<<< orphan*/  VKFALSE ; 
 int /*<<< orphan*/  VKTRUE ; 
 scalar_t__ VNONRELOC ; 
 void* bcemit_AD (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcemit_AJ (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* bcemit_jmp (TYPE_3__*) ; 
 scalar_t__ expr_hasjump (TYPE_4__*) ; 
 int /*<<< orphan*/  expr_toreg_nobranch (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_append (TYPE_3__*,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ jmp_novalue (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  jmp_patchval (TYPE_3__*,void*,void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  jmp_tohere (TYPE_3__*,void*) ; 

__attribute__((used)) static void expr_toreg(FuncState *fs, ExpDesc *e, BCReg reg)
{
  expr_toreg_nobranch(fs, e, reg);
  if (e->k == VJMP)
    jmp_append(fs, &e->t, e->u.s.info);  /* Add it to the true jump list. */
  if (expr_hasjump(e)) {  /* Discharge expression with branches. */
    BCPos jend, jfalse = NO_JMP, jtrue = NO_JMP;
    if (jmp_novalue(fs, e->t) || jmp_novalue(fs, e->f)) {
      BCPos jval = (e->k == VJMP) ? NO_JMP : bcemit_jmp(fs);
      jfalse = bcemit_AD(fs, BC_KPRI, reg, VKFALSE);
      bcemit_AJ(fs, BC_JMP, fs->freereg, 1);
      jtrue = bcemit_AD(fs, BC_KPRI, reg, VKTRUE);
      jmp_tohere(fs, jval);
    }
    jend = fs->pc;
    fs->lasttarget = jend;
    jmp_patchval(fs, e->f, jend, reg, jfalse);
    jmp_patchval(fs, e->t, jend, reg, jtrue);
  }
  e->f = e->t = NO_JMP;
  e->u.s.info = reg;
  e->k = VNONRELOC;
}