#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  gray; } ;
struct TYPE_17__ {TYPE_3__ gc; } ;
typedef  TYPE_4__ global_State ;
typedef  scalar_t__ TraceNo ;
struct TYPE_14__ {scalar_t__ traceno; } ;
struct TYPE_19__ {TYPE_1__ cur; } ;
struct TYPE_15__ {int /*<<< orphan*/  gclist; } ;
struct TYPE_18__ {TYPE_2__ gch; } ;
typedef  TYPE_5__ GCobj ;

/* Variables and functions */
 TYPE_7__* G2J (TYPE_4__*) ; 
 scalar_t__ iswhite (TYPE_5__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 TYPE_5__* obj2gco (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  setgcrefr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traceref (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  white2gray (TYPE_5__*) ; 

__attribute__((used)) static void gc_marktrace(global_State *g, TraceNo traceno)
{
  GCobj *o = obj2gco(traceref(G2J(g), traceno));
  lua_assert(traceno != G2J(g)->cur.traceno);
  if (iswhite(o)) {
    white2gray(o);
    setgcrefr(o->gch.gclist, g->gc.gray);
    setgcref(g->gc.gray, o);
  }
}