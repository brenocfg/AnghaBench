#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* f; } ;
struct TYPE_5__ {int /*<<< orphan*/ * code; } ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */
 int GETARG_A (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_OPCODE (int /*<<< orphan*/ ) ; 
 int NO_JUMP ; 
 scalar_t__ OP_JMP ; 
 int /*<<< orphan*/  SETARG_A (int /*<<< orphan*/ ,int) ; 
 int getjump (TYPE_2__*,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

void luaK_patchclose (FuncState *fs, int list, int level) {
  level++;  /* argument is +1 to reserve 0 as non-op */
  for (; list != NO_JUMP; list = getjump(fs, list)) {
    lua_assert(GET_OPCODE(fs->f->code[list]) == OP_JMP &&
                (GETARG_A(fs->f->code[list]) == 0 ||
                 GETARG_A(fs->f->code[list]) >= level));
    SETARG_A(fs->f->code[list], level);
  }
}