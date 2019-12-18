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
struct TYPE_3__ {int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ sd_id128_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SD_BUS_TYPE_BYTE ; 
 TYPE_1__ SD_ID128_NULL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int sd_bus_message_read_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const**,size_t*) ; 

int bus_map_id128(sd_bus *bus, const char *member, sd_bus_message *m, sd_bus_error *error, void *userdata) {
        sd_id128_t *p = userdata;
        const void *v;
        size_t n;
        int r;

        r = sd_bus_message_read_array(m, SD_BUS_TYPE_BYTE, &v, &n);
        if (r < 0)
                return r;

        if (n == 0)
                *p = SD_ID128_NULL;
        else if (n == 16)
                memcpy((*p).bytes, v, n);
        else
                return -EINVAL;

        return 0;
}