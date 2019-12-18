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
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  XA_WM_CLIENT_MACHINE ; 
 long _POSIX_HOST_NAME_MAX ; 
 int /*<<< orphan*/  _SC_HOST_NAME_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ gethostname (char*,long) ; 
 char* malloc (long) ; 
 int /*<<< orphan*/  set_ascii_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void set_hostname_prop (xcb_connection_t *conn, xcb_window_t window)
{
    char* hostname;
    long host_name_max = sysconf (_SC_HOST_NAME_MAX);
    if (host_name_max <= 0) host_name_max = _POSIX_HOST_NAME_MAX;
    hostname = malloc (host_name_max);
    if(!hostname) return;

    if (gethostname (hostname, host_name_max) == 0)
    {
        hostname[host_name_max - 1] = '\0';
        set_ascii_prop (conn, window, XA_WM_CLIENT_MACHINE, hostname);
    }
    free(hostname);
}