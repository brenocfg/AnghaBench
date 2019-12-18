#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_3__ {int /*<<< orphan*/  hostname; int /*<<< orphan*/  metadata_valid; } ;
typedef  TYPE_1__ Image ;

/* Variables and functions */
 int image_read_metadata (TYPE_1__*) ; 
 int sd_bus_error_set_errnof (int /*<<< orphan*/ *,int,char*) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int bus_image_method_get_hostname(
                sd_bus_message *message,
                void *userdata,
                sd_bus_error *error) {

        Image *image = userdata;
        int r;

        if (!image->metadata_valid) {
                r = image_read_metadata(image);
                if (r < 0)
                        return sd_bus_error_set_errnof(error, r, "Failed to read image metadata: %m");
        }

        return sd_bus_reply_method_return(message, "s", image->hostname);
}