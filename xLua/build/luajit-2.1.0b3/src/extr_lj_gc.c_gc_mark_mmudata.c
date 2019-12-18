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
struct TYPE_6__ {int /*<<< orphan*/  mmudata; } ;
struct TYPE_7__ {TYPE_1__ gc; } ;
typedef  TYPE_2__ global_State ;
typedef  int /*<<< orphan*/  GCobj ;

/* Variables and functions */
 int /*<<< orphan*/  gc_mark (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gcnext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gcref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makewhite (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gc_mark_mmudata(global_State *g)
{
  GCobj *root = gcref(g->gc.mmudata);
  GCobj *u = root;
  if (u) {
    do {
      u = gcnext(u);
      makewhite(g, u);  /* Could be from previous GC. */
      gc_mark(g, u);
    } while (u != root);
  }
}