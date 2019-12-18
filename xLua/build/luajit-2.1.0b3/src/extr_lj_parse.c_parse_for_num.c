#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {size_t pc; TYPE_1__* bcbase; int /*<<< orphan*/  freereg; } ;
struct TYPE_19__ {TYPE_3__* fs; } ;
struct TYPE_18__ {int /*<<< orphan*/  line; } ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_3__ FuncState ;
typedef  int /*<<< orphan*/  FuncScope ;
typedef  int /*<<< orphan*/  BCReg ;
typedef  size_t BCPos ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FORI ; 
 int /*<<< orphan*/  BC_FORL ; 
 int /*<<< orphan*/  BC_KSHORT ; 
 int /*<<< orphan*/  FORL_EXT ; 
 int /*<<< orphan*/  FORL_IDX ; 
 int /*<<< orphan*/  FORL_STEP ; 
 int /*<<< orphan*/  FORL_STOP ; 
 int /*<<< orphan*/  NO_JMP ; 
 char TK_do ; 
 int /*<<< orphan*/  VARNAME_FOR_IDX ; 
 int /*<<< orphan*/  VARNAME_FOR_STEP ; 
 int /*<<< orphan*/  VARNAME_FOR_STOP ; 
 int /*<<< orphan*/  bcemit_AD (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t bcemit_AJ (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcreg_reserve (TYPE_3__*,int) ; 
 int /*<<< orphan*/  expr_next (TYPE_2__*) ; 
 int /*<<< orphan*/  fscope_begin (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscope_end (TYPE_3__*) ; 
 int /*<<< orphan*/  jmp_patchins (TYPE_3__*,size_t,size_t) ; 
 int /*<<< orphan*/  lex_check (TYPE_2__*,char) ; 
 scalar_t__ lex_opt (TYPE_2__*,char) ; 
 int /*<<< orphan*/  parse_block (TYPE_2__*) ; 
 int /*<<< orphan*/  var_add (TYPE_2__*,int) ; 
 int /*<<< orphan*/  var_new (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_new_fixed (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_for_num(LexState *ls, GCstr *varname, BCLine line)
{
  FuncState *fs = ls->fs;
  BCReg base = fs->freereg;
  FuncScope bl;
  BCPos loop, loopend;
  /* Hidden control variables. */
  var_new_fixed(ls, FORL_IDX, VARNAME_FOR_IDX);
  var_new_fixed(ls, FORL_STOP, VARNAME_FOR_STOP);
  var_new_fixed(ls, FORL_STEP, VARNAME_FOR_STEP);
  /* Visible copy of index variable. */
  var_new(ls, FORL_EXT, varname);
  lex_check(ls, '=');
  expr_next(ls);
  lex_check(ls, ',');
  expr_next(ls);
  if (lex_opt(ls, ',')) {
    expr_next(ls);
  } else {
    bcemit_AD(fs, BC_KSHORT, fs->freereg, 1);  /* Default step is 1. */
    bcreg_reserve(fs, 1);
  }
  var_add(ls, 3);  /* Hidden control variables. */
  lex_check(ls, TK_do);
  loop = bcemit_AJ(fs, BC_FORI, base, NO_JMP);
  fscope_begin(fs, &bl, 0);  /* Scope for visible variables. */
  var_add(ls, 1);
  bcreg_reserve(fs, 1);
  parse_block(ls);
  fscope_end(fs);
  /* Perform loop inversion. Loop control instructions are at the end. */
  loopend = bcemit_AJ(fs, BC_FORL, base, NO_JMP);
  fs->bcbase[loopend].line = line;  /* Fix line for control ins. */
  jmp_patchins(fs, loopend, loop+1);
  jmp_patchins(fs, loop, fs->pc);
}