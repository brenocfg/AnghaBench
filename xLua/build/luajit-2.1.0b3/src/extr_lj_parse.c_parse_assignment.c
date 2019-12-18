#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_11__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  aux; int /*<<< orphan*/  info; } ;
struct TYPE_30__ {TYPE_1__ s; } ;
struct TYPE_33__ {scalar_t__ k; TYPE_2__ u; } ;
struct TYPE_27__ {scalar_t__ k; } ;
struct TYPE_32__ {TYPE_11__ v; struct TYPE_32__* prev; } ;
struct TYPE_31__ {scalar_t__ level; TYPE_15__* fs; } ;
struct TYPE_28__ {scalar_t__ freereg; } ;
typedef  TYPE_3__ LexState ;
typedef  TYPE_4__ LHSVarList ;
typedef  TYPE_5__ ExpDesc ;
typedef  scalar_t__ BCReg ;

/* Variables and functions */
 scalar_t__ BC_VARG ; 
 int /*<<< orphan*/  LJ_ERR_XSYNTAX ; 
 int /*<<< orphan*/  LJ_MAX_XLEVEL ; 
 scalar_t__ VCALL ; 
 scalar_t__ VINDEXED ; 
 scalar_t__ VLOCAL ; 
 scalar_t__ VNONRELOC ; 
 scalar_t__ VRELOCABLE ; 
 int /*<<< orphan*/  assign_adjust (TYPE_3__*,scalar_t__,scalar_t__,TYPE_5__*) ; 
 int /*<<< orphan*/  assign_hazard (TYPE_3__*,TYPE_4__*,TYPE_11__*) ; 
 scalar_t__ bc_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcemit_store (TYPE_15__*,TYPE_11__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * bcptr (TYPE_15__*,TYPE_5__*) ; 
 int /*<<< orphan*/  checkcond (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checklimit (TYPE_15__*,scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  expr_init (TYPE_5__*,scalar_t__,scalar_t__) ; 
 scalar_t__ expr_list (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  expr_primary (TYPE_3__*,TYPE_11__*) ; 
 int /*<<< orphan*/  lex_check (TYPE_3__*,char) ; 
 scalar_t__ lex_opt (TYPE_3__*,char) ; 

__attribute__((used)) static void parse_assignment(LexState *ls, LHSVarList *lh, BCReg nvars)
{
  ExpDesc e;
  checkcond(ls, VLOCAL <= lh->v.k && lh->v.k <= VINDEXED, LJ_ERR_XSYNTAX);
  if (lex_opt(ls, ',')) {  /* Collect LHS list and recurse upwards. */
    LHSVarList vl;
    vl.prev = lh;
    expr_primary(ls, &vl.v);
    if (vl.v.k == VLOCAL)
      assign_hazard(ls, lh, &vl.v);
    checklimit(ls->fs, ls->level + nvars, LJ_MAX_XLEVEL, "variable names");
    parse_assignment(ls, &vl, nvars+1);
  } else {  /* Parse RHS. */
    BCReg nexps;
    lex_check(ls, '=');
    nexps = expr_list(ls, &e);
    if (nexps == nvars) {
      if (e.k == VCALL) {
	if (bc_op(*bcptr(ls->fs, &e)) == BC_VARG) {  /* Vararg assignment. */
	  ls->fs->freereg--;
	  e.k = VRELOCABLE;
	} else {  /* Multiple call results. */
	  e.u.s.info = e.u.s.aux;  /* Base of call is not relocatable. */
	  e.k = VNONRELOC;
	}
      }
      bcemit_store(ls->fs, &lh->v, &e);
      return;
    }
    assign_adjust(ls, nvars, nexps, &e);
  }
  /* Assign RHS to LHS and recurse downwards. */
  expr_init(&e, VNONRELOC, ls->fs->freereg-1);
  bcemit_store(ls->fs, &lh->v, &e);
}