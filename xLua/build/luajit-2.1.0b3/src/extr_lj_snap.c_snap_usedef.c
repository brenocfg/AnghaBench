#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_11__ {TYPE_6__* pt; TYPE_1__* L; } ;
typedef  TYPE_3__ jit_State ;
struct TYPE_13__ {int sizebc; } ;
struct TYPE_10__ {int /*<<< orphan*/  nextgc; } ;
struct TYPE_12__ {TYPE_2__ gch; } ;
struct TYPE_9__ {scalar_t__ base; int /*<<< orphan*/  openupval; } ;
typedef  TYPE_4__ GCobj ;
typedef  scalar_t__ BCReg ;
typedef  int /*<<< orphan*/  BCOp ;
typedef  int /*<<< orphan*/  const BCIns ;

/* Variables and functions */
#define  BCMbase 134 
#define  BCMdst 133 
#define  BCMfunc 132 
#define  BCMjump 131 
#define  BCMlit 130 
#define  BCMrbase 129 
#define  BCMvar 128 
 int /*<<< orphan*/  BC_CALLM ; 
 int /*<<< orphan*/  BC_CALLMT ; 
 int /*<<< orphan*/  BC_CALLT ; 
 int /*<<< orphan*/  BC_CAT ; 
 int /*<<< orphan*/  BC_FORI ; 
 int /*<<< orphan*/  BC_ISFC ; 
 int /*<<< orphan*/  BC_ISTC ; 
 int /*<<< orphan*/  BC_ITERC ; 
 int /*<<< orphan*/  BC_ITERL ; 
 int /*<<< orphan*/  BC_ITERN ; 
 int /*<<< orphan*/  BC_JFORL ; 
 int /*<<< orphan*/  BC_JITERL ; 
 int /*<<< orphan*/  BC_JLOOP ; 
 int /*<<< orphan*/  BC_KNIL ; 
 int /*<<< orphan*/  BC_RETM ; 
 int /*<<< orphan*/  BC_TSETM ; 
 int /*<<< orphan*/  BC_UCLO ; 
 int /*<<< orphan*/  BC_VARG ; 
 int /*<<< orphan*/  DEF_SLOT (scalar_t__) ; 
 scalar_t__ FORL_EXT ; 
 scalar_t__ LJ_FR2 ; 
 scalar_t__ SNAP_USEDEF_SLOTS ; 
 int /*<<< orphan*/  USE_SLOT (scalar_t__) ; 
 scalar_t__ bc_a (int /*<<< orphan*/  const) ; 
 scalar_t__ bc_b (int /*<<< orphan*/  const) ; 
 scalar_t__ bc_c (int /*<<< orphan*/  const) ; 
 scalar_t__ bc_d (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  bc_isret (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bc_j (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  bc_op (int /*<<< orphan*/  const) ; 
 int bcmode_a (int /*<<< orphan*/ ) ; 
 int bcmode_b (int /*<<< orphan*/ ) ; 
 int bcmode_c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gco2uv (TYPE_4__*) ; 
 TYPE_4__* gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  const* proto_bc (TYPE_6__*) ; 
 size_t uvval (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BCReg snap_usedef(jit_State *J, uint8_t *udf,
			 const BCIns *pc, BCReg maxslot)
{
  BCReg s;
  GCobj *o;

  if (maxslot == 0) return 0;
#ifdef LUAJIT_USE_VALGRIND
  /* Avoid errors for harmless reads beyond maxslot. */
  memset(udf, 1, SNAP_USEDEF_SLOTS);
#else
  memset(udf, 1, maxslot);
#endif

  /* Treat open upvalues as used. */
  o = gcref(J->L->openupval);
  while (o) {
    if (uvval(gco2uv(o)) < J->L->base) break;
    udf[uvval(gco2uv(o)) - J->L->base] = 0;
    o = gcref(o->gch.nextgc);
  }

#define USE_SLOT(s)		udf[(s)] &= ~1
#define DEF_SLOT(s)		udf[(s)] *= 3

  /* Scan through following bytecode and check for uses/defs. */
  lua_assert(pc >= proto_bc(J->pt) && pc < proto_bc(J->pt) + J->pt->sizebc);
  for (;;) {
    BCIns ins = *pc++;
    BCOp op = bc_op(ins);
    switch (bcmode_b(op)) {
    case BCMvar: USE_SLOT(bc_b(ins)); break;
    default: break;
    }
    switch (bcmode_c(op)) {
    case BCMvar: USE_SLOT(bc_c(ins)); break;
    case BCMrbase:
      lua_assert(op == BC_CAT);
      for (s = bc_b(ins); s <= bc_c(ins); s++) USE_SLOT(s);
      for (; s < maxslot; s++) DEF_SLOT(s);
      break;
    case BCMjump:
    handle_jump: {
      BCReg minslot = bc_a(ins);
      if (op >= BC_FORI && op <= BC_JFORL) minslot += FORL_EXT;
      else if (op >= BC_ITERL && op <= BC_JITERL) minslot += bc_b(pc[-2])-1;
      else if (op == BC_UCLO) { pc += bc_j(ins); break; }
      for (s = minslot; s < maxslot; s++) DEF_SLOT(s);
      return minslot < maxslot ? minslot : maxslot;
      }
    case BCMlit:
      if (op == BC_JFORL || op == BC_JITERL || op == BC_JLOOP) {
	goto handle_jump;
      } else if (bc_isret(op)) {
	BCReg top = op == BC_RETM ? maxslot : (bc_a(ins) + bc_d(ins)-1);
	for (s = 0; s < bc_a(ins); s++) DEF_SLOT(s);
	for (; s < top; s++) USE_SLOT(s);
	for (; s < maxslot; s++) DEF_SLOT(s);
	return 0;
      }
      break;
    case BCMfunc: return maxslot;  /* NYI: will abort, anyway. */
    default: break;
    }
    switch (bcmode_a(op)) {
    case BCMvar: USE_SLOT(bc_a(ins)); break;
    case BCMdst:
       if (!(op == BC_ISTC || op == BC_ISFC)) DEF_SLOT(bc_a(ins));
       break;
    case BCMbase:
      if (op >= BC_CALLM && op <= BC_VARG) {
	BCReg top = (op == BC_CALLM || op == BC_CALLMT || bc_c(ins) == 0) ?
		    maxslot : (bc_a(ins) + bc_c(ins)+LJ_FR2);
	if (LJ_FR2) DEF_SLOT(bc_a(ins)+1);
	s = bc_a(ins) - ((op == BC_ITERC || op == BC_ITERN) ? 3 : 0);
	for (; s < top; s++) USE_SLOT(s);
	for (; s < maxslot; s++) DEF_SLOT(s);
	if (op == BC_CALLT || op == BC_CALLMT) {
	  for (s = 0; s < bc_a(ins); s++) DEF_SLOT(s);
	  return 0;
	}
      } else if (op == BC_KNIL) {
	for (s = bc_a(ins); s <= bc_d(ins); s++) DEF_SLOT(s);
      } else if (op == BC_TSETM) {
	for (s = bc_a(ins)-1; s < maxslot; s++) USE_SLOT(s);
      }
      break;
    default: break;
    }
    lua_assert(pc >= proto_bc(J->pt) && pc < proto_bc(J->pt) + J->pt->sizebc);
  }

#undef USE_SLOT
#undef DEF_SLOT

  return 0;  /* unreachable */
}