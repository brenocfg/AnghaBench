#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ currentline; int /*<<< orphan*/  short_src; } ;
typedef  TYPE_1__ lua_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  lua_getinfo (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 scalar_t__ lua_getstack (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void luaL_where(lua_State*L,int level){
lua_Debug ar;
if(lua_getstack(L,level,&ar)){
lua_getinfo(L,"Sl",&ar);
if(ar.currentline>0){
lua_pushfstring(L,"%s:%d: ",ar.short_src,ar.currentline);
return;
}
}
lua_pushliteral(L,"");
}