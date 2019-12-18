#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * stack; TYPE_6__* ci; TYPE_5__* openupval; int /*<<< orphan*/ * top; } ;
typedef  TYPE_4__ lua_State ;
struct TYPE_17__ {int /*<<< orphan*/ * v; } ;
struct TYPE_12__ {int /*<<< orphan*/ * base; } ;
struct TYPE_13__ {TYPE_2__ l; } ;
struct TYPE_16__ {TYPE_3__ u; int /*<<< orphan*/ * func; int /*<<< orphan*/ * top; struct TYPE_16__* previous; } ;
struct TYPE_11__ {TYPE_5__* next; } ;
struct TYPE_15__ {TYPE_1__ gch; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_5__ GCObject ;
typedef  TYPE_6__ CallInfo ;

/* Variables and functions */
 TYPE_8__* gco2uv (TYPE_5__*) ; 
 scalar_t__ isLua (TYPE_6__*) ; 

__attribute__((used)) static void correctstack (lua_State *L, TValue *oldstack) {
  CallInfo *ci;
  GCObject *up;
  L->top = (L->top - oldstack) + L->stack;
  for (up = L->openupval; up != NULL; up = up->gch.next)
    gco2uv(up)->v = (gco2uv(up)->v - oldstack) + L->stack;
  for (ci = L->ci; ci != NULL; ci = ci->previous) {
    ci->top = (ci->top - oldstack) + L->stack;
    ci->func = (ci->func - oldstack) + L->stack;
    if (isLua(ci))
      ci->u.l.base = (ci->u.l.base - oldstack) + L->stack;
  }
}