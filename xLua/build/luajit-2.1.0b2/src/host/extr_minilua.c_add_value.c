#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_6__ {int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ MatchState ;

/* Variables and functions */
 int /*<<< orphan*/  add_s (TYPE_1__*,int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  luaL_addvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int push_captures (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  push_onecapture (TYPE_1__*,int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static void add_value(MatchState*ms,luaL_Buffer*b,const char*s,
const char*e){
lua_State*L=ms->L;
switch(lua_type(L,3)){
case 3:
case 4:{
add_s(ms,b,s,e);
return;
}
case 6:{
int n;
lua_pushvalue(L,3);
n=push_captures(ms,s,e);
lua_call(L,n,1);
break;
}
case 5:{
push_onecapture(ms,0,s,e);
lua_gettable(L,3);
break;
}
}
if(!lua_toboolean(L,-1)){
lua_pop(L,1);
lua_pushlstring(L,s,e-s);
}
else if(!lua_isstring(L,-1))
luaL_error(L,"invalid replacement value (a %s)",luaL_typename(L,-1));
luaL_addvalue(b);
}