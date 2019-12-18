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
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static const char*luaL_findtable(lua_State*L,int idx,
const char*fname,int szhint){
const char*e;
lua_pushvalue(L,idx);
do{
e=strchr(fname,'.');
if(e==NULL)e=fname+strlen(fname);
lua_pushlstring(L,fname,e-fname);
lua_rawget(L,-2);
if(lua_isnil(L,-1)){
lua_pop(L,1);
lua_createtable(L,0,(*e=='.'?1:szhint));
lua_pushlstring(L,fname,e-fname);
lua_pushvalue(L,-2);
lua_settable(L,-4);
}
else if(!lua_istable(L,-1)){
lua_pop(L,2);
return fname;
}
lua_remove(L,-2);
fname=e+1;
}while(*e=='.');
return NULL;
}