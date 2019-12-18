#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  TK_DO ; 
 int /*<<< orphan*/  TK_END ; 
 int /*<<< orphan*/  TK_WHILE ; 
 int /*<<< orphan*/  block (TYPE_1__*) ; 
 int /*<<< orphan*/  check_match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  checknext (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int cond (TYPE_1__*) ; 
 int /*<<< orphan*/  enterblock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  leaveblock (int /*<<< orphan*/ *) ; 
 int luaK_getlabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_jump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_patchlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaK_patchtohere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaX_next (TYPE_1__*) ; 

__attribute__((used)) static void whilestat(LexState*ls,int line){
FuncState*fs=ls->fs;
int whileinit;
int condexit;
BlockCnt bl;
luaX_next(ls);
whileinit=luaK_getlabel(fs);
condexit=cond(ls);
enterblock(fs,&bl,1);
checknext(ls,TK_DO);
block(ls);
luaK_patchlist(fs,luaK_jump(fs),whileinit);
check_match(ls,TK_END,TK_WHILE,line);
leaveblock(fs);
luaK_patchtohere(fs,condexit);
}