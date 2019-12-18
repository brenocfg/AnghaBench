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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
struct TYPE_3__ {int /*<<< orphan*/  job_id; } ;
typedef  TYPE_1__ WaitForItem ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int property_map_job(
                sd_bus *bus,
                const char *member,
                sd_bus_message *m,
                sd_bus_error *error,
                void *userdata) {

        WaitForItem *item = userdata;
        const char *path;
        uint32_t id;
        int r;

        assert(item);

        r = sd_bus_message_read(m, "(uo)", &id, &path);
        if (r < 0)
                return r;

        item->job_id = id;
        return 0;
}