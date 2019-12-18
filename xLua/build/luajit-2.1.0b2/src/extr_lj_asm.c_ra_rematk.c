#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  u64; } ;
struct TYPE_17__ {int /*<<< orphan*/  freeset; } ;
struct TYPE_16__ {scalar_t__ o; int /*<<< orphan*/  i; int /*<<< orphan*/  t; int /*<<< orphan*/  r; int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  Reg ;
typedef  int /*<<< orphan*/  IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ ASMState ;

/* Variables and functions */
 int /*<<< orphan*/  ASMREF_L ; 
 TYPE_1__* IR (int /*<<< orphan*/ ) ; 
 scalar_t__ IR_BASE ; 
 scalar_t__ IR_KGC ; 
 scalar_t__ IR_KINT ; 
 scalar_t__ IR_KINT64 ; 
 scalar_t__ IR_KKPTR ; 
 scalar_t__ IR_KNULL ; 
 scalar_t__ IR_KNUM ; 
 scalar_t__ IR_KPRI ; 
 scalar_t__ IR_KPTR ; 
 int /*<<< orphan*/  RA_DBGX (TYPE_2__*) ; 
 int /*<<< orphan*/  REF_BASE ; 
 int /*<<< orphan*/  RID_BASE ; 
 int /*<<< orphan*/  RID_INIT ; 
 int /*<<< orphan*/  cur_L ; 
 scalar_t__ emit_canremat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_getgl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_loadi (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_loadn (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_loadu64 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* ir_kint64 (TYPE_1__*) ; 
 int /*<<< orphan*/  ir_knum (TYPE_1__*) ; 
 int irt_isnil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jit_base ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  ra_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_hasreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_hasspill (int /*<<< orphan*/ ) ; 
 scalar_t__ ra_iskref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_krefk (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_krefreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_modified (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_sethint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rset_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Reg ra_rematk(ASMState *as, IRRef ref)
{
  IRIns *ir;
  Reg r;
  if (ra_iskref(ref)) {
    r = ra_krefreg(ref);
    lua_assert(!rset_test(as->freeset, r));
    ra_free(as, r);
    ra_modified(as, r);
    emit_loadi(as, r, ra_krefk(as, ref));
    return r;
  }
  ir = IR(ref);
  r = ir->r;
  lua_assert(ra_hasreg(r) && !ra_hasspill(ir->s));
  ra_free(as, r);
  ra_modified(as, r);
  ir->r = RID_INIT;  /* Do not keep any hint. */
  RA_DBGX((as, "remat     $i $r", ir, r));
#if !LJ_SOFTFP
  if (ir->o == IR_KNUM) {
    emit_loadn(as, r, ir_knum(ir));
  } else
#endif
  if (emit_canremat(REF_BASE) && ir->o == IR_BASE) {
    ra_sethint(ir->r, RID_BASE);  /* Restore BASE register hint. */
    emit_getgl(as, r, jit_base);
  } else if (emit_canremat(ASMREF_L) && ir->o == IR_KPRI) {
    lua_assert(irt_isnil(ir->t));  /* REF_NIL stores ASMREF_L register. */
    emit_getgl(as, r, cur_L);
#if LJ_64
  } else if (ir->o == IR_KINT64) {
    emit_loadu64(as, r, ir_kint64(ir)->u64);
#endif
  } else {
    lua_assert(ir->o == IR_KINT || ir->o == IR_KGC ||
	       ir->o == IR_KPTR || ir->o == IR_KKPTR || ir->o == IR_KNULL);
    emit_loadi(as, r, ir->i);
  }
  return r;
}