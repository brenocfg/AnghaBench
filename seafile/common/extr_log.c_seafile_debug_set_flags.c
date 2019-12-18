#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SeafileDebugFlags ;

/* Variables and functions */
 int /*<<< orphan*/  debug_flags ; 
 int /*<<< orphan*/  g_message (char*,int /*<<< orphan*/ ) ; 

void
seafile_debug_set_flags (SeafileDebugFlags flags)
{
    g_message ("Set debug flags %#x\n", flags);
    debug_flags |= flags;
}