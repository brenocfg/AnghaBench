#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {scalar_t__ flags; int /*<<< orphan*/  metatable; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  const TValue ;
typedef  int /*<<< orphan*/  const* StkId ;

/* Variables and functions */
 int /*<<< orphan*/  TM_NEWINDEX ; 
 int /*<<< orphan*/  callTM (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* fasttm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* hvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  luaC_barriert (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  luaG_runerror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaG_typeerror (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  const* luaH_set (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* luaT_gettmbyobj (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisfunction (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttistable (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void luaV_settable(lua_State*L,const TValue*t,TValue*key,StkId val){
int loop;
TValue temp;
for(loop=0;loop<100;loop++){
const TValue*tm;
if(ttistable(t)){
Table*h=hvalue(t);
TValue*oldval=luaH_set(L,h,key);
if(!ttisnil(oldval)||
(tm=fasttm(L,h->metatable,TM_NEWINDEX))==NULL){
setobj(L,oldval,val);
h->flags=0;
luaC_barriert(L,h,val);
return;
}
}
else if(ttisnil(tm=luaT_gettmbyobj(L,t,TM_NEWINDEX)))
luaG_typeerror(L,t,"index");
if(ttisfunction(tm)){
callTM(L,tm,t,key,val);
return;
}
setobj(L,&temp,tm);
t=&temp;
}
luaG_runerror(L,"loop in settable");
}