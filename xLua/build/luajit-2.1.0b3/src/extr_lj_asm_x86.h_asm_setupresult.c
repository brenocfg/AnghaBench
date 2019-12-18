#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {scalar_t__ o; int r; int /*<<< orphan*/  t; int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  RegSet ;
typedef  int Reg ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ CCallInfo ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 int CCI_CASTU64 ; 
 int CCI_NOFPRCLOBBER ; 
 scalar_t__ IR_HIOP ; 
 scalar_t__ LJ_32 ; 
 int REX_64 ; 
 int /*<<< orphan*/  RID_ESP ; 
 int RID_FPRET ; 
 int RID_RET ; 
 int RID_RETHI ; 
 int RID_RETLO ; 
 int /*<<< orphan*/  RSET_FPR ; 
 int /*<<< orphan*/  RSET_SCRATCH ; 
 int /*<<< orphan*/  XI_FPOP ; 
 int /*<<< orphan*/  XO_FSTPd ; 
 int /*<<< orphan*/  XO_FSTPq ; 
 int /*<<< orphan*/  XO_MOVD ; 
 int /*<<< orphan*/  XO_MOVSD ; 
 int /*<<< orphan*/  XO_MOVSS ; 
 int XOg_FSTPd ; 
 int XOg_FSTPq ; 
 int /*<<< orphan*/  emit_movtomro (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_rmro (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_x87op (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isfp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_isnil (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_ispri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  ra_destpair (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ra_destreg (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ra_evictset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_free (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ra_hasreg (int) ; 
 int /*<<< orphan*/  ra_modified (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ra_used (TYPE_1__*) ; 
 int /*<<< orphan*/  rset_clear (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sps_scale (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asm_setupresult(ASMState *as, IRIns *ir, const CCallInfo *ci)
{
  RegSet drop = RSET_SCRATCH;
  int hiop = (LJ_32 && (ir+1)->o == IR_HIOP && !irt_isnil((ir+1)->t));
  if ((ci->flags & CCI_NOFPRCLOBBER))
    drop &= ~RSET_FPR;
  if (ra_hasreg(ir->r))
    rset_clear(drop, ir->r);  /* Dest reg handled below. */
  if (hiop && ra_hasreg((ir+1)->r))
    rset_clear(drop, (ir+1)->r);  /* Dest reg handled below. */
  ra_evictset(as, drop);  /* Evictions must be performed first. */
  if (ra_used(ir)) {
    if (irt_isfp(ir->t)) {
      int32_t ofs = sps_scale(ir->s);  /* Use spill slot or temp slots. */
#if LJ_64
      if ((ci->flags & CCI_CASTU64)) {
	Reg dest = ir->r;
	if (ra_hasreg(dest)) {
	  ra_free(as, dest);
	  ra_modified(as, dest);
	  emit_rr(as, XO_MOVD, dest|REX_64, RID_RET);  /* Really MOVQ. */
	}
	if (ofs) emit_movtomro(as, RID_RET|REX_64, RID_ESP, ofs);
      } else {
	ra_destreg(as, ir, RID_FPRET);
      }
#else
      /* Number result is in x87 st0 for x86 calling convention. */
      Reg dest = ir->r;
      if (ra_hasreg(dest)) {
	ra_free(as, dest);
	ra_modified(as, dest);
	emit_rmro(as, irt_isnum(ir->t) ? XO_MOVSD : XO_MOVSS,
		  dest, RID_ESP, ofs);
      }
      if ((ci->flags & CCI_CASTU64)) {
	emit_movtomro(as, RID_RETLO, RID_ESP, ofs);
	emit_movtomro(as, RID_RETHI, RID_ESP, ofs+4);
      } else {
	emit_rmro(as, irt_isnum(ir->t) ? XO_FSTPq : XO_FSTPd,
		  irt_isnum(ir->t) ? XOg_FSTPq : XOg_FSTPd, RID_ESP, ofs);
      }
#endif
#if LJ_32
    } else if (hiop) {
      ra_destpair(as, ir);
#endif
    } else {
      lua_assert(!irt_ispri(ir->t));
      ra_destreg(as, ir, RID_RET);
    }
  } else if (LJ_32 && irt_isfp(ir->t) && !(ci->flags & CCI_CASTU64)) {
    emit_x87op(as, XI_FPOP);  /* Pop unused result from x87 st0. */
  }
}