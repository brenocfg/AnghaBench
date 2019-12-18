#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__* chain; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ jit_State ;
struct TYPE_21__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_2__ cTValue ;
struct TYPE_22__ {scalar_t__ op1; scalar_t__ op2; scalar_t__ prev; scalar_t__ o; int /*<<< orphan*/  t; } ;
struct TYPE_19__ {size_t o; int /*<<< orphan*/  t; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  scalar_t__ TRef ;
typedef  scalar_t__ IRRef ;
typedef  TYPE_3__ IRIns ;

/* Variables and functions */
#define  ALIAS_MAY 130 
#define  ALIAS_MUST 129 
#define  ALIAS_NO 128 
 TYPE_3__* IR (scalar_t__) ; 
 size_t IRDELTA_L2S ; 
 scalar_t__ IR_AREF ; 
 scalar_t__ IR_HREFK ; 
 scalar_t__ IR_KSLOT ; 
 size_t IR_NEWREF ; 
 scalar_t__ IR_TDUP ; 
 scalar_t__ IR_TNEW ; 
 scalar_t__ LJ_DUALNUM ; 
 scalar_t__ TREF_PRI (scalar_t__) ; 
 int aa_ahref (TYPE_1__*,TYPE_3__*,TYPE_3__*) ; 
 TYPE_14__* fins ; 
 int /*<<< orphan*/  intV (TYPE_2__*) ; 
 int /*<<< orphan*/  ir_ktab (TYPE_3__*) ; 
 scalar_t__ irref_isk (scalar_t__) ; 
 scalar_t__ irt_isint (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnil (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isnum (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_ispri (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_isstr (int /*<<< orphan*/ ) ; 
 scalar_t__ irt_type (int /*<<< orphan*/ ) ; 
 scalar_t__ itype2irt (TYPE_2__*) ; 
 scalar_t__ lj_ir_kint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_ir_knum_u64 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_ir_kstr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ir_kvalue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_2__* lj_tab_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  strV (TYPE_2__*) ; 

__attribute__((used)) static TRef fwd_ahload(jit_State *J, IRRef xref)
{
  IRIns *xr = IR(xref);
  IRRef lim = xref;  /* Search limit. */
  IRRef ref;

  /* Search for conflicting stores. */
  ref = J->chain[fins->o+IRDELTA_L2S];
  while (ref > xref) {
    IRIns *store = IR(ref);
    switch (aa_ahref(J, xr, IR(store->op1))) {
    case ALIAS_NO:   break;  /* Continue searching. */
    case ALIAS_MAY:  lim = ref; goto cselim;  /* Limit search for load. */
    case ALIAS_MUST: return store->op2;  /* Store forwarding. */
    }
    ref = store->prev;
  }

  /* No conflicting store (yet): const-fold loads from allocations. */
  {
    IRIns *ir = (xr->o == IR_HREFK || xr->o == IR_AREF) ? IR(xr->op1) : xr;
    IRRef tab = ir->op1;
    ir = IR(tab);
    if (ir->o == IR_TNEW || (ir->o == IR_TDUP && irref_isk(xr->op2))) {
      /* A NEWREF with a number key may end up pointing to the array part.
      ** But it's referenced from HSTORE and not found in the ASTORE chain.
      ** For now simply consider this a conflict without forwarding anything.
      */
      if (xr->o == IR_AREF) {
	IRRef ref2 = J->chain[IR_NEWREF];
	while (ref2 > tab) {
	  IRIns *newref = IR(ref2);
	  if (irt_isnum(IR(newref->op2)->t))
	    goto cselim;
	  ref2 = newref->prev;
	}
      }
      /* NEWREF inhibits CSE for HREF, and dependent FLOADs from HREFK/AREF.
      ** But the above search for conflicting stores was limited by xref.
      ** So continue searching, limited by the TNEW/TDUP. Store forwarding
      ** is ok, too. A conflict does NOT limit the search for a matching load.
      */
      while (ref > tab) {
	IRIns *store = IR(ref);
	switch (aa_ahref(J, xr, IR(store->op1))) {
	case ALIAS_NO:   break;  /* Continue searching. */
	case ALIAS_MAY:  goto cselim;  /* Conflicting store. */
	case ALIAS_MUST: return store->op2;  /* Store forwarding. */
	}
	ref = store->prev;
      }
      lua_assert(ir->o != IR_TNEW || irt_isnil(fins->t));
      if (irt_ispri(fins->t)) {
	return TREF_PRI(irt_type(fins->t));
      } else if (irt_isnum(fins->t) || (LJ_DUALNUM && irt_isint(fins->t)) ||
		 irt_isstr(fins->t)) {
	TValue keyv;
	cTValue *tv;
	IRIns *key = IR(xr->op2);
	if (key->o == IR_KSLOT) key = IR(key->op1);
	lj_ir_kvalue(J->L, &keyv, key);
	tv = lj_tab_get(J->L, ir_ktab(IR(ir->op1)), &keyv);
	lua_assert(itype2irt(tv) == irt_type(fins->t));
	if (irt_isnum(fins->t))
	  return lj_ir_knum_u64(J, tv->u64);
	else if (LJ_DUALNUM && irt_isint(fins->t))
	  return lj_ir_kint(J, intV(tv));
	else
	  return lj_ir_kstr(J, strV(tv));
      }
      /* Othwerwise: don't intern as a constant. */
    }
  }

cselim:
  /* Try to find a matching load. Below the conflicting store, if any. */
  ref = J->chain[fins->o];
  while (ref > lim) {
    IRIns *load = IR(ref);
    if (load->op1 == xref)
      return ref;  /* Load forwarding. */
    ref = load->prev;
  }
  return 0;  /* Conflict or no match. */
}