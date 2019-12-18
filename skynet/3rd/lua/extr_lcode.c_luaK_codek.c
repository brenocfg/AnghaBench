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
 int MAXARG_Bx ; 
 int /*<<< orphan*/  OP_LOADK ; 
 int /*<<< orphan*/  OP_LOADKX ; 
 int /*<<< orphan*/  codeextraarg (int /*<<< orphan*/ *,int) ; 
 int luaK_codeABx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

int luaK_codek (FuncState *fs, int reg, int k) {
  if (k <= MAXARG_Bx)
    return luaK_codeABx(fs, OP_LOADK, reg, k);
  else {
    int p = luaK_codeABx(fs, OP_LOADKX, reg, 0);
    codeextraarg(fs, k);
    return p;
  }
}