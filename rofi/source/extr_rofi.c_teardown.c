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

/* Variables and functions */
 int /*<<< orphan*/  display_early_cleanup () ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  remove_pid_file (int) ; 
 int /*<<< orphan*/  rofi_view_cleanup () ; 
 int /*<<< orphan*/  textbox_cleanup () ; 

__attribute__((used)) static void teardown ( int pfd )
{
    g_debug ( "Teardown" );
    // Cleanup font setup.
    textbox_cleanup ( );

    display_early_cleanup ();

    // Cleanup view
    rofi_view_cleanup ();
    // Cleanup pid file.
    remove_pid_file ( pfd );
}