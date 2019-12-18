#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct udev_monitor {int dummy; } ;
struct udev_device {int dummy; } ;
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_6__ {struct udev_monitor* monitor; } ;
typedef  TYPE_2__ services_discovery_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddDevice (TYPE_1__*,struct udev_device*) ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  RemoveDevice (TYPE_1__*,struct udev_device*) ; 
 scalar_t__ errno ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* udev_device_get_action (struct udev_device*) ; 
 int /*<<< orphan*/  udev_device_unref (struct udev_device*) ; 
 int udev_monitor_get_fd (struct udev_monitor*) ; 
 struct udev_device* udev_monitor_receive_device (struct udev_monitor*) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void *Run (void *data)
{
    services_discovery_t *sd = data;
    services_discovery_sys_t *p_sys = sd->p_sys;
    struct udev_monitor *mon = p_sys->monitor;

    int fd = udev_monitor_get_fd (mon);
    struct pollfd ufd = { .fd = fd, .events = POLLIN, };

    for (;;)
    {
        while (poll (&ufd, 1, -1) == -1)
            if (errno != EINTR)
                break;

        int canc = vlc_savecancel ();
        struct udev_device *dev = udev_monitor_receive_device (mon);
        if (dev == NULL)
            continue;

        const char *action = udev_device_get_action (dev);
        if (!strcmp (action, "add"))
            AddDevice (sd, dev);
        else if (!strcmp (action, "remove"))
            RemoveDevice (sd, dev);
        else if (!strcmp (action, "change"))
        {
            RemoveDevice (sd, dev);
            AddDevice (sd, dev);
        }
        udev_device_unref (dev);
        vlc_restorecancel (canc);
    }
    return NULL;
}