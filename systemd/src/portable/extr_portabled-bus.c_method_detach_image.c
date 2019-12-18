#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  PortableChange ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  PORTABLE_RUNTIME ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_polkit_async (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portable_changes_free (int /*<<< orphan*/ *,size_t) ; 
 int portable_detach (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 int reply_portable_changes (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**,int*) ; 

__attribute__((used)) static int method_detach_image(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        PortableChange *changes = NULL;
        Manager *m = userdata;
        size_t n_changes = 0;
        const char *name_or_path;
        int r, runtime;

        assert(message);
        assert(m);

        /* Note that we do not redirect detaching to the image object here, because we want to allow that users can
         * detach already deleted images too, in case the user already deleted an image before properly detaching
         * it. */

        r = sd_bus_message_read(message, "sb", &name_or_path, &runtime);
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
                        name_or_path,
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