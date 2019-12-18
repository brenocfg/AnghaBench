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
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  set2 (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ sort_comp (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void auxsort(lua_State*L,int l,int u){
while(l<u){
int i,j;
lua_rawgeti(L,1,l);
lua_rawgeti(L,1,u);
if(sort_comp(L,-1,-2))
set2(L,l,u);
else
lua_pop(L,2);
if(u-l==1)break;
i=(l+u)/2;
lua_rawgeti(L,1,i);
lua_rawgeti(L,1,l);
if(sort_comp(L,-2,-1))
set2(L,i,l);
else{
lua_pop(L,1);
lua_rawgeti(L,1,u);
if(sort_comp(L,-1,-2))
set2(L,i,u);
else
lua_pop(L,2);
}
if(u-l==2)break;
lua_rawgeti(L,1,i);
lua_pushvalue(L,-1);
lua_rawgeti(L,1,u-1);
set2(L,i,u-1);
i=l;j=u-1;
for(;;){
while(lua_rawgeti(L,1,++i),sort_comp(L,-1,-2)){
if(i>u)luaL_error(L,"invalid order function for sorting");
lua_pop(L,1);
}
while(lua_rawgeti(L,1,--j),sort_comp(L,-3,-1)){
if(j<l)luaL_error(L,"invalid order function for sorting");
lua_pop(L,1);
}
if(j<i){
lua_pop(L,3);
break;
}
set2(L,i,j);
}
lua_rawgeti(L,1,u-1);
lua_rawgeti(L,1,i);
set2(L,u-1,i);
if(i-l<u-i){
j=l;i=i-1;l=i+2;
}
else{
j=i+1;i=u;u=j-2;
}
auxsort(L,j,i);
}
}