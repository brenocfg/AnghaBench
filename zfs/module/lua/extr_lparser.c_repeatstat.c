#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  nactvar; scalar_t__ upval; } ;
struct TYPE_9__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  TYPE_2__ BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  TK_REPEAT ; 
 int /*<<< orphan*/  TK_UNTIL ; 
 int /*<<< orphan*/  check_match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cond (TYPE_1__*) ; 
 int /*<<< orphan*/  enterblock (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  leaveblock (int /*<<< orphan*/ *) ; 
 int luaK_getlabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_patchclose (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_patchlist (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaX_next (TYPE_1__*) ; 
 int /*<<< orphan*/  statlist (TYPE_1__*) ; 

__attribute__((used)) static void repeatstat (LexState *ls, int line) {
  /* repeatstat -> REPEAT block UNTIL cond */
  int condexit;
  FuncState *fs = ls->fs;
  int repeat_init = luaK_getlabel(fs);
  BlockCnt bl1, bl2;
  enterblock(fs, &bl1, 1);  /* loop block */
  enterblock(fs, &bl2, 0);  /* scope block */
  luaX_next(ls);  /* skip REPEAT */
  statlist(ls);
  check_match(ls, TK_UNTIL, TK_REPEAT, line);
  condexit = cond(ls);  /* read condition (inside scope block) */
  if (bl2.upval)  /* upvalues? */
    luaK_patchclose(fs, condexit, bl2.nactvar);
  leaveblock(fs);  /* finish scope */
  luaK_patchlist(fs, condexit, repeat_init);  /* close the loop */
  leaveblock(fs);  /* finish loop */
}