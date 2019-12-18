#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ repaint_source; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 TYPE_1__ CacheState ; 
 int /*<<< orphan*/  G_PRIORITY_HIGH_IDLE ; 
 scalar_t__ current_active_menu ; 
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_idle_add_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_view_repaint ; 

void rofi_view_queue_redraw ( void  )
{
    if ( current_active_menu && CacheState.repaint_source == 0 ) {
        CacheState.count++;
        g_debug ( "redraw %llu", CacheState.count );
        CacheState.repaint_source = g_idle_add_full (  G_PRIORITY_HIGH_IDLE, rofi_view_repaint, NULL, NULL );
    }
}