#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {size_t nactvar; scalar_t__* varmap; int /*<<< orphan*/  kt; } ;
struct TYPE_7__ {size_t vtop; size_t sizevstack; TYPE_4__* vstack; int /*<<< orphan*/  L; TYPE_2__* fs; } ;
typedef  size_t MSize ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_2__ FuncState ;
typedef  size_t BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_XLIMC ; 
 int /*<<< orphan*/  LJ_MAX_LOCVAR ; 
 scalar_t__ LJ_MAX_VSTACK ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 uintptr_t VARNAME__MAX ; 
 int /*<<< orphan*/  VarInfo ; 
 int /*<<< orphan*/  checklimit (TYPE_2__*,size_t,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lj_lex_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lj_mem_growvec (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_tab_getstr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void var_new(LexState *ls, BCReg n, GCstr *name)
{
  FuncState *fs = ls->fs;
  MSize vtop = ls->vtop;
  checklimit(fs, fs->nactvar+n, LJ_MAX_LOCVAR, "local variables");
  if (LJ_UNLIKELY(vtop >= ls->sizevstack)) {
    if (ls->sizevstack >= LJ_MAX_VSTACK)
      lj_lex_error(ls, 0, LJ_ERR_XLIMC, LJ_MAX_VSTACK);
    lj_mem_growvec(ls->L, ls->vstack, ls->sizevstack, LJ_MAX_VSTACK, VarInfo);
  }
  lua_assert((uintptr_t)name < VARNAME__MAX ||
	     lj_tab_getstr(fs->kt, name) != NULL);
  /* NOBARRIER: name is anchored in fs->kt and ls->vstack is not a GCobj. */
  setgcref(ls->vstack[vtop].name, obj2gco(name));
  fs->varmap[fs->nactvar+n] = (uint16_t)vtop;
  ls->vtop = vtop+1;
}