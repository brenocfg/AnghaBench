#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OpCode ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ABC (int /*<<< orphan*/ ,int,int,int) ; 
 int MAXARG_A ; 
 int MAXARG_B ; 
 int MAXARG_C ; 
 scalar_t__ OpArgN ; 
 scalar_t__ getBMode (int /*<<< orphan*/ ) ; 
 scalar_t__ getCMode (int /*<<< orphan*/ ) ; 
 scalar_t__ getOpMode (int /*<<< orphan*/ ) ; 
 scalar_t__ iABC ; 
 int luaK_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

int luaK_codeABC (FuncState *fs, OpCode o, int a, int b, int c) {
  lua_assert(getOpMode(o) == iABC);
  lua_assert(getBMode(o) != OpArgN || b == 0);
  lua_assert(getCMode(o) != OpArgN || c == 0);
  lua_assert(a <= MAXARG_A && b <= MAXARG_B && c <= MAXARG_C);
  return luaK_code(fs, CREATE_ABC(o, a, b, c));
}