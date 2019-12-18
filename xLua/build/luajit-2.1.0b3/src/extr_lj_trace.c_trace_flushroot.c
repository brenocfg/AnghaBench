#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jit_State ;
struct TYPE_8__ {scalar_t__ trace; } ;
struct TYPE_9__ {TYPE_2__ pt; } ;
struct TYPE_7__ {scalar_t__ root; scalar_t__ traceno; scalar_t__ nextroot; int /*<<< orphan*/  startpt; } ;
typedef  TYPE_1__ GCtrace ;
typedef  TYPE_2__ GCproto ;

/* Variables and functions */
 TYPE_6__* gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  trace_unpatch (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* traceref (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void trace_flushroot(jit_State *J, GCtrace *T)
{
  GCproto *pt = &gcref(T->startpt)->pt;
  lua_assert(T->root == 0 && pt != NULL);
  /* First unpatch any modified bytecode. */
  trace_unpatch(J, T);
  /* Unlink root trace from chain anchored in prototype. */
  if (pt->trace == T->traceno) {  /* Trace is first in chain. Easy. */
    pt->trace = T->nextroot;
  } else if (pt->trace) {  /* Otherwise search in chain of root traces. */
    GCtrace *T2 = traceref(J, pt->trace);
    if (T2) {
      for (; T2->nextroot; T2 = traceref(J, T2->nextroot))
	if (T2->nextroot == T->traceno) {
	  T2->nextroot = T->nextroot;  /* Unlink from chain. */
	  break;
	}
    }
  }
}