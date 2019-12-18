#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int f; int /*<<< orphan*/  t; } ;
typedef  TYPE_2__ expdesc ;
struct TYPE_15__ {scalar_t__ token; } ;
struct TYPE_17__ {TYPE_1__ t; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_3__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  BlockCnt ;

/* Variables and functions */
 scalar_t__ TK_BREAK ; 
 scalar_t__ TK_ELSE ; 
 scalar_t__ TK_ELSEIF ; 
 scalar_t__ TK_GOTO ; 
 int /*<<< orphan*/  TK_THEN ; 
 scalar_t__ block_follow (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checknext (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enterblock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  gotostat (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaveblock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_concat (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  luaK_goiffalse (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_goiftrue (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int luaK_jump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_patchtohere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaX_next (TYPE_3__*) ; 
 int /*<<< orphan*/  statlist (TYPE_3__*) ; 
 scalar_t__ testnext (TYPE_3__*,char) ; 

__attribute__((used)) static void test_then_block (LexState *ls, int *escapelist) {
  /* test_then_block -> [IF | ELSEIF] cond THEN block */
  BlockCnt bl;
  FuncState *fs = ls->fs;
  expdesc v;
  int jf;  /* instruction to skip 'then' code (if condition is false) */
  luaX_next(ls);  /* skip IF or ELSEIF */
  expr(ls, &v);  /* read condition */
  checknext(ls, TK_THEN);
  if (ls->t.token == TK_GOTO || ls->t.token == TK_BREAK) {
    luaK_goiffalse(ls->fs, &v);  /* will jump to label if condition is true */
    enterblock(fs, &bl, 0);  /* must enter block before 'goto' */
    gotostat(ls, v.t);  /* handle goto/break */
	while (testnext(ls, ';')) {}  /* skip semicolons */
    if (block_follow(ls, 0)) {  /* 'goto' is the entire block? */
      leaveblock(fs);
      return;  /* and that is it */
    }
    else  /* must skip over 'then' part if condition is false */
      jf = luaK_jump(fs);
  }
  else {  /* regular case (not goto/break) */
    luaK_goiftrue(ls->fs, &v);  /* skip over block if condition is false */
    enterblock(fs, &bl, 0);
    jf = v.f;
  }
  statlist(ls);  /* 'then' part */
  leaveblock(fs);
  if (ls->t.token == TK_ELSE ||
      ls->t.token == TK_ELSEIF)  /* followed by 'else'/'elseif'? */
    luaK_concat(fs, escapelist, luaK_jump(fs));  /* must jump over it */
  luaK_patchtohere(fs, jf);
}