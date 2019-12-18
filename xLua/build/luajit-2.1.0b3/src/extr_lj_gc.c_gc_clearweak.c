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
struct TYPE_7__ {int marked; scalar_t__ asize; scalar_t__ hmask; int /*<<< orphan*/  gclist; int /*<<< orphan*/  node; } ;
struct TYPE_6__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ Node ;
typedef  scalar_t__ MSize ;
typedef  TYPE_2__ GCtab ;
typedef  int /*<<< orphan*/  GCobj ;

/* Variables and functions */
 int LJ_GC_WEAK ; 
 int LJ_GC_WEAKVAL ; 
 int /*<<< orphan*/ * arrayslot (TYPE_2__*,scalar_t__) ; 
 scalar_t__ gc_mayclear (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* gco2tab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 TYPE_1__* noderef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setnilV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gc_clearweak(GCobj *o)
{
  while (o) {
    GCtab *t = gco2tab(o);
    lua_assert((t->marked & LJ_GC_WEAK));
    if ((t->marked & LJ_GC_WEAKVAL)) {
      MSize i, asize = t->asize;
      for (i = 0; i < asize; i++) {
	/* Clear array slot when value is about to be collected. */
	TValue *tv = arrayslot(t, i);
	if (gc_mayclear(tv, 1))
	  setnilV(tv);
      }
    }
    if (t->hmask > 0) {
      Node *node = noderef(t->node);
      MSize i, hmask = t->hmask;
      for (i = 0; i <= hmask; i++) {
	Node *n = &node[i];
	/* Clear hash slot when key or value is about to be collected. */
	if (!tvisnil(&n->val) && (gc_mayclear(&n->key, 0) ||
				  gc_mayclear(&n->val, 1)))
	  setnilV(&n->val);
      }
    }
    o = gcref(t->gclist);
  }
}