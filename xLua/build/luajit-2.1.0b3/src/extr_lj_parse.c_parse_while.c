#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  pc; int /*<<< orphan*/  nactvar; int /*<<< orphan*/  lasttarget; } ;
struct TYPE_16__ {TYPE_2__* fs; } ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ FuncState ;
typedef  int /*<<< orphan*/  FuncScope ;
typedef  int /*<<< orphan*/  BCPos ;
typedef  int /*<<< orphan*/  BCLine ;

/* Variables and functions */
 int /*<<< orphan*/  BC_LOOP ; 
 int /*<<< orphan*/  FSCOPE_LOOP ; 
 int /*<<< orphan*/  TK_do ; 
 int /*<<< orphan*/  TK_end ; 
 int /*<<< orphan*/  TK_while ; 
 int /*<<< orphan*/  bcemit_AD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcemit_jmp (TYPE_2__*) ; 
 int /*<<< orphan*/  expr_cond (TYPE_1__*) ; 
 int /*<<< orphan*/  fscope_begin (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscope_end (TYPE_2__*) ; 
 int /*<<< orphan*/  jmp_patch (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_patchins (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_tohere (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lex_check (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lex_match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_block (TYPE_1__*) ; 

__attribute__((used)) static void parse_while(LexState *ls, BCLine line)
{
  FuncState *fs = ls->fs;
  BCPos start, loop, condexit;
  FuncScope bl;
  lj_lex_next(ls);  /* Skip 'while'. */
  start = fs->lasttarget = fs->pc;
  condexit = expr_cond(ls);
  fscope_begin(fs, &bl, FSCOPE_LOOP);
  lex_check(ls, TK_do);
  loop = bcemit_AD(fs, BC_LOOP, fs->nactvar, 0);
  parse_block(ls);
  jmp_patch(fs, bcemit_jmp(fs), start);
  lex_match(ls, TK_end, TK_while, line);
  fscope_end(fs);
  jmp_tohere(fs, condexit);
  jmp_patchins(fs, loop, fs->pc);
}