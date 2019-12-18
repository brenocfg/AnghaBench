#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_2__ lua_State ;
typedef  int /*<<< orphan*/  lua_CFunction ;
struct TYPE_11__ {int /*<<< orphan*/  env; } ;
struct TYPE_13__ {TYPE_1__ c; } ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  int /*<<< orphan*/  GCfunc ;

/* Variables and functions */
 TYPE_9__* curr_func (TYPE_2__*) ; 
 int /*<<< orphan*/  lj_gc_anybarriert (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lj_lib_pushcf (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lj_str_newz (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  lj_tab_setstr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setfuncV (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tabref (int /*<<< orphan*/ ) ; 

int lj_lib_postreg(lua_State *L, lua_CFunction cf, int id, const char *name)
{
  GCfunc *fn = lj_lib_pushcf(L, cf, id);
  GCtab *t = tabref(curr_func(L)->c.env);  /* Reference to parent table. */
  setfuncV(L, lj_tab_setstr(L, t, lj_str_newz(L, name)), fn);
  lj_gc_anybarriert(L, t);
  setfuncV(L, L->top++, fn);
  return 1;
}