#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ top; scalar_t__ stack; TYPE_2__* ci; TYPE_2__* base_ci; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_7__ {scalar_t__ top; } ;
typedef  scalar_t__ StkId ;
typedef  TYPE_2__ CallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  checkstacksizes (TYPE_1__*,scalar_t__) ; 
 scalar_t__ gt (TYPE_1__*) ; 
 int /*<<< orphan*/  markvalue (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setnilvalue (scalar_t__) ; 

__attribute__((used)) static void traversestack(global_State*g,lua_State*l){
StkId o,lim;
CallInfo*ci;
markvalue(g,gt(l));
lim=l->top;
for(ci=l->base_ci;ci<=l->ci;ci++){
if(lim<ci->top)lim=ci->top;
}
for(o=l->stack;o<l->top;o++)
markvalue(g,o);
for(;o<=lim;o++)
setnilvalue(o);
checkstacksizes(l,lim);
}