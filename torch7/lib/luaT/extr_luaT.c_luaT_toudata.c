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

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  luaT_pushmetatable (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_rawequal (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 void** lua_touserdata (int /*<<< orphan*/ *,int) ; 

void *luaT_toudata(lua_State *L, int ud, const char *tname)
{
  void **p = lua_touserdata(L, ud);
  if(p != NULL) /* value is a userdata? */
  {
    if(!luaT_pushmetatable(L, tname))
      luaL_error(L, "Torch internal problem: cannot find metatable for type <%s>", tname);

    /* initialize the table we want to get the metatable on */
    /* note that we have to be careful with indices, as we just inserted stuff */
    lua_pushvalue(L, (ud < 0 ? ud - 1 : ud));
    while(lua_getmetatable(L, -1)) /* get the next metatable */
    {
      lua_remove(L, -2); /* remove the previous metatable [or object, if first time] */
      if(lua_rawequal(L, -1, -2))
      {
        lua_pop(L, 2);  /* remove the two metatables */
        return *p;
      }
    }
    lua_pop(L, 2); /* remove the two metatables */
  }
  return NULL;
}