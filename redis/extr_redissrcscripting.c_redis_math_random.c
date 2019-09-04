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
typedef  int lua_Number ;

/* Variables and functions */
 int REDIS_LRAND48_MAX ; 
 int /*<<< orphan*/  floor (int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int redisLrand48 () ; 

int redis_math_random (lua_State *L) {
  /* the `%' avoids the (rare) case of r==1, and is needed also because on
     some systems (SunOS!) `rand()' may return a value larger than RAND_MAX */
  lua_Number r = (lua_Number)(redisLrand48()%REDIS_LRAND48_MAX) /
                                (lua_Number)REDIS_LRAND48_MAX;
  switch (lua_gettop(L)) {  /* check number of arguments */
    case 0: {  /* no arguments */
      lua_pushnumber(L, r);  /* Number between 0 and 1 */
      break;
    }
    case 1: {  /* only upper limit */
      int u = luaL_checkint(L, 1);
      luaL_argcheck(L, 1<=u, 1, "interval is empty");
      lua_pushnumber(L, floor(r*u)+1);  /* int between 1 and `u' */
      break;
    }
    case 2: {  /* lower and upper limits */
      int l = luaL_checkint(L, 1);
      int u = luaL_checkint(L, 2);
      luaL_argcheck(L, l<=u, 2, "interval is empty");
      lua_pushnumber(L, floor(r*(u-l+1))+l);  /* int between `l' and `u' */
      break;
    }
    default: return luaL_error(L, "wrong number of arguments");
  }
  return 1;
}