#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BUS_TYPE_STRING ; 
 char SD_BUS_TYPE_STRUCT ; 
 int bus_log_create_error (int) ; 
 int sd_bus_message_append_array (int /*<<< orphan*/ *,char,void const*,size_t) ; 
 int sd_bus_message_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int sd_bus_message_close_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_open_container (int /*<<< orphan*/ *,char,char*) ; 

__attribute__((used)) static int bus_append_byte_array(sd_bus_message *m, const char *field, const void *buf, size_t n) {
        int r;

        r = sd_bus_message_open_container(m, SD_BUS_TYPE_STRUCT, "sv");
        if (r < 0)
                return bus_log_create_error(r);

        r = sd_bus_message_append_basic(m, SD_BUS_TYPE_STRING, field);
        if (r < 0)
                return bus_log_create_error(r);

        r = sd_bus_message_open_container(m, 'v', "ay");
        if (r < 0)
                return bus_log_create_error(r);

        r = sd_bus_message_append_array(m, 'y', buf, n);
        if (r < 0)
                return bus_log_create_error(r);

        r = sd_bus_message_close_container(m);
        if (r < 0)
                return bus_log_create_error(r);

        r = sd_bus_message_close_container(m);
        if (r < 0)
                return bus_log_create_error(r);

        return 1;
}