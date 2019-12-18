#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  sizeupvalues; int /*<<< orphan*/  upvalues; int /*<<< orphan*/  sizelocvars; int /*<<< orphan*/  locvars; int /*<<< orphan*/  sizelineinfo; int /*<<< orphan*/  lineinfo; int /*<<< orphan*/  sizek; int /*<<< orphan*/  k; int /*<<< orphan*/  sizep; int /*<<< orphan*/  p; int /*<<< orphan*/  sizecode; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ Proto ;

/* Variables and functions */
 int /*<<< orphan*/  luaM_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  luaM_freearray (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void luaF_freeproto (lua_State *L, Proto *f) {
  luaM_freearray(L, f->code, f->sizecode);
  luaM_freearray(L, f->p, f->sizep);
  luaM_freearray(L, f->k, f->sizek);
  luaM_freearray(L, f->lineinfo, f->sizelineinfo);
  luaM_freearray(L, f->locvars, f->sizelocvars);
  luaM_freearray(L, f->upvalues, f->sizeupvalues);
  luaM_free(L, f);
}