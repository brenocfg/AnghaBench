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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {scalar_t__ k; TYPE_1__* sp; } ;
struct TYPE_5__ {scalar_t__ l_G; scalar_t__ code; scalar_t__ lineinfo; scalar_t__ locvars; scalar_t__ upvalues; scalar_t__ k; int /*<<< orphan*/  sizek; int /*<<< orphan*/  sizeupvalues; int /*<<< orphan*/  sizelocvars; int /*<<< orphan*/  sizelineinfo; int /*<<< orphan*/  sizecode; } ;
typedef  TYPE_1__ SharedProto ;
typedef  TYPE_2__ Proto ;

/* Variables and functions */
 scalar_t__ G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaM_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  luaM_freearray (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freesharedproto (lua_State *L, Proto *pf) {
  SharedProto *f = pf->sp;
  if (f == NULL)
    return;
  if (G(L) == f->l_G) {
    luaM_freearray(L, f->code, f->sizecode);
    luaM_freearray(L, f->lineinfo, f->sizelineinfo);
    luaM_freearray(L, f->locvars, f->sizelocvars);
    luaM_freearray(L, f->upvalues, f->sizeupvalues);
    luaM_freearray(L, f->k, f->sizek);
    luaM_free(L, f);
  } else if (pf->k != f->k) {
    luaM_freearray(L, pf->k, f->sizek);
  }
}