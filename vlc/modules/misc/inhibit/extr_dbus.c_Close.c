#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_inhibit_t ;
struct TYPE_5__ {int /*<<< orphan*/  conn; int /*<<< orphan*/ * pending; } ;
typedef  TYPE_2__ vlc_inhibit_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_connection_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_connection_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbus_pending_call_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_pending_call_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void Close (vlc_object_t *obj)
{
    vlc_inhibit_t *ih = (vlc_inhibit_t *)obj;
    vlc_inhibit_sys_t *sys = ih->p_sys;

    if (sys->pending != NULL)
    {
        dbus_pending_call_cancel(sys->pending);
        dbus_pending_call_unref(sys->pending);
    }
    dbus_connection_close (sys->conn);
    dbus_connection_unref (sys->conn);
    free (sys);
}