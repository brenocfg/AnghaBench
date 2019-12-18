#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct TYPE_12__* node; int /*<<< orphan*/  dev; TYPE_2__* session; TYPE_1__* device; int /*<<< orphan*/  fd; scalar_t__ pushed_fd; } ;
struct TYPE_11__ {int /*<<< orphan*/  devices; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int /*<<< orphan*/  session_devices; } ;
typedef  TYPE_3__ SessionDevice ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  SESSION_DEVICE_RELEASE ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_by_device ; 
 int /*<<< orphan*/  sd_notifyf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_device_notify (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_device_stop (TYPE_3__*) ; 

void session_device_free(SessionDevice *sd) {
        assert(sd);

        /* Make sure to remove the pushed fd. */
        if (sd->pushed_fd)
                (void) sd_notifyf(false,
                                  "FDSTOREREMOVE=1\n"
                                  "FDNAME=session-%s-device-%u-%u",
                                  sd->session->id, major(sd->dev), minor(sd->dev));

        session_device_stop(sd);
        session_device_notify(sd, SESSION_DEVICE_RELEASE);
        safe_close(sd->fd);

        LIST_REMOVE(sd_by_device, sd->device->session_devices, sd);

        hashmap_remove(sd->session->devices, &sd->dev);

        free(sd->node);
        free(sd);
}