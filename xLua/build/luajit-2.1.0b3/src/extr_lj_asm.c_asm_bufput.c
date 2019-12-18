#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int len; } ;
struct TYPE_9__ {scalar_t__ op1; scalar_t__ op2; scalar_t__ o; int /*<<< orphan*/  t; int /*<<< orphan*/  r; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ GCstr ;
typedef  int /*<<< orphan*/  CCallInfo ;
typedef  int /*<<< orphan*/  ASMState ;

/* Variables and functions */
 scalar_t__ ASMREF_TMP1 ; 
 TYPE_1__* IR (scalar_t__) ; 
 size_t IRCALL_lj_buf_putchar ; 
 size_t IRCALL_lj_buf_putmem ; 
 size_t IRCALL_lj_buf_putstr ; 
 size_t IRCALL_lj_strfmt_putint ; 
 size_t IRCALL_lj_strfmt_putnum ; 
 scalar_t__ IRTOSTR_INT ; 
 scalar_t__ IRTOSTR_NUM ; 
 scalar_t__ IR_KGC ; 
 scalar_t__ IR_SNEW ; 
 scalar_t__ IR_TOSTR ; 
 int /*<<< orphan*/  asm_gencall (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__*) ; 
 int /*<<< orphan*/  asm_setupresult (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  asm_tvptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* ir_kstr (TYPE_1__*) ; 
 int /*<<< orphan*/  irt_isinteger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irt_isstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_ir_callinfo ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ mayfuse (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ra_allockreg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_noreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_releasetmp (int /*<<< orphan*/ *,scalar_t__) ; 
 int* strdata (TYPE_2__*) ; 

__attribute__((used)) static void asm_bufput(ASMState *as, IRIns *ir)
{
  const CCallInfo *ci = &lj_ir_callinfo[IRCALL_lj_buf_putstr];
  IRRef args[3];
  IRIns *irs;
  int kchar = -1;
  args[0] = ir->op1;  /* SBuf * */
  args[1] = ir->op2;  /* GCstr * */
  irs = IR(ir->op2);
  lua_assert(irt_isstr(irs->t));
  if (irs->o == IR_KGC) {
    GCstr *s = ir_kstr(irs);
    if (s->len == 1) {  /* Optimize put of single-char string constant. */
      kchar = strdata(s)[0];
      args[1] = ASMREF_TMP1;  /* int, truncated to char */
      ci = &lj_ir_callinfo[IRCALL_lj_buf_putchar];
    }
  } else if (mayfuse(as, ir->op2) && ra_noreg(irs->r)) {
    if (irs->o == IR_TOSTR) {  /* Fuse number to string conversions. */
      if (irs->op2 == IRTOSTR_NUM) {
	args[1] = ASMREF_TMP1;  /* TValue * */
	ci = &lj_ir_callinfo[IRCALL_lj_strfmt_putnum];
      } else {
	lua_assert(irt_isinteger(IR(irs->op1)->t));
	args[1] = irs->op1;  /* int */
	if (irs->op2 == IRTOSTR_INT)
	  ci = &lj_ir_callinfo[IRCALL_lj_strfmt_putint];
	else
	  ci = &lj_ir_callinfo[IRCALL_lj_buf_putchar];
      }
    } else if (irs->o == IR_SNEW) {  /* Fuse string allocation. */
      args[1] = irs->op1;  /* const void * */
      args[2] = irs->op2;  /* MSize */
      ci = &lj_ir_callinfo[IRCALL_lj_buf_putmem];
    }
  }
  asm_setupresult(as, ir, ci);  /* SBuf * */
  asm_gencall(as, ci, args);
  if (args[1] == ASMREF_TMP1) {
    Reg tmp = ra_releasetmp(as, ASMREF_TMP1);
    if (kchar == -1)
      asm_tvptr(as, tmp, irs->op1);
    else
      ra_allockreg(as, kchar, tmp);
  }
}