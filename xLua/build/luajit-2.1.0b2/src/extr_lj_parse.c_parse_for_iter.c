#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int freereg; int pc; TYPE_1__* bcbase; } ;
struct TYPE_24__ {void* linenumber; TYPE_3__* fs; } ;
struct TYPE_23__ {void* line; } ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_3__ FuncState ;
typedef  int /*<<< orphan*/  FuncScope ;
typedef  int /*<<< orphan*/  ExpDesc ;
typedef  int BCReg ;
typedef  int BCPos ;
typedef  void* BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  BC_ISNEXT ; 
 int /*<<< orphan*/  BC_ITERC ; 
 int /*<<< orphan*/  BC_ITERL ; 
 int /*<<< orphan*/  BC_ITERN ; 
 int /*<<< orphan*/  BC_JMP ; 
 scalar_t__ LJ_FR2 ; 
 int /*<<< orphan*/  NO_JMP ; 
 int /*<<< orphan*/  TK_do ; 
 int /*<<< orphan*/  TK_in ; 
 int /*<<< orphan*/  VARNAME_FOR_CTL ; 
 int /*<<< orphan*/  VARNAME_FOR_GEN ; 
 int /*<<< orphan*/  VARNAME_FOR_STATE ; 
 int /*<<< orphan*/  assign_adjust (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcemit_ABC (TYPE_3__*,int /*<<< orphan*/ ,int,int,int) ; 
 int bcemit_AJ (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcreg_bump (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  bcreg_reserve (TYPE_3__*,int) ; 
 int /*<<< orphan*/  expr_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscope_begin (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscope_end (TYPE_3__*) ; 
 int /*<<< orphan*/  jmp_patchins (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  lex_check (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lex_opt (TYPE_2__*,char) ; 
 int /*<<< orphan*/ * lex_str (TYPE_2__*) ; 
 int /*<<< orphan*/  parse_block (TYPE_2__*) ; 
 scalar_t__ predict_next (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  var_add (TYPE_2__*,int) ; 
 int /*<<< orphan*/  var_new (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_new_fixed (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_for_iter(LexState *ls, GCstr *indexname)
{
  FuncState *fs = ls->fs;
  ExpDesc e;
  BCReg nvars = 0;
  BCLine line;
  BCReg base = fs->freereg + 3;
  BCPos loop, loopend, exprpc = fs->pc;
  FuncScope bl;
  int isnext;
  /* Hidden control variables. */
  var_new_fixed(ls, nvars++, VARNAME_FOR_GEN);
  var_new_fixed(ls, nvars++, VARNAME_FOR_STATE);
  var_new_fixed(ls, nvars++, VARNAME_FOR_CTL);
  /* Visible variables returned from iterator. */
  var_new(ls, nvars++, indexname);
  while (lex_opt(ls, ','))
    var_new(ls, nvars++, lex_str(ls));
  lex_check(ls, TK_in);
  line = ls->linenumber;
  assign_adjust(ls, 3, expr_list(ls, &e), &e);
  /* The iterator needs another 3 [4] slots (func [pc] | state ctl). */
  bcreg_bump(fs, 3+LJ_FR2);
  isnext = (nvars <= 5 && predict_next(ls, fs, exprpc));
  var_add(ls, 3);  /* Hidden control variables. */
  lex_check(ls, TK_do);
  loop = bcemit_AJ(fs, isnext ? BC_ISNEXT : BC_JMP, base, NO_JMP);
  fscope_begin(fs, &bl, 0);  /* Scope for visible variables. */
  var_add(ls, nvars-3);
  bcreg_reserve(fs, nvars-3);
  parse_block(ls);
  fscope_end(fs);
  /* Perform loop inversion. Loop control instructions are at the end. */
  jmp_patchins(fs, loop, fs->pc);
  bcemit_ABC(fs, isnext ? BC_ITERN : BC_ITERC, base, nvars-3+1, 2+1);
  loopend = bcemit_AJ(fs, BC_ITERL, base, NO_JMP);
  fs->bcbase[loopend-1].line = line;  /* Fix line for control ins. */
  fs->bcbase[loopend].line = line;
  jmp_patchins(fs, loopend, loop+1);
}