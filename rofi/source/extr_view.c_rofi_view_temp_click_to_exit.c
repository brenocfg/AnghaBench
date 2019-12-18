#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xcb_window_t ;
struct TYPE_5__ {int flags; scalar_t__ main_window; } ;
struct TYPE_4__ {int /*<<< orphan*/  retv; int /*<<< orphan*/  quit; } ;
typedef  TYPE_1__ RofiViewState ;

/* Variables and functions */
 TYPE_3__ CacheState ; 
 int /*<<< orphan*/  MENU_CANCEL ; 
 int MENU_NORMAL_WINDOW ; 
 int /*<<< orphan*/  TRUE ; 

void rofi_view_temp_click_to_exit ( RofiViewState *state, xcb_window_t target )
{
    if ( ( CacheState.flags & MENU_NORMAL_WINDOW ) == 0 ) {
        if ( target != CacheState.main_window ) {
            state->quit = TRUE;
            state->retv = MENU_CANCEL;
        }
    }
}