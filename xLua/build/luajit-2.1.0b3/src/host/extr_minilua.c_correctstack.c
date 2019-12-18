#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * stack; int /*<<< orphan*/ * base; TYPE_4__* ci; TYPE_4__* base_ci; TYPE_3__* openupval; int /*<<< orphan*/ * top; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_12__ {int /*<<< orphan*/ * v; } ;
struct TYPE_11__ {int /*<<< orphan*/ * func; int /*<<< orphan*/ * base; int /*<<< orphan*/ * top; } ;
struct TYPE_8__ {TYPE_3__* next; } ;
struct TYPE_10__ {TYPE_1__ gch; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_3__ GCObject ;
typedef  TYPE_4__ CallInfo ;

/* Variables and functions */
 TYPE_5__* gco2uv (TYPE_3__*) ; 

__attribute__((used)) static void correctstack(lua_State*L,TValue*oldstack){
CallInfo*ci;
GCObject*up;
L->top=(L->top-oldstack)+L->stack;
for(up=L->openupval;up!=NULL;up=up->gch.next)
gco2uv(up)->v=(gco2uv(up)->v-oldstack)+L->stack;
for(ci=L->base_ci;ci<=L->ci;ci++){
ci->top=(ci->top-oldstack)+L->stack;
ci->base=(ci->base-oldstack)+L->stack;
ci->func=(ci->func-oldstack)+L->stack;
}
L->base=(L->base-oldstack)+L->stack;
}