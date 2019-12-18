#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_5__ {scalar_t__ trace; scalar_t__ sizekgc; } ;
typedef  TYPE_1__ GCproto ;

/* Variables and functions */
 int /*<<< orphan*/  gc_mark_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_markobj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_marktrace (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  proto_chunkname (TYPE_1__*) ; 
 int /*<<< orphan*/  proto_kgc (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gc_traverse_proto(global_State *g, GCproto *pt)
{
  ptrdiff_t i;
  gc_mark_str(proto_chunkname(pt));
  for (i = -(ptrdiff_t)pt->sizekgc; i < 0; i++)  /* Mark collectable consts. */
    gc_markobj(g, proto_kgc(pt, i));
#if LJ_HASJIT
  if (pt->trace) gc_marktrace(g, pt->trace);
#endif
}