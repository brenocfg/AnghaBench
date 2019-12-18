#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_15__ {int /*<<< orphan*/  J; } ;
struct TYPE_14__ {int r; } ;
struct TYPE_13__ {int /*<<< orphan*/  jit_base; } ;
typedef  scalar_t__ RegSet ;
typedef  int Reg ;
typedef  TYPE_1__ IRIns ;
typedef  int /*<<< orphan*/  ExitNo ;
typedef  int BCReg ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  CC_B ; 
 TYPE_12__* J2G (int /*<<< orphan*/ ) ; 
 int REX_64 ; 
 int REX_GC64 ; 
 int RID_BASE ; 
 int RID_DISPATCH ; 
 int RID_EAX ; 
 int RID_ESP ; 
 int RID_NONE ; 
 scalar_t__ RSET_EMPTY ; 
 int /*<<< orphan*/  XG_ARITHi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XO_ARITH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XO_MOV ; 
 int /*<<< orphan*/  XO_MOVto ; 
 int /*<<< orphan*/  XOg_CMP ; 
 int /*<<< orphan*/  XOg_SUB ; 
 int /*<<< orphan*/  cur_L ; 
 scalar_t__ dispofs (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_getgl (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_gri (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jcc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rmro (TYPE_2__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rr (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  exitstub_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_State ; 
 int /*<<< orphan*/  maxstack ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr2addr (int /*<<< orphan*/ *) ; 
 scalar_t__ ra_hasreg (int) ; 
 int /*<<< orphan*/  ra_modified (TYPE_2__*,int) ; 
 int rset_pickbot (scalar_t__) ; 

__attribute__((used)) static void asm_stack_check(ASMState *as, BCReg topslot,
			    IRIns *irp, RegSet allow, ExitNo exitno)
{
  /* Try to get an unused temp. register, otherwise spill/restore eax. */
  Reg pbase = irp ? irp->r : RID_BASE;
  Reg r = allow ? rset_pickbot(allow) : RID_EAX;
  emit_jcc(as, CC_B, exitstub_addr(as->J, exitno));
  if (allow == RSET_EMPTY)  /* Restore temp. register. */
    emit_rmro(as, XO_MOV, r|REX_64, RID_ESP, 0);
  else
    ra_modified(as, r);
  emit_gri(as, XG_ARITHi(XOg_CMP), r|REX_GC64, (int32_t)(8*topslot));
  if (ra_hasreg(pbase) && pbase != r)
    emit_rr(as, XO_ARITH(XOg_SUB), r|REX_GC64, pbase);
  else
#if LJ_GC64
    emit_rmro(as, XO_ARITH(XOg_SUB), r|REX_64, RID_DISPATCH,
	      (int32_t)dispofs(as, &J2G(as->J)->jit_base));
#else
    emit_rmro(as, XO_ARITH(XOg_SUB), r, RID_NONE,
	      ptr2addr(&J2G(as->J)->jit_base));
#endif
  emit_rmro(as, XO_MOV, r|REX_GC64, r, offsetof(lua_State, maxstack));
  emit_getgl(as, r, cur_L);
  if (allow == RSET_EMPTY)  /* Spill temp. register. */
    emit_rmro(as, XO_MOVto, r|REX_64, RID_ESP, 0);
}