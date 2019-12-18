#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_3__ {scalar_t__ trace; } ;
typedef  TYPE_1__ GCproto ;

/* Variables and functions */
 int /*<<< orphan*/  G2J (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_flushroot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traceref (int /*<<< orphan*/ ,scalar_t__) ; 

void lj_trace_flushproto(global_State *g, GCproto *pt)
{
  while (pt->trace != 0)
    trace_flushroot(G2J(g), traceref(G2J(g), pt->trace));
}