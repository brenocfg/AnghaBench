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
 int LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*,...) ; 
 char* luaT_classrootname (char const*) ; 
 int /*<<< orphan*/  luaT_cmt__call ; 
 int /*<<< orphan*/  luaT_cmt__newindex ; 
 int luaT_fullparentname (char const*,char*) ; 
 int /*<<< orphan*/  luaT_getinnerparent (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaT_mt__add ; 
 int /*<<< orphan*/  luaT_mt__call ; 
 int /*<<< orphan*/  luaT_mt__concat ; 
 int /*<<< orphan*/  luaT_mt__div ; 
 int /*<<< orphan*/  luaT_mt__eq ; 
 int /*<<< orphan*/  luaT_mt__index ; 
 int /*<<< orphan*/  luaT_mt__le ; 
 int /*<<< orphan*/  luaT_mt__len ; 
 int /*<<< orphan*/  luaT_mt__lt ; 
 int /*<<< orphan*/  luaT_mt__mod ; 
 int /*<<< orphan*/  luaT_mt__mul ; 
 int /*<<< orphan*/  luaT_mt__newindex ; 
 int /*<<< orphan*/  luaT_mt__pow ; 
 int /*<<< orphan*/  luaT_mt__sub ; 
 int /*<<< orphan*/  luaT_mt__tostring ; 
 int /*<<< orphan*/  luaT_mt__unm ; 
 int /*<<< orphan*/  luaT_pushmetatable (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushglobaltable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 

int luaT_lua_newmetatable(lua_State *L)
{
  /* Local Variables */
  const char* tname = luaL_checkstring(L, 1);
  char parent_name[256];
  int is_in_module = 0;

  /* Argument Checking */
  lua_settop(L, 6);
  luaL_argcheck(L, lua_isnoneornil(L, 2) || lua_isstring(L, 2), 2, "parent class name or nil expected");
  luaL_argcheck(L, lua_isnoneornil(L, 3) || lua_isfunction(L, 3), 3, "constructor function or nil expected");
  luaL_argcheck(L, lua_isnoneornil(L, 4) || lua_isfunction(L, 4), 4, "destructor function or nil expected");
  luaL_argcheck(L, lua_isnoneornil(L, 5) || lua_isfunction(L, 5), 5, "factory function or nil expected");
  luaL_argcheck(L, lua_isnoneornil(L, 6) || lua_istable(L, 6), 6, "module table or nil expected");

  /* Push immediate parent module to stack */
  if(lua_isnoneornil(L, 6)) {
    lua_pop(L, 1); /* remove the nil */
    is_in_module = luaT_fullparentname(tname, parent_name);
    if (is_in_module)
      luaT_getinnerparent(L, tname);
    else
      lua_pushglobaltable(L);
  }

  if(!lua_istable(L, -1))
    luaL_error(L, "while creating metatable %s: bad argument #1 (%s is an invalid module name)", tname, parent_name);

  /* we first create the new metaclass if we have to */
  if(!luaT_pushmetatable(L, tname))
  {
    /* create the metatable */
    lua_newtable(L);

    /* registry[name] = metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, LUA_REGISTRYINDEX, tname);

    /* registry[metatable] = tname */
    lua_pushvalue(L, -1);
    lua_pushstring(L, tname);
    lua_rawset(L, LUA_REGISTRYINDEX);

    /* __index handling */
    lua_pushcfunction(L, luaT_mt__index);
    lua_setfield(L, -2, "__index");

    /* __newindex handling */
    lua_pushcfunction(L, luaT_mt__newindex);
    lua_setfield(L, -2, "__newindex");

    /* __typename contains the typename */
    lua_pushstring(L, tname);
    lua_setfield(L, -2, "__typename");

    /* __metatable is self */
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__metatable");

    /* by default, __version equals 1 */
    lua_pushnumber(L, 1);
    lua_setfield(L, -2, "__version");

    /* assign default operator functions */
    lua_pushcfunction(L, luaT_mt__tostring);
    lua_setfield(L, -2, "__tostring");

    lua_pushcfunction(L, luaT_mt__add);
    lua_setfield(L, -2, "__add");

    lua_pushcfunction(L, luaT_mt__sub);
    lua_setfield(L, -2, "__sub");

    lua_pushcfunction(L, luaT_mt__mul);
    lua_setfield(L, -2, "__mul");

    lua_pushcfunction(L, luaT_mt__div);
    lua_setfield(L, -2, "__div");

    lua_pushcfunction(L, luaT_mt__mod);
    lua_setfield(L, -2, "__mod");

    lua_pushcfunction(L, luaT_mt__pow);
    lua_setfield(L, -2, "__pow");

    lua_pushcfunction(L, luaT_mt__unm);
    lua_setfield(L, -2, "__unm");

    lua_pushcfunction(L, luaT_mt__concat);
    lua_setfield(L, -2, "__concat");

    lua_pushcfunction(L, luaT_mt__len);
    lua_setfield(L, -2, "__len");

    lua_pushcfunction(L, luaT_mt__eq);
    lua_setfield(L, -2, "__eq");

    lua_pushcfunction(L, luaT_mt__lt);
    lua_setfield(L, -2, "__lt");

    lua_pushcfunction(L, luaT_mt__le);
    lua_setfield(L, -2, "__le");

    lua_pushcfunction(L, luaT_mt__call);
    lua_setfield(L, -2, "__call");
  }

  /* we assign the parent class if necessary */
  if(!lua_isnoneornil(L, 2))
  {
    if(lua_getmetatable(L, -1))
      luaL_error(L, "class %s has been already assigned a parent class\n", tname);
    else
    {
      const char* parent_tname = luaL_checkstring(L, 2);
      if(!luaT_pushmetatable(L, parent_tname))
        luaL_error(L, "bad argument #2 (invalid parent class name %s)", parent_tname);
      lua_setmetatable(L, -2);
    }
  }

  /* register the destructor function  */
  if(!lua_isnoneornil(L, 4))
  {
    /* does it exists already? */
    lua_pushstring(L, "__gc");
    lua_rawget(L, -2);

    if(lua_isnil(L, -1))
    {
      lua_pop(L, 1); /* pop nil */
      lua_pushstring(L, "__gc");
      lua_pushvalue(L, 4);
      lua_rawset(L, -3);
    }
    else
      luaL_error(L, "%s has been already assigned a destructor", tname);
  }

  /* register the factory function  */
  if(!lua_isnoneornil(L, 5))
  {
    /* does it exists already? */
    lua_pushstring(L, "__factory");
    lua_rawget(L, -2);

    if(lua_isnil(L, -1))
    {
      lua_pop(L, 1); /* pop nil */
      lua_pushstring(L, "__factory");
      lua_pushvalue(L, 5);
      lua_rawset(L, -3);
    }
    else
      luaL_error(L, "%s has been already assigned a factory", tname);
  }

  /******** Constructor table and metatable ********/
  lua_pushstring(L, "__constructor");
  lua_rawget(L, -2);
  if(lua_isnil(L, -1))
  {
    lua_pop(L, 1);                        /* pop nil */
    lua_newtable(L);                      /* fancy table */
    lua_newtable(L);                      /* fancy metatable */

    lua_pushvalue(L, -3);                 /* metatable */
    lua_setfield(L, -2, "__index");       /* so we can get the methods */

    lua_pushcfunction(L, luaT_cmt__newindex);
    lua_setfield(L, -2, "__newindex");    /* so we add new methods */

    lua_pushcfunction(L, luaT_cmt__call);
    lua_setfield(L, -2, "__call");        /* so we can create, we are here for only that */

    lua_pushvalue(L, -3);
    lua_setfield(L, -2, "__metatable");   /* redirect to metatable with methods */

    lua_setmetatable(L, -2);              /* constructor metatable is ... this fancy metatable */

    /* set metatable[__constructor] = constructor-metatable */
    lua_pushstring(L, "__constructor");
    lua_pushvalue(L, -2);
    lua_rawset(L, -4);
  }

  /* register the constructor function  */
  if(!lua_isnoneornil(L, 3))
  {
    /* get constructor metatable */
    lua_getmetatable(L, -1);

    /* does it exists already? */
    lua_pushstring(L, "__new");
    lua_rawget(L, -2);

    if(lua_isnil(L, -1))
    {
      lua_pop(L, 1); /* pop nil */
      lua_pushstring(L, "__new");
      lua_pushvalue(L, 3);
      lua_rawset(L, -3);

      /* set "new" in the metatable too */
      lua_pushstring(L, "new");
      lua_pushvalue(L, 3);
      lua_rawset(L, -5);
    }
    else
      luaL_error(L, "%s has been already assigned a constructor", tname);

    /* pop constructor metatable */
    lua_pop(L, 1);
  }

  /* module.name = constructor metatable */
  lua_setfield(L, 6, luaT_classrootname(tname));

  return 1; /* returns the metatable */
}