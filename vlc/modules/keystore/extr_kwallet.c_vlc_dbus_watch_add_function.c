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
struct TYPE_2__ {short events; int /*<<< orphan*/  fd; } ;
struct vlc_dbus_watch_data {int /*<<< orphan*/ * p_watch; TYPE_1__ pollfd; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusWatch ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 short POLLERR ; 
 short POLLHUP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dbus_watch_get_unix_fd (int /*<<< orphan*/ *) ; 
 struct vlc_dbus_watch_data* vlc_dbus_watch_get_data (int /*<<< orphan*/ *,void*) ; 
 short vlc_dbus_watch_get_poll_events (int /*<<< orphan*/ *) ; 

__attribute__((used)) static dbus_bool_t
vlc_dbus_watch_add_function( DBusWatch *p_watch, void *p_data )
{
    struct vlc_dbus_watch_data *p_ctx = vlc_dbus_watch_get_data( p_watch, p_data );

    if( p_ctx == NULL )
        return FALSE;

    short i_events = POLLHUP | POLLERR;

    i_events |= vlc_dbus_watch_get_poll_events( p_watch );

    p_ctx->pollfd.fd = dbus_watch_get_unix_fd( p_watch );
    p_ctx->pollfd.events = i_events;
    p_ctx->p_watch = p_watch;
    return TRUE;
}