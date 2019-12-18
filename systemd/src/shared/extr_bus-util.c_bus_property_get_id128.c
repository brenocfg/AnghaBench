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
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int sd_bus_message_append_array (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sd_id128_is_null (TYPE_1__) ; 

int bus_property_get_id128(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        sd_id128_t *id = userdata;

        if (sd_id128_is_null(*id)) /* Add an empty array if the ID is zero */
                return sd_bus_message_append(reply, "ay", 0);
        else
                return sd_bus_message_append_array(reply, 'y', id->bytes, 16);
}