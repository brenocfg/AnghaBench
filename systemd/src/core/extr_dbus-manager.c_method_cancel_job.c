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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Manager ;
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_NO_SUCH_JOB ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_job_method_cancel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * manager_get_job (int /*<<< orphan*/ *,scalar_t__) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,scalar_t__*) ; 

__attribute__((used)) static int method_cancel_job(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        uint32_t id;
        Job *j;
        int r;

        assert(message);
        assert(m);

        r = sd_bus_message_read(message, "u", &id);
        if (r < 0)
                return r;

        j = manager_get_job(m, id);
        if (!j)
                return sd_bus_error_setf(error, BUS_ERROR_NO_SUCH_JOB, "Job %u does not exist.", (unsigned) id);

        return bus_job_method_cancel(message, j, error);
}