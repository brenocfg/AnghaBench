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
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 

__attribute__((used)) static int luaB_newproxy(lua_State*L){
lua_settop(L,1);
lua_newuserdata(L,0);
if(lua_toboolean(L,1)==0)
return 1;
else if(lua_isboolean(L,1)){
lua_newtable(L);
lua_pushvalue(L,-1);
lua_pushboolean(L,1);
lua_rawset(L,lua_upvalueindex(1));
}
else{
int validproxy=0;
if(lua_getmetatable(L,1)){
lua_rawget(L,lua_upvalueindex(1));
validproxy=lua_toboolean(L,-1);
lua_pop(L,1);
}
luaL_argcheck(L,validproxy,1,"boolean or proxy expected");
lua_getmetatable(L,1);
}
lua_setmetatable(L,2);
return 1;
}