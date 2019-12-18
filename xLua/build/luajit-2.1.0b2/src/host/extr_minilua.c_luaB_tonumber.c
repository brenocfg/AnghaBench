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
typedef  int /*<<< orphan*/  lua_Number ;

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_checkany (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_optint (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static int luaB_tonumber(lua_State*L){
int base=luaL_optint(L,2,10);
if(base==10){
luaL_checkany(L,1);
if(lua_isnumber(L,1)){
lua_pushnumber(L,lua_tonumber(L,1));
return 1;
}
}
else{
const char*s1=luaL_checkstring(L,1);
char*s2;
unsigned long n;
luaL_argcheck(L,2<=base&&base<=36,2,"base out of range");
n=strtoul(s1,&s2,base);
if(s1!=s2){
while(isspace((unsigned char)(*s2)))s2++;
if(*s2=='\0'){
lua_pushnumber(L,(lua_Number)n);
return 1;
}
}
}
lua_pushnil(L);
return 1;
}