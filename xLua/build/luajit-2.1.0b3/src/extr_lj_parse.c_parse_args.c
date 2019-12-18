#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int info; int aux; } ;
struct TYPE_23__ {TYPE_1__ s; int /*<<< orphan*/  sval; } ;
struct TYPE_27__ {scalar_t__ k; TYPE_2__ u; } ;
struct TYPE_26__ {int freereg; int pc; TYPE_3__* bcbase; } ;
struct TYPE_25__ {scalar_t__ linenumber; char tok; scalar_t__ lastline; int /*<<< orphan*/  tokval; TYPE_5__* fs; } ;
struct TYPE_24__ {scalar_t__ line; } ;
typedef  TYPE_4__ LexState ;
typedef  TYPE_5__ FuncState ;
typedef  TYPE_6__ ExpDesc ;
typedef  int BCReg ;
typedef  scalar_t__ BCLine ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 int /*<<< orphan*/  BCINS_ABC (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  BC_CALL ; 
 int /*<<< orphan*/  BC_CALLM ; 
 int /*<<< orphan*/  LJ_ERR_XAMBIG ; 
 int /*<<< orphan*/  LJ_ERR_XFUNARG ; 
 int LJ_FR2 ; 
 char TK_string ; 
 scalar_t__ VCALL ; 
 scalar_t__ VKSTR ; 
 scalar_t__ VNONRELOC ; 
 scalar_t__ VVOID ; 
 int /*<<< orphan*/  bcemit_INS (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcptr (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  err_syntax (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr_init (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr_list (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  expr_table (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  expr_tonextreg (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  lex_match (TYPE_4__*,char,char,scalar_t__) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_4__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setbc_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strV (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void parse_args(LexState *ls, ExpDesc *e)
{
  FuncState *fs = ls->fs;
  ExpDesc args;
  BCIns ins;
  BCReg base;
  BCLine line = ls->linenumber;
  if (ls->tok == '(') {
#if !LJ_52
    if (line != ls->lastline)
      err_syntax(ls, LJ_ERR_XAMBIG);
#endif
    lj_lex_next(ls);
    if (ls->tok == ')') {  /* f(). */
      args.k = VVOID;
    } else {
      expr_list(ls, &args);
      if (args.k == VCALL)  /* f(a, b, g()) or f(a, b, ...). */
	setbc_b(bcptr(fs, &args), 0);  /* Pass on multiple results. */
    }
    lex_match(ls, ')', '(', line);
  } else if (ls->tok == '{') {
    expr_table(ls, &args);
  } else if (ls->tok == TK_string) {
    expr_init(&args, VKSTR, 0);
    args.u.sval = strV(&ls->tokval);
    lj_lex_next(ls);
  } else {
    err_syntax(ls, LJ_ERR_XFUNARG);
    return;  /* Silence compiler. */
  }
  lua_assert(e->k == VNONRELOC);
  base = e->u.s.info;  /* Base register for call. */
  if (args.k == VCALL) {
    ins = BCINS_ABC(BC_CALLM, base, 2, args.u.s.aux - base - 1 - LJ_FR2);
  } else {
    if (args.k != VVOID)
      expr_tonextreg(fs, &args);
    ins = BCINS_ABC(BC_CALL, base, 2, fs->freereg - base - LJ_FR2);
  }
  expr_init(e, VCALL, bcemit_INS(fs, ins));
  e->u.s.aux = base;
  fs->bcbase[fs->pc - 1].line = line;
  fs->freereg = base+1;  /* Leave one result by default. */
}