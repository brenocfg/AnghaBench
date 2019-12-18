#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ main_window; } ;
struct TYPE_3__ {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 TYPE_2__ CacheState ; 
 scalar_t__ XCB_WINDOW_NONE ; 
 int /*<<< orphan*/  display_early_cleanup () ; 
 TYPE_1__* xcb ; 
 int /*<<< orphan*/  xcb_unmap_window (int /*<<< orphan*/ ,scalar_t__) ; 

void rofi_view_hide ( void )
{
    if ( CacheState.main_window != XCB_WINDOW_NONE ) {
        xcb_unmap_window ( xcb->connection, CacheState.main_window );
        display_early_cleanup ();
    }
}