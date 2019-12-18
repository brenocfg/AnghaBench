#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ top; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_12__ {void* env; } ;
struct TYPE_15__ {TYPE_1__ c; } ;
struct TYPE_14__ {void* env; } ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  api_checknelems (TYPE_2__*,int) ; 
 int /*<<< orphan*/  api_checkvalidindex (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* clvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gt (int /*<<< orphan*/ ) ; 
 void* hvalue (scalar_t__) ; 
 int /*<<< orphan*/  index2adr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  luaC_objbarrier (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  luai_apicheck (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sethvalue (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  thvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttistable (scalar_t__) ; 
 int ttype (int /*<<< orphan*/ ) ; 
 TYPE_3__* uvalue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lua_setfenv(lua_State*L,int idx){
StkId o;
int res=1;
api_checknelems(L,1);
o=index2adr(L,idx);
api_checkvalidindex(L,o);
luai_apicheck(L,ttistable(L->top-1));
switch(ttype(o)){
case 6:
clvalue(o)->c.env=hvalue(L->top-1);
break;
case 7:
uvalue(o)->env=hvalue(L->top-1);
break;
case 8:
sethvalue(L,gt(thvalue(o)),hvalue(L->top-1));
break;
default:
res=0;
break;
}
if(res)luaC_objbarrier(L,gcvalue(o),hvalue(L->top-1));
L->top--;
return res;
}