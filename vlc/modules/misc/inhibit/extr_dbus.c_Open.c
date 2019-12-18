#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_11__ {int /*<<< orphan*/  inhibit; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_inhibit_t ;
struct TYPE_12__ {unsigned int api; int /*<<< orphan*/ * conn; scalar_t__ cookie; int /*<<< orphan*/ * pending; } ;
typedef  TYPE_2__ vlc_inhibit_sys_t ;
struct TYPE_13__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_3__ DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBUS_BUS_SESSION ; 
 int /*<<< orphan*/  Inhibit ; 
 unsigned int MAX_API ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * dbus_bus_get_private (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ dbus_bus_name_has_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_error_free (TYPE_3__*) ; 
 int /*<<< orphan*/  dbus_error_init (TYPE_3__*) ; 
 int /*<<< orphan*/ * dbus_service ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Open (vlc_object_t *obj)
{
    vlc_inhibit_t *ih = (vlc_inhibit_t *)obj;
    vlc_inhibit_sys_t *sys = malloc (sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    DBusError err;
    dbus_error_init(&err);

    sys->conn = dbus_bus_get_private (DBUS_BUS_SESSION, &err);
    if (sys->conn == NULL)
    {
        msg_Err(ih, "cannot connect to session bus: %s", err.message);
        dbus_error_free(&err);
        free(sys);
        return VLC_EGENERIC;
    }

    sys->pending = NULL;
    sys->cookie = 0;
    ih->p_sys = sys;

    for (unsigned i = 0; i < MAX_API; i++)
    {
        if (dbus_bus_name_has_owner(sys->conn, dbus_service[i], NULL))
        {
            msg_Dbg(ih, "found service %s", dbus_service[i]);
            sys->api = i;
            ih->inhibit = Inhibit;
            return VLC_SUCCESS;
        }

        msg_Dbg(ih, "cannot find service %s", dbus_service[i]);
    }

    Close(obj);
    return VLC_EGENERIC;
}