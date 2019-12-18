#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ top; TYPE_3__* base_ci; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_14__ {scalar_t__ i_ci; } ;
typedef  TYPE_2__ lua_Debug ;
struct TYPE_15__ {scalar_t__ func; } ;
typedef  scalar_t__ StkId ;
typedef  int /*<<< orphan*/  Closure ;
typedef  TYPE_3__ CallInfo ;

/* Variables and functions */
 int auxgetinfo (TYPE_1__*,char const*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * clvalue (scalar_t__) ; 
 int /*<<< orphan*/  collectvalidlines (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  luai_apicheck (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setclvalue (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnilvalue (scalar_t__) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  ttisfunction (scalar_t__) ; 

__attribute__((used)) static int lua_getinfo(lua_State*L,const char*what,lua_Debug*ar){
int status;
Closure*f=NULL;
CallInfo*ci=NULL;
if(*what=='>'){
StkId func=L->top-1;
luai_apicheck(L,ttisfunction(func));
what++;
f=clvalue(func);
L->top--;
}
else if(ar->i_ci!=0){
ci=L->base_ci+ar->i_ci;
f=clvalue(ci->func);
}
status=auxgetinfo(L,what,ar,f,ci);
if(strchr(what,'f')){
if(f==NULL)setnilvalue(L->top);
else setclvalue(L,L->top,f);
incr_top(L);
}
if(strchr(what,'L'))
collectvalidlines(L,f);
return status;
}