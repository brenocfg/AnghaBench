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
typedef  int /*<<< orphan*/  DBusPendingCall ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/ * dbus_pending_call_steal_reply (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vlc_dbus_pending_call_notify( DBusPendingCall *p_pending_call, void *p_data )
{
    DBusMessage **pp_repmsg = p_data;
    *pp_repmsg = dbus_pending_call_steal_reply( p_pending_call );
}