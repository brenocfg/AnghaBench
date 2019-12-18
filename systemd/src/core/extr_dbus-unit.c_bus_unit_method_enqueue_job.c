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
typedef  size_t JobType ;
typedef  scalar_t__ JobMode ;
typedef  int /*<<< orphan*/  BusUnitQueueFlags ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_UNIT_QUEUE_RELOAD_IF_POSSIBLE ; 
 int /*<<< orphan*/  BUS_UNIT_QUEUE_VERBOSE_REPLY ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t JOB_RESTART ; 
 size_t JOB_TRY_RESTART ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_unit_queue_job (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_verify_manage_units_async_full (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ job_mode_from_string (char const*) ; 
 size_t job_type_from_string (char const*) ; 
 int /*<<< orphan*/  job_type_to_access_method (size_t) ; 
 int mac_selinux_unit_access_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * polkit_message_for_job ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**,char const**) ; 
 scalar_t__ streq (char const*,char*) ; 

int bus_unit_method_enqueue_job(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        BusUnitQueueFlags flags = BUS_UNIT_QUEUE_VERBOSE_REPLY;
        const char *jtype, *smode;
        Unit *u = userdata;
        JobType type;
        JobMode mode;
        int r;

        assert(message);
        assert(u);

        r = sd_bus_message_read(message, "ss", &jtype, &smode);
        if (r < 0)
                return r;

        /* Parse the two magic reload types "reload-or-…" manually */
        if (streq(jtype, "reload-or-restart")) {
                type = JOB_RESTART;
                flags |= BUS_UNIT_QUEUE_RELOAD_IF_POSSIBLE;
        } else if (streq(jtype, "reload-or-try-restart")) {
                type = JOB_TRY_RESTART;
                flags |= BUS_UNIT_QUEUE_RELOAD_IF_POSSIBLE;
        } else {
                /* And the rest generically */
                type = job_type_from_string(jtype);
                if (type < 0)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Job type %s invalid", jtype);
        }

        mode = job_mode_from_string(smode);
        if (mode < 0)
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Job mode %s invalid", smode);

        r = mac_selinux_unit_access_check(
                        u, message,
                        job_type_to_access_method(type),
                        error);
        if (r < 0)
                return r;

        r = bus_verify_manage_units_async_full(
                        u,
                        jtype,
                        CAP_SYS_ADMIN,
                        polkit_message_for_job[type],
                        true,
                        message,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        return bus_unit_queue_job(message, u, type, mode, flags, error);
}