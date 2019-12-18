#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  gray; } ;
struct TYPE_24__ {TYPE_2__ gc; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_22__ {int gct; int /*<<< orphan*/  gclist; } ;
struct TYPE_26__ {TYPE_1__ gch; } ;
struct TYPE_25__ {scalar_t__ closed; } ;
struct TYPE_21__ {int /*<<< orphan*/  env; int /*<<< orphan*/  metatable; } ;
typedef  TYPE_4__ GCupval ;
typedef  int /*<<< orphan*/  GCtab ;
typedef  TYPE_5__ GCobj ;

/* Variables and functions */
 int LJ_TCDATA ; 
 int LJ_TFUNC ; 
 int LJ_TPROTO ; 
 int LJ_TSTR ; 
 int LJ_TTAB ; 
 int LJ_TTHREAD ; 
 int LJ_TTRACE ; 
 int LJ_TUDATA ; 
 int LJ_TUPVAL ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 int /*<<< orphan*/  gc_markobj (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_marktv (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_15__* gco2ud (TYPE_5__*) ; 
 TYPE_4__* gco2uv (TYPE_5__*) ; 
 int /*<<< orphan*/  gray2black (TYPE_5__*) ; 
 int /*<<< orphan*/  isdead (TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ iswhite (TYPE_5__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  setgcrefr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tabref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvval (TYPE_4__*) ; 
 int /*<<< orphan*/  white2gray (TYPE_5__*) ; 

__attribute__((used)) static void gc_mark(global_State *g, GCobj *o)
{
  int gct = o->gch.gct;
  lua_assert(iswhite(o) && !isdead(g, o));
  white2gray(o);
  if (LJ_UNLIKELY(gct == ~LJ_TUDATA)) {
    GCtab *mt = tabref(gco2ud(o)->metatable);
    gray2black(o);  /* Userdata are never gray. */
    if (mt) gc_markobj(g, mt);
    gc_markobj(g, tabref(gco2ud(o)->env));
  } else if (LJ_UNLIKELY(gct == ~LJ_TUPVAL)) {
    GCupval *uv = gco2uv(o);
    gc_marktv(g, uvval(uv));
    if (uv->closed)
      gray2black(o);  /* Closed upvalues are never gray. */
  } else if (gct != ~LJ_TSTR && gct != ~LJ_TCDATA) {
    lua_assert(gct == ~LJ_TFUNC || gct == ~LJ_TTAB ||
	       gct == ~LJ_TTHREAD || gct == ~LJ_TPROTO || gct == ~LJ_TTRACE);
    setgcrefr(o->gch.gclist, g->gc.gray);
    setgcref(g->gc.gray, o);
  }
}