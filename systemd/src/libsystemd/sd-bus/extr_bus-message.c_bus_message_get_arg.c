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
typedef  char const* sd_bus_message ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IN_SET (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_BUS_TYPE_OBJECT_PATH ; 
 int /*<<< orphan*/  SD_BUS_TYPE_SIGNATURE ; 
 int /*<<< orphan*/  SD_BUS_TYPE_STRING ; 
 int /*<<< orphan*/  assert (char const**) ; 
 int bus_message_get_arg_skip (char const**,unsigned int,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_message_read_basic (char const**,char,char const**) ; 

int bus_message_get_arg(sd_bus_message *m, unsigned i, const char **str) {
        char type;
        int r;

        assert(m);
        assert(str);

        r = bus_message_get_arg_skip(m, i, &type, NULL);
        if (r < 0)
                return r;

        if (!IN_SET(type, SD_BUS_TYPE_STRING, SD_BUS_TYPE_OBJECT_PATH, SD_BUS_TYPE_SIGNATURE))
                return -ENXIO;

        return sd_bus_message_read_basic(m, type, str);
}