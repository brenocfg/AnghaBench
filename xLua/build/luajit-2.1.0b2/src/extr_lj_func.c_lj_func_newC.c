#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  bc_cfunc_ext; } ;
struct TYPE_5__ {int /*<<< orphan*/  env; int /*<<< orphan*/  pc; scalar_t__ nupvalues; int /*<<< orphan*/  ffid; int /*<<< orphan*/  gct; } ;
struct TYPE_6__ {TYPE_1__ c; } ;
typedef  scalar_t__ MSize ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  TYPE_2__ GCfunc ;

/* Variables and functions */
 int /*<<< orphan*/  FF_C ; 
 TYPE_4__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LJ_TFUNC ; 
 scalar_t__ lj_mem_newgco (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sizeCfunc (scalar_t__) ; 

GCfunc *lj_func_newC(lua_State *L, MSize nelems, GCtab *env)
{
  GCfunc *fn = (GCfunc *)lj_mem_newgco(L, sizeCfunc(nelems));
  fn->c.gct = ~LJ_TFUNC;
  fn->c.ffid = FF_C;
  fn->c.nupvalues = (uint8_t)nelems;
  /* NOBARRIER: The GCfunc is new (marked white). */
  setmref(fn->c.pc, &G(L)->bc_cfunc_ext);
  setgcref(fn->c.env, obj2gco(env));
  return fn;
}