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
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ) ; 

void remove_pid_file ( int fd )
{
    if ( fd >= 0 ) {
        if ( close ( fd ) ) {
            g_warning ( "Failed to close pidfile: '%s'", g_strerror ( errno ) );
        }
    }
}