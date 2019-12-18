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
struct vlc_dbus_watch_data {int /*<<< orphan*/ * p_watch; } ;
typedef  int /*<<< orphan*/  DBusWatch ;

/* Variables and functions */
 unsigned int MAX_WATCHES ; 

__attribute__((used)) static struct vlc_dbus_watch_data *
vlc_dbus_watch_get_data( DBusWatch *p_watch,
                         struct vlc_dbus_watch_data *p_ctx )
{
    for( unsigned i = 0; i < MAX_WATCHES; ++i )
    {
        if( p_ctx[i].p_watch == NULL || p_ctx[i].p_watch == p_watch )
            return &p_ctx[i];
    }
    return NULL;
}