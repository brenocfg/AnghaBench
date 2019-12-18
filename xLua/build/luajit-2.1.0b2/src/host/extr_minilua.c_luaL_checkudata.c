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
 int /*<<< orphan*/  luaL_typerror (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char const*) ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_rawequal (int /*<<< orphan*/ *,int,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void*luaL_checkudata(lua_State*L,int ud,const char*tname){
void*p=lua_touserdata(L,ud);
if(p!=NULL){
if(lua_getmetatable(L,ud)){
lua_getfield(L,(-10000),tname);
if(lua_rawequal(L,-1,-2)){
lua_pop(L,2);
return p;
}
}
}
luaL_typerror(L,ud,tname);
return NULL;
}