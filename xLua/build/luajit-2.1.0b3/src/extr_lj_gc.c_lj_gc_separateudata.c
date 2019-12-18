#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  mmudata; } ;
struct TYPE_19__ {TYPE_2__ gc; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_22__ {int /*<<< orphan*/  nextgc; } ;
struct TYPE_21__ {int /*<<< orphan*/  metatable; } ;
struct TYPE_17__ {int /*<<< orphan*/  nextgc; } ;
struct TYPE_20__ {TYPE_1__ gch; } ;
typedef  TYPE_4__ GCobj ;
typedef  int /*<<< orphan*/  GCRef ;

/* Variables and functions */
 int /*<<< orphan*/  MM_gc ; 
 TYPE_5__* gco2ud (TYPE_4__*) ; 
 TYPE_4__* gcref (int /*<<< orphan*/ ) ; 
 scalar_t__ isfinalized (TYPE_5__*) ; 
 scalar_t__ iswhite (TYPE_4__*) ; 
 int /*<<< orphan*/  lj_meta_fastg (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* mainthread (TYPE_3__*) ; 
 int /*<<< orphan*/  markfinalized (TYPE_4__*) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  setgcrefr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sizeudata (TYPE_5__*) ; 
 int /*<<< orphan*/  tabref (int /*<<< orphan*/ ) ; 

size_t lj_gc_separateudata(global_State *g, int all)
{
  size_t m = 0;
  GCRef *p = &mainthread(g)->nextgc;
  GCobj *o;
  while ((o = gcref(*p)) != NULL) {
    if (!(iswhite(o) || all) || isfinalized(gco2ud(o))) {
      p = &o->gch.nextgc;  /* Nothing to do. */
    } else if (!lj_meta_fastg(g, tabref(gco2ud(o)->metatable), MM_gc)) {
      markfinalized(o);  /* Done, as there's no __gc metamethod. */
      p = &o->gch.nextgc;
    } else {  /* Otherwise move userdata to be finalized to mmudata list. */
      m += sizeudata(gco2ud(o));
      markfinalized(o);
      *p = o->gch.nextgc;
      if (gcref(g->gc.mmudata)) {  /* Link to end of mmudata list. */
	GCobj *root = gcref(g->gc.mmudata);
	setgcrefr(o->gch.nextgc, root->gch.nextgc);
	setgcref(root->gch.nextgc, o);
	setgcref(g->gc.mmudata, o);
      } else {  /* Create circular list. */
	setgcref(o->gch.nextgc, o);
	setgcref(g->gc.mmudata, o);
      }
    }
  }
  return m;
}