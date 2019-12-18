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
struct TYPE_8__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  cTValue ;
typedef  int /*<<< orphan*/  GCtab ;

/* Variables and functions */
 char* LUA_FFILIBNAME ; 
 int /*<<< orphan*/  copyTV (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lj_gc_anybarriert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_str_newlit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * lj_tab_getstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_tab_setstr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * registry (TYPE_1__*) ; 
 int /*<<< orphan*/ * tabV (int /*<<< orphan*/ *) ; 
 scalar_t__ tvistab (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffi_register_module(lua_State *L)
{
  cTValue *tmp = lj_tab_getstr(tabV(registry(L)), lj_str_newlit(L, "_LOADED"));
  if (tmp && tvistab(tmp)) {
    GCtab *t = tabV(tmp);
    copyTV(L, lj_tab_setstr(L, t, lj_str_newlit(L, LUA_FFILIBNAME)), L->top-1);
    lj_gc_anybarriert(L, t);
  }
}