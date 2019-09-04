#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  upval; } ;
struct TYPE_10__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  TYPE_2__ BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  TK_REPEAT ; 
 int /*<<< orphan*/  TK_UNTIL ; 
 int /*<<< orphan*/  breakstat (TYPE_1__*) ; 
 int /*<<< orphan*/  check_match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chunk (TYPE_1__*) ; 
 int cond (TYPE_1__*) ; 
 int /*<<< orphan*/  enterblock (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  leaveblock (int /*<<< orphan*/ *) ; 
 int luaK_getlabel (int /*<<< orphan*/ *) ; 
 int luaK_jump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_patchlist (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaK_patchtohere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaX_next (TYPE_1__*) ; 

__attribute__((used)) static void repeatstat (LexState *ls, int line) {
  /* repeatstat -> REPEAT block UNTIL cond */
  int condexit;
  FuncState *fs = ls->fs;
  int repeat_init = luaK_getlabel(fs);
  BlockCnt bl1, bl2;
  enterblock(fs, &bl1, 1);  /* loop block */
  enterblock(fs, &bl2, 0);  /* scope block */
  luaX_next(ls);  /* skip REPEAT */
  chunk(ls);
  check_match(ls, TK_UNTIL, TK_REPEAT, line);
  condexit = cond(ls);  /* read condition (inside scope block) */
  if (!bl2.upval) {  /* no upvalues? */
    leaveblock(fs);  /* finish scope */
    luaK_patchlist(ls->fs, condexit, repeat_init);  /* close the loop */
  }
  else {  /* complete semantics when there are upvalues */
    breakstat(ls);  /* if condition then break */
    luaK_patchtohere(ls->fs, condexit);  /* else... */
    leaveblock(fs);  /* finish scope... */
    luaK_patchlist(ls->fs, luaK_jump(fs), repeat_init);  /* and repeat */
  }
  leaveblock(fs);  /* finish loop */
}