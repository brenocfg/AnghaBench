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
struct TYPE_5__ {int currentwhite; int /*<<< orphan*/  root; } ;
struct TYPE_6__ {size_t strmask; int /*<<< orphan*/ * strhash; TYPE_1__ gc; } ;
typedef  TYPE_2__ global_State ;
typedef  size_t MSize ;

/* Variables and functions */
 int LJ_GC_SFIXED ; 
 int LJ_GC_WHITES ; 
 int /*<<< orphan*/  gc_fullsweep (TYPE_2__*,int /*<<< orphan*/ *) ; 

void lj_gc_freeall(global_State *g)
{
  MSize i, strmask;
  /* Free everything, except super-fixed objects (the main thread). */
  g->gc.currentwhite = LJ_GC_WHITES | LJ_GC_SFIXED;
  gc_fullsweep(g, &g->gc.root);
  strmask = g->strmask;
  for (i = 0; i <= strmask; i++)  /* Free all string hash chains. */
    gc_fullsweep(g, &g->strhash[i]);
}