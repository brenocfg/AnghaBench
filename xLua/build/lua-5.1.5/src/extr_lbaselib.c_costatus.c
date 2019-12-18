#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Debug ;

/* Variables and functions */
 int CO_DEAD ; 
 int CO_NOR ; 
 int CO_RUN ; 
 int CO_SUS ; 
#define  LUA_YIELD 128 
 int /*<<< orphan*/  lua_getstack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_status (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int costatus (lua_State *L, lua_State *co) {
  if (L == co) return CO_RUN;
  switch (lua_status(co)) {
    case LUA_YIELD:
      return CO_SUS;
    case 0: {
      lua_Debug ar;
      if (lua_getstack(co, 0, &ar) > 0)  /* does it have frames? */
        return CO_NOR;  /* it is running */
      else if (lua_gettop(co) == 0)
          return CO_DEAD;
      else
        return CO_SUS;  /* initial state */
    }
    default:  /* some error occured */
      return CO_DEAD;
  }
}