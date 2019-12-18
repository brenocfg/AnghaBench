#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  show_status; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHOW_STATUS_TEMPORARY ; 
 int /*<<< orphan*/  SHOW_STATUS_YES ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_message_append_basic (TYPE_1__*,char,int*) ; 

__attribute__((used)) static int property_get_show_status(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Manager *m = userdata;
        int b;

        assert(bus);
        assert(reply);
        assert(m);

        b = IN_SET(m->show_status, SHOW_STATUS_TEMPORARY, SHOW_STATUS_YES);
        return sd_bus_message_append_basic(reply, 'b', &b);
}