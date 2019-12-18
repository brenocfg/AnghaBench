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
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ GCproto ;

/* Variables and functions */
 int LUAJIT_MODE_FLUSH ; 
 int LUAJIT_MODE_ON ; 
 int /*<<< orphan*/  PROTO_NOJIT ; 
 int /*<<< orphan*/  lj_trace_flushproto (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lj_trace_reenableproto (TYPE_1__*) ; 

__attribute__((used)) static void setptmode(global_State *g, GCproto *pt, int mode)
{
  if ((mode & LUAJIT_MODE_ON)) {  /* (Re-)enable JIT compilation. */
    pt->flags &= ~PROTO_NOJIT;
    lj_trace_reenableproto(pt);  /* Unpatch all ILOOP etc. bytecodes. */
  } else {  /* Flush and/or disable JIT compilation. */
    if (!(mode & LUAJIT_MODE_FLUSH))
      pt->flags |= PROTO_NOJIT;
    lj_trace_flushproto(g, pt);  /* Flush all traces of prototype. */
  }
}