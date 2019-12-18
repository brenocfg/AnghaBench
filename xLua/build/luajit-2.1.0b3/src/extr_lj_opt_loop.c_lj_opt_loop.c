#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ top; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_11__ {int /*<<< orphan*/  nsnapmap; int /*<<< orphan*/  nsnap; int /*<<< orphan*/  nins; } ;
struct TYPE_13__ {int /*<<< orphan*/  instunroll; TYPE_2__* L; TYPE_1__ cur; } ;
typedef  TYPE_3__ jit_State ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  TraceError ;
struct TYPE_14__ {scalar_t__ sizesubst; int /*<<< orphan*/ * subst; TYPE_3__* J; } ;
typedef  int /*<<< orphan*/  SnapNo ;
typedef  int /*<<< orphan*/  MSize ;
typedef  TYPE_4__ LoopState ;
typedef  int /*<<< orphan*/  IRRef ;

/* Variables and functions */
 int /*<<< orphan*/  IRRef1 ; 
 int /*<<< orphan*/  J2G (TYPE_3__*) ; 
#define  LJ_TRERR_GFAIL 129 
#define  LJ_TRERR_TYPEINS 128 
 scalar_t__ LJ_UNLIKELY (int) ; 
 int LUA_ERRRUN ; 
 int /*<<< orphan*/  cploop_opt ; 
 int /*<<< orphan*/  lj_err_throw (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lj_mem_freevec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int lj_vm_cpcall (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_undo (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numberVint (scalar_t__) ; 
 scalar_t__ tvisnumber (scalar_t__) ; 

int lj_opt_loop(jit_State *J)
{
  IRRef nins = J->cur.nins;
  SnapNo nsnap = J->cur.nsnap;
  MSize nsnapmap = J->cur.nsnapmap;
  LoopState lps;
  int errcode;
  lps.J = J;
  lps.subst = NULL;
  lps.sizesubst = 0;
  errcode = lj_vm_cpcall(J->L, NULL, &lps, cploop_opt);
  lj_mem_freevec(J2G(J), lps.subst, lps.sizesubst, IRRef1);
  if (LJ_UNLIKELY(errcode)) {
    lua_State *L = J->L;
    if (errcode == LUA_ERRRUN && tvisnumber(L->top-1)) {  /* Trace error? */
      int32_t e = numberVint(L->top-1);
      switch ((TraceError)e) {
      case LJ_TRERR_TYPEINS:  /* Type instability. */
      case LJ_TRERR_GFAIL:  /* Guard would always fail. */
	/* Unrolling via recording fixes many cases, e.g. a flipped boolean. */
	if (--J->instunroll < 0)  /* But do not unroll forever. */
	  break;
	L->top--;  /* Remove error object. */
	loop_undo(J, nins, nsnap, nsnapmap);
	return 1;  /* Loop optimization failed, continue recording. */
      default:
	break;
      }
    }
    lj_err_throw(L, errcode);  /* Propagate all other errors. */
  }
  return 0;  /* Loop optimization is ok. */
}