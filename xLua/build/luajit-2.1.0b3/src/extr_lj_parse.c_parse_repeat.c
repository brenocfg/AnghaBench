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
struct TYPE_20__ {int flags; } ;
struct TYPE_19__ {int /*<<< orphan*/  pc; int /*<<< orphan*/  nactvar; int /*<<< orphan*/  lasttarget; } ;
struct TYPE_18__ {TYPE_2__* fs; } ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ FuncState ;
typedef  TYPE_3__ FuncScope ;
typedef  int /*<<< orphan*/  BCPos ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  BC_LOOP ; 
 int /*<<< orphan*/  FSCOPE_LOOP ; 
 int FSCOPE_UPVAL ; 
 int /*<<< orphan*/  TK_repeat ; 
 int /*<<< orphan*/  TK_until ; 
 int /*<<< orphan*/  bcemit_AD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcemit_jmp (TYPE_2__*) ; 
 int /*<<< orphan*/  expr_cond (TYPE_1__*) ; 
 int /*<<< orphan*/  fscope_begin (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscope_end (TYPE_2__*) ; 
 int /*<<< orphan*/  jmp_patch (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_patchins (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_tohere (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lex_match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_break (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_chunk (TYPE_1__*) ; 

__attribute__((used)) static void parse_repeat(LexState *ls, BCLine line)
{
  FuncState *fs = ls->fs;
  BCPos loop = fs->lasttarget = fs->pc;
  BCPos condexit;
  FuncScope bl1, bl2;
  fscope_begin(fs, &bl1, FSCOPE_LOOP);  /* Breakable loop scope. */
  fscope_begin(fs, &bl2, 0);  /* Inner scope. */
  lj_lex_next(ls);  /* Skip 'repeat'. */
  bcemit_AD(fs, BC_LOOP, fs->nactvar, 0);
  parse_chunk(ls);
  lex_match(ls, TK_until, TK_repeat, line);
  condexit = expr_cond(ls);  /* Parse condition (still inside inner scope). */
  if (!(bl2.flags & FSCOPE_UPVAL)) {  /* No upvalues? Just end inner scope. */
    fscope_end(fs);
  } else {  /* Otherwise generate: cond: UCLO+JMP out, !cond: UCLO+JMP loop. */
    parse_break(ls);  /* Break from loop and close upvalues. */
    jmp_tohere(fs, condexit);
    fscope_end(fs);  /* End inner scope and close upvalues. */
    condexit = bcemit_jmp(fs);
  }
  jmp_patch(fs, condexit, loop);  /* Jump backwards if !cond. */
  jmp_patchins(fs, loop, fs->pc);
  fscope_end(fs);  /* End loop scope. */
}