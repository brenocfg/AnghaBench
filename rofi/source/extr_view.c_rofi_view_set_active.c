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
struct TYPE_2__ {int /*<<< orphan*/  views; } ;
typedef  int /*<<< orphan*/  RofiViewState ;

/* Variables and functions */
 TYPE_1__ CacheState ; 
 int /*<<< orphan*/ * current_active_menu ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  g_queue_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_queue_pop_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_queue_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_view_queue_redraw () ; 
 int /*<<< orphan*/  rofi_view_window_update_size (int /*<<< orphan*/ *) ; 

void rofi_view_set_active ( RofiViewState *state )
{
    if ( current_active_menu != NULL && state != NULL ) {
        g_queue_push_head ( &( CacheState.views ), current_active_menu );
        // TODO check.
        current_active_menu = state;
        g_debug ( "stack view." );
        rofi_view_window_update_size ( current_active_menu );
        rofi_view_queue_redraw ();
        return;
    }
    else if ( state == NULL && !g_queue_is_empty ( &( CacheState.views ) ) ) {
        g_debug ( "pop view." );
        current_active_menu = g_queue_pop_head ( &( CacheState.views ) );
        rofi_view_window_update_size ( current_active_menu );
        rofi_view_queue_redraw ();
        return;
    }
    g_assert ( ( current_active_menu == NULL && state != NULL ) || ( current_active_menu != NULL && state == NULL ) );
    current_active_menu = state;
    rofi_view_queue_redraw ();
}