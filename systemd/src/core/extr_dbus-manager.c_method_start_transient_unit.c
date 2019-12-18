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
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  Manager ;
typedef  scalar_t__ JobMode ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_START ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_unit_queue_job (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_verify_manage_units_async (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ job_mode_from_string (char const*) ; 
 int mac_selinux_access_check (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**,char const**) ; 
 int transient_aux_units_from_message (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int transient_unit_from_message (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_start_transient_unit(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        const char *name, *smode;
        Manager *m = userdata;
        JobMode mode;
        Unit *u;
        int r;

        assert(message);
        assert(m);

        r = mac_selinux_access_check(message, "start", error);
        if (r < 0)
                return r;

        r = sd_bus_message_read(message, "ss", &name, &smode);
        if (r < 0)
                return r;

        mode = job_mode_from_string(smode);
        if (mode < 0)
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Job mode %s is invalid.", smode);

        r = bus_verify_manage_units_async(m, message, error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        r = transient_unit_from_message(m, message, name, &u, error);
        if (r < 0)
                return r;

        r = transient_aux_units_from_message(m, message, error);
        if (r < 0)
                return r;

        /* Finally, start it */
        return bus_unit_queue_job(message, u, JOB_START, mode, 0, error);
}