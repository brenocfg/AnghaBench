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

/* Variables and functions */
 int /*<<< orphan*/  BUS_UNIT_QUEUE_RELOAD_IF_POSSIBLE ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 size_t _JOB_TYPE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int bus_unit_queue_job (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_verify_manage_units_async_full (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ job_mode_from_string (char const*) ; 
 int /*<<< orphan*/  job_type_to_access_method (size_t) ; 
 char* job_type_to_string (size_t) ; 
 int mac_selinux_unit_access_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * polkit_message_for_job ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 
 char* strjoina (char*,char*) ; 

int bus_unit_method_start_generic(
                sd_bus_message *message,
                Unit *u,
                JobType job_type,
                bool reload_if_possible,
                sd_bus_error *error) {

        const char *smode, *verb;
        JobMode mode;
        int r;

        assert(message);
        assert(u);
        assert(job_type >= 0 && job_type < _JOB_TYPE_MAX);

        r = mac_selinux_unit_access_check(
                        u, message,
                        job_type_to_access_method(job_type),
                        error);
        if (r < 0)
                return r;

        r = sd_bus_message_read(message, "s", &smode);
        if (r < 0)
                return r;

        mode = job_mode_from_string(smode);
        if (mode < 0)
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Job mode %s invalid", smode);

        if (reload_if_possible)
                verb = strjoina("reload-or-", job_type_to_string(job_type));
        else
                verb = job_type_to_string(job_type);

        r = bus_verify_manage_units_async_full(
                        u,
                        verb,
                        CAP_SYS_ADMIN,
                        polkit_message_for_job[job_type],
                        true,
                        message,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        return bus_unit_queue_job(message, u, job_type, mode,
                                  reload_if_possible ? BUS_UNIT_QUEUE_RELOAD_IF_POSSIBLE : 0, error);
}