#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ nuse; int size; } ;
struct TYPE_5__ {int /*<<< orphan*/  buff; TYPE_1__ strt; } ;
typedef  TYPE_2__ global_State ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int LUA_MINBUFFER ; 
 int MINSTRTABSIZE ; 
 scalar_t__ cast (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lu_int32 ; 
 int /*<<< orphan*/  luaS_resize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaZ_resizebuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int luaZ_sizebuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void checkSizes (lua_State *L) {
  global_State *g = G(L);
  /* check size of string hash */
  if (g->strt.nuse < cast(lu_int32, g->strt.size/4) &&
      g->strt.size > MINSTRTABSIZE*2)
    luaS_resize(L, g->strt.size/2);  /* table is too big */
  /* check size of buffer */
  if (luaZ_sizebuffer(&g->buff) > LUA_MINBUFFER*2) {  /* buffer too big? */
    size_t newsize = luaZ_sizebuffer(&g->buff) / 2;
    luaZ_resizebuffer(L, &g->buff, newsize);
  }
}