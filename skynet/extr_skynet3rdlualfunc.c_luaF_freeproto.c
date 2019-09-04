#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {TYPE_1__* sp; int /*<<< orphan*/  p; } ;
struct TYPE_6__ {int /*<<< orphan*/  sizep; } ;
typedef  TYPE_2__ Proto ;

/* Variables and functions */
 int /*<<< orphan*/  freesharedproto (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaM_free (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaM_freearray (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void luaF_freeproto (lua_State *L, Proto *f) {
  luaM_freearray(L, f->p, f->sp->sizep);
  freesharedproto(L, f);
  luaM_free(L, f);
}