#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  J; } ;
struct TYPE_11__ {int info; } ;
struct TYPE_9__ {int irt; } ;
struct TYPE_10__ {scalar_t__ op1; scalar_t__ o; scalar_t__ op2; TYPE_1__ t; int /*<<< orphan*/  i; } ;
typedef  TYPE_2__ IRIns ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_3__ CType ;
typedef  TYPE_4__ ASMState ;

/* Variables and functions */
 int CCI_CC_SHIFT ; 
 int CCI_OTSHIFT ; 
 int CCI_VARARG ; 
 int CTF_VARARG ; 
 TYPE_2__* IR (scalar_t__) ; 
 scalar_t__ IR_CARG ; 
 int /*<<< orphan*/  J2G (int /*<<< orphan*/ ) ; 
 scalar_t__ REF_NIL ; 
 int ctype_cconv (int) ; 
 int /*<<< orphan*/  ctype_ctsG (int /*<<< orphan*/ ) ; 
 TYPE_3__* ctype_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t asm_callx_flags(ASMState *as, IRIns *ir)
{
  uint32_t nargs = 0;
  if (ir->op1 != REF_NIL) {  /* Count number of arguments first. */
    IRIns *ira = IR(ir->op1);
    nargs++;
    while (ira->o == IR_CARG) { nargs++; ira = IR(ira->op1); }
  }
#if LJ_HASFFI
  if (IR(ir->op2)->o == IR_CARG) {  /* Copy calling convention info. */
    CTypeID id = (CTypeID)IR(IR(ir->op2)->op2)->i;
    CType *ct = ctype_get(ctype_ctsG(J2G(as->J)), id);
    nargs |= ((ct->info & CTF_VARARG) ? CCI_VARARG : 0);
#if LJ_TARGET_X86
    nargs |= (ctype_cconv(ct->info) << CCI_CC_SHIFT);
#endif
  }
#endif
  return (nargs | (ir->t.irt << CCI_OTSHIFT));
}