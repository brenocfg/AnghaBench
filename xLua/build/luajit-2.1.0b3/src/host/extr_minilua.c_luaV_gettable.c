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
struct TYPE_4__ {int /*<<< orphan*/  metatable; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  TM_INDEX ; 
 int /*<<< orphan*/  callTMres (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fasttm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* hvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  luaG_runerror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaG_typeerror (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * luaH_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaT_gettmbyobj (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisfunction (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttistable (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void luaV_gettable(lua_State*L,const TValue*t,TValue*key,StkId val){
int loop;
for(loop=0;loop<100;loop++){
const TValue*tm;
if(ttistable(t)){
Table*h=hvalue(t);
const TValue*res=luaH_get(h,key);
if(!ttisnil(res)||
(tm=fasttm(L,h->metatable,TM_INDEX))==NULL){
setobj(L,val,res);
return;
}
}
else if(ttisnil(tm=luaT_gettmbyobj(L,t,TM_INDEX)))
luaG_typeerror(L,t,"index");
if(ttisfunction(tm)){
callTMres(L,val,tm,t,key);
return;
}
t=tm;
}
luaG_runerror(L,"loop in gettable");
}