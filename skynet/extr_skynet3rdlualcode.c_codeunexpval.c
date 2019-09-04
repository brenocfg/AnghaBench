#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  info; } ;
struct TYPE_7__ {int /*<<< orphan*/  k; TYPE_1__ u; } ;
typedef  TYPE_2__ expdesc ;
typedef  int /*<<< orphan*/  OpCode ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  VRELOCABLE ; 
 int /*<<< orphan*/  freeexp (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_codeABC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int luaK_exp2anyreg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_fixline (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void codeunexpval (FuncState *fs, OpCode op, expdesc *e, int line) {
  int r = luaK_exp2anyreg(fs, e);  /* opcodes operate only on registers */
  freeexp(fs, e);
  e->u.info = luaK_codeABC(fs, op, 0, r, 0);  /* generate opcode */
  e->k = VRELOCABLE;  /* all those operations are relocatable */
  luaK_fixline(fs, line);
}