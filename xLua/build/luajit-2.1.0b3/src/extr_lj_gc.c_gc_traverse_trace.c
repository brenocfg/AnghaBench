#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_6__ {scalar_t__ traceno; size_t nk; int /*<<< orphan*/  startpt; scalar_t__ nextside; scalar_t__ nextroot; scalar_t__ link; TYPE_1__* ir; } ;
struct TYPE_5__ {scalar_t__ o; int /*<<< orphan*/  t; } ;
typedef  size_t IRRef ;
typedef  TYPE_1__ IRIns ;
typedef  TYPE_2__ GCtrace ;

/* Variables and functions */
 scalar_t__ IR_KGC ; 
 scalar_t__ IR_KNULL ; 
 size_t REF_TRUE ; 
 int /*<<< orphan*/  gc_markobj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_marktrace (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_kgc (TYPE_1__*) ; 
 scalar_t__ irt_is64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_traverse_trace(global_State *g, GCtrace *T)
{
  IRRef ref;
  if (T->traceno == 0) return;
  for (ref = T->nk; ref < REF_TRUE; ref++) {
    IRIns *ir = &T->ir[ref];
    if (ir->o == IR_KGC)
      gc_markobj(g, ir_kgc(ir));
    if (irt_is64(ir->t) && ir->o != IR_KNULL)
      ref++;
  }
  if (T->link) gc_marktrace(g, T->link);
  if (T->nextroot) gc_marktrace(g, T->nextroot);
  if (T->nextside) gc_marktrace(g, T->nextside);
  gc_markobj(g, gcref(T->startpt));
}