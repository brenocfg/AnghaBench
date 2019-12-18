#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_34__ {scalar_t__ info; } ;
struct TYPE_35__ {TYPE_1__ s; int /*<<< orphan*/  nval; } ;
struct TYPE_39__ {scalar_t__ k; TYPE_2__ u; int /*<<< orphan*/  t; int /*<<< orphan*/  f; } ;
struct TYPE_38__ {scalar_t__ freereg; } ;
struct TYPE_37__ {scalar_t__ ctypeid; } ;
struct TYPE_36__ {scalar_t__ u64; } ;
typedef  TYPE_3__ TValue ;
typedef  TYPE_4__ GCcdata ;
typedef  TYPE_5__ FuncState ;
typedef  TYPE_6__ ExpDesc ;
typedef  int /*<<< orphan*/  BCPos ;
typedef  scalar_t__ BCOp ;

/* Variables and functions */
 scalar_t__ BC_LEN ; 
 scalar_t__ BC_NOT ; 
 scalar_t__ BC_UNM ; 
 scalar_t__ CTID_COMPLEX_DOUBLE ; 
 scalar_t__ LJ_HASFFI ; 
 scalar_t__ U64x (int,int) ; 
 scalar_t__ VJMP ; 
 scalar_t__ VKCDATA ; 
 scalar_t__ VKFALSE ; 
 scalar_t__ VKNIL ; 
 scalar_t__ VKTRUE ; 
 scalar_t__ VNONRELOC ; 
 scalar_t__ VRELOCABLE ; 
 scalar_t__ bcemit_AD (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bcptr (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  bcreg_reserve (TYPE_5__*,int) ; 
 TYPE_4__* cdataV (int /*<<< orphan*/ *) ; 
 scalar_t__ cdataptr (TYPE_4__*) ; 
 int /*<<< orphan*/  expr_discharge (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  expr_free (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  expr_hasjump (TYPE_6__*) ; 
 scalar_t__ expr_isk (TYPE_6__*) ; 
 scalar_t__ expr_isnumk (TYPE_6__*) ; 
 int /*<<< orphan*/  expr_numiszero (TYPE_6__*) ; 
 TYPE_3__* expr_numtv (TYPE_6__*) ; 
 int /*<<< orphan*/  expr_toanyreg (TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ intV (TYPE_3__*) ; 
 int /*<<< orphan*/  invertcond (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  jmp_dropval (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setbc_a (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setintV (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  setnumV (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ tvisint (TYPE_3__*) ; 

__attribute__((used)) static void bcemit_unop(FuncState *fs, BCOp op, ExpDesc *e)
{
  if (op == BC_NOT) {
    /* Swap true and false lists. */
    { BCPos temp = e->f; e->f = e->t; e->t = temp; }
    jmp_dropval(fs, e->f);
    jmp_dropval(fs, e->t);
    expr_discharge(fs, e);
    if (e->k == VKNIL || e->k == VKFALSE) {
      e->k = VKTRUE;
      return;
    } else if (expr_isk(e) || (LJ_HASFFI && e->k == VKCDATA)) {
      e->k = VKFALSE;
      return;
    } else if (e->k == VJMP) {
      invertcond(fs, e);
      return;
    } else if (e->k == VRELOCABLE) {
      bcreg_reserve(fs, 1);
      setbc_a(bcptr(fs, e), fs->freereg-1);
      e->u.s.info = fs->freereg-1;
      e->k = VNONRELOC;
    } else {
      lua_assert(e->k == VNONRELOC);
    }
  } else {
    lua_assert(op == BC_UNM || op == BC_LEN);
    if (op == BC_UNM && !expr_hasjump(e)) {  /* Constant-fold negations. */
#if LJ_HASFFI
      if (e->k == VKCDATA) {  /* Fold in-place since cdata is not interned. */
	GCcdata *cd = cdataV(&e->u.nval);
	int64_t *p = (int64_t *)cdataptr(cd);
	if (cd->ctypeid == CTID_COMPLEX_DOUBLE)
	  p[1] ^= (int64_t)U64x(80000000,00000000);
	else
	  *p = -*p;
	return;
      } else
#endif
      if (expr_isnumk(e) && !expr_numiszero(e)) {  /* Avoid folding to -0. */
	TValue *o = expr_numtv(e);
	if (tvisint(o)) {
	  int32_t k = intV(o);
	  if (k == -k)
	    setnumV(o, -(lua_Number)k);
	  else
	    setintV(o, -k);
	  return;
	} else {
	  o->u64 ^= U64x(80000000,00000000);
	  return;
	}
      }
    }
    expr_toanyreg(fs, e);
  }
  expr_free(fs, e);
  e->u.s.info = bcemit_AD(fs, op, 0, e->u.s.info);
  e->k = VRELOCABLE;
}