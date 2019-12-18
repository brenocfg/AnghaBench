#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int freereg; int /*<<< orphan*/  ls; } ;
typedef  TYPE_1__ FuncState ;

/* Variables and functions */
 int LFIELDS_PER_FLUSH ; 
 int LUA_MULTRET ; 
 int MAXARG_Ax ; 
 int MAXARG_C ; 
 int /*<<< orphan*/  OP_SETLIST ; 
 int /*<<< orphan*/  codeextraarg (TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaK_codeABC (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  luaX_syntaxerror (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

void luaK_setlist (FuncState *fs, int base, int nelems, int tostore) {
  int c =  (nelems - 1)/LFIELDS_PER_FLUSH + 1;
  int b = (tostore == LUA_MULTRET) ? 0 : tostore;
  lua_assert(tostore != 0 && tostore <= LFIELDS_PER_FLUSH);
  if (c <= MAXARG_C)
    luaK_codeABC(fs, OP_SETLIST, base, b, c);
  else if (c <= MAXARG_Ax) {
    luaK_codeABC(fs, OP_SETLIST, base, b, 0);
    codeextraarg(fs, c);
  }
  else
    luaX_syntaxerror(fs->ls, "constructor too long");
  fs->freereg = base + 1;  /* free registers with list values */
}