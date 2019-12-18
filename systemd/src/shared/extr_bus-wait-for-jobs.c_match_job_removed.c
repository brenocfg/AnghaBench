#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  result; int /*<<< orphan*/  jobs; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ BusWaitForJobs ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_log_parse_error (int) ; 
 int /*<<< orphan*/  empty_to_null (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_and_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sd_bus_message_read (TYPE_1__*,char*,int /*<<< orphan*/ *,char const**,char const**,char const**) ; 
 char* set_remove (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int match_job_removed(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        const char *path, *unit, *result;
        BusWaitForJobs *d = userdata;
        uint32_t id;
        char *found;
        int r;

        assert(m);
        assert(d);

        r = sd_bus_message_read(m, "uoss", &id, &path, &unit, &result);
        if (r < 0) {
                bus_log_parse_error(r);
                return 0;
        }

        found = set_remove(d->jobs, (char*) path);
        if (!found)
                return 0;

        free(found);

        (void) free_and_strdup(&d->result, empty_to_null(result));

        (void) free_and_strdup(&d->name, empty_to_null(unit));

        return 0;
}