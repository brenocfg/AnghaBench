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
typedef  int l_mem ;
struct TYPE_5__ {int GCestimate; int gcpause; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 int MAX_LMEM ; 
 int PAUSEADJ ; 
 int gettotalbytes (TYPE_1__*) ; 
 int /*<<< orphan*/  luaE_setdebt (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void setpause (global_State *g) {
  l_mem threshold, debt;
  l_mem estimate = g->GCestimate / PAUSEADJ;  /* adjust 'estimate' */
  lua_assert(estimate > 0);
  threshold = (g->gcpause < MAX_LMEM / estimate)  /* overflow? */
            ? estimate * g->gcpause  /* no overflow */
            : MAX_LMEM;  /* overflow; truncate to maximum */
  debt = gettotalbytes(g) - threshold;
  luaE_setdebt(g, debt);
}