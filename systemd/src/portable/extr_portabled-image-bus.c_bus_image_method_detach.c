#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  path; int /*<<< orphan*/  polkit_registry; struct TYPE_10__* userdata; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  PortableChange ;
typedef  TYPE_1__ Manager ;
typedef  TYPE_1__ Image ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  PORTABLE_RUNTIME ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_polkit_async (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portable_changes_free (int /*<<< orphan*/ *,size_t) ; 
 int portable_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 int reply_portable_changes (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,int*) ; 

__attribute__((used)) static int bus_image_method_detach(
                sd_bus_message *message,
                void *userdata,
                sd_bus_error *error) {

        PortableChange *changes = NULL;
        Image *image = userdata;
        Manager *m = image->userdata;
        size_t n_changes = 0;
        int r, runtime;

        assert(message);
        assert(image);
        assert(m);

        r = sd_bus_message_read(message, "b", &runtime);
        if (r < 0)
                return r;

        r = bus_verify_polkit_async(
                        message,
                        CAP_SYS_ADMIN,
                        "org.freedesktop.portable1.attach-images",
                        NULL,
                        false,
                        UID_INVALID,
                        &m->polkit_registry,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* Will call us back */

        r = portable_detach(
                        sd_bus_message_get_bus(message),
                        image->path,
                        runtime ? PORTABLE_RUNTIME : 0,
                        &changes,
                        &n_changes,
                        error);
        if (r < 0)
                goto finish;

        r = reply_portable_changes(message, changes, n_changes);

finish:
        portable_changes_free(changes, n_changes);
        return r;
}