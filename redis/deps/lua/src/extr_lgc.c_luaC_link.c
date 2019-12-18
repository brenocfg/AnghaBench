#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lu_byte ;
struct TYPE_8__ {TYPE_3__* rootgc; } ;
typedef  TYPE_2__ global_State ;
struct TYPE_7__ {int /*<<< orphan*/  tt; int /*<<< orphan*/  marked; TYPE_3__* next; } ;
struct TYPE_9__ {TYPE_1__ gch; } ;
typedef  TYPE_3__ GCObject ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaC_white (TYPE_2__*) ; 

void luaC_link (lua_State *L, GCObject *o, lu_byte tt) {
  global_State *g = G(L);
  o->gch.next = g->rootgc;
  g->rootgc = o;
  o->gch.marked = luaC_white(g);
  o->gch.tt = tt;
}