#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_5__* unit; int /*<<< orphan*/  bus_track; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_12__ {int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_CANCELED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_manage_units_async (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  job_finish_and_invalidate (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int mac_selinux_unit_access_check (TYPE_5__*,TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_message_get_sender (TYPE_1__*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_track_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bus_job_method_cancel(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Job *j = userdata;
        int r;

        assert(message);
        assert(j);

        r = mac_selinux_unit_access_check(j->unit, message, "stop", error);
        if (r < 0)
                return r;

        /* Access is granted to the job owner */
        if (!sd_bus_track_contains(j->bus_track, sd_bus_message_get_sender(message))) {

                /* And for everybody else consult polkit */
                r = bus_verify_manage_units_async(j->unit->manager, message, error);
                if (r < 0)
                        return r;
                if (r == 0)
                        return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */
        }

        job_finish_and_invalidate(j, JOB_CANCELED, true, false);

        return sd_bus_reply_method_return(message, NULL);
}