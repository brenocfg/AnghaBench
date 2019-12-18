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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_5__ {TYPE_1__* userdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ Manager ;
typedef  TYPE_2__ Image ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_verify_polkit_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int image_read_only (TYPE_2__*,int) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int*) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bus_image_method_mark_read_only(
                sd_bus_message *message,
                void *userdata,
                sd_bus_error *error) {

        Image *image = userdata;
        Manager *m = image->userdata;
        int r, read_only;

        assert(message);

        r = sd_bus_message_read(message, "b", &read_only);
        if (r < 0)
                return r;

        r = bus_verify_polkit_async(
                        message,
                        CAP_SYS_ADMIN,
                        "org.freedesktop.machine1.manage-images",
                        NULL,
                        false,
                        UID_INVALID,
                        &m->polkit_registry,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* Will call us back */

        r = image_read_only(image, read_only);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, NULL);
}