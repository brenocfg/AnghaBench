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
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_Ax (int /*<<< orphan*/ ,int) ; 
 int MAXARG_Ax ; 
 int /*<<< orphan*/  OP_EXTRAARG ; 
 int luaK_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static int codeextraarg (FuncState *fs, int a) {
  lua_assert(a <= MAXARG_Ax);
  return luaK_code(fs, CREATE_Ax(OP_EXTRAARG, a));
}