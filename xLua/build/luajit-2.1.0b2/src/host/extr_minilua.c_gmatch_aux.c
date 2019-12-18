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
typedef  int lua_Integer ;
struct TYPE_4__ {char const* src_init; char const* src_end; scalar_t__ level; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ MatchState ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 char* match (TYPE_1__*,char const*,char const*) ; 
 int push_captures (TYPE_1__*,char const*,char const*) ; 

__attribute__((used)) static int gmatch_aux(lua_State*L){
MatchState ms;
size_t ls;
const char*s=lua_tolstring(L,lua_upvalueindex(1),&ls);
const char*p=lua_tostring(L,lua_upvalueindex(2));
const char*src;
ms.L=L;
ms.src_init=s;
ms.src_end=s+ls;
for(src=s+(size_t)lua_tointeger(L,lua_upvalueindex(3));
src<=ms.src_end;
src++){
const char*e;
ms.level=0;
if((e=match(&ms,src,p))!=NULL){
lua_Integer newstart=e-s;
if(e==src)newstart++;
lua_pushinteger(L,newstart);
lua_replace(L,lua_upvalueindex(3));
return push_captures(&ms,src,e);
}
}
return 0;
}