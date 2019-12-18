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
struct udev {int dummy; } ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_5__ {int /*<<< orphan*/  root; int /*<<< orphan*/ * monitor; int /*<<< orphan*/  thread; } ;
typedef  TYPE_2__ services_discovery_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyDevice ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  tdestroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct udev* udev_monitor_get_udev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udev_monitor_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udev_unref (struct udev*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close (vlc_object_t *obj)
{
    services_discovery_t *sd = (services_discovery_t *)obj;
    services_discovery_sys_t *p_sys = sd->p_sys;

    if (p_sys->monitor != NULL)
    {
        struct udev *udev = udev_monitor_get_udev (p_sys->monitor);

        vlc_cancel (p_sys->thread);
        vlc_join (p_sys->thread, NULL);
        udev_monitor_unref (p_sys->monitor);
        udev_unref (udev);
    }

    tdestroy (p_sys->root, DestroyDevice);
    free (p_sys);
}