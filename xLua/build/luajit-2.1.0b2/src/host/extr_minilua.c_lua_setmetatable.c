#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/ * top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_19__ {struct TYPE_19__* metatable; } ;
typedef  TYPE_2__ Table ;
struct TYPE_20__ {TYPE_2__* metatable; } ;
struct TYPE_17__ {TYPE_2__** mt; } ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 TYPE_15__* G (TYPE_1__*) ; 
 int /*<<< orphan*/  api_checknelems (TYPE_1__*,int) ; 
 int /*<<< orphan*/  api_checkvalidindex (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* hvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * index2adr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaC_objbarrier (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  luaC_objbarriert (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  luai_apicheck (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rawuvalue (int /*<<< orphan*/ *) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttistable (int /*<<< orphan*/ *) ; 
 size_t ttype (int /*<<< orphan*/ *) ; 
 TYPE_3__* uvalue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lua_setmetatable(lua_State*L,int objindex){
TValue*obj;
Table*mt;
api_checknelems(L,1);
obj=index2adr(L,objindex);
api_checkvalidindex(L,obj);
if(ttisnil(L->top-1))
mt=NULL;
else{
luai_apicheck(L,ttistable(L->top-1));
mt=hvalue(L->top-1);
}
switch(ttype(obj)){
case 5:{
hvalue(obj)->metatable=mt;
if(mt)
luaC_objbarriert(L,hvalue(obj),mt);
break;
}
case 7:{
uvalue(obj)->metatable=mt;
if(mt)
luaC_objbarrier(L,rawuvalue(obj),mt);
break;
}
default:{
G(L)->mt[ttype(obj)]=mt;
break;
}
}
L->top--;
return 1;
}