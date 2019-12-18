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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  Unit ;
typedef  scalar_t__ KillWho ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_KILL ; 
 scalar_t__ KILL_ALL ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SD_BUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  SIGNAL_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_verify_manage_units_async_full (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isempty (char const*) ; 
 scalar_t__ kill_who_from_string (char const*) ; 
 int mac_selinux_unit_access_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**,int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int unit_kill (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bus_unit_method_kill(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Unit *u = userdata;
        const char *swho;
        int32_t signo;
        KillWho who;
        int r;

        assert(message);
        assert(u);

        r = mac_selinux_unit_access_check(u, message, "stop", error);
        if (r < 0)
                return r;

        r = sd_bus_message_read(message, "si", &swho, &signo);
        if (r < 0)
                return r;

        if (isempty(swho))
                who = KILL_ALL;
        else {
                who = kill_who_from_string(swho);
                if (who < 0)
                        return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Invalid who argument %s", swho);
        }

        if (!SIGNAL_VALID(signo))
                return sd_bus_error_setf(error, SD_BUS_ERROR_INVALID_ARGS, "Signal number out of range.");

        r = bus_verify_manage_units_async_full(
                        u,
                        "kill",
                        CAP_KILL,
                        N_("Authentication is required to send a UNIX signal to the processes of '$(unit)'."),
                        true,
                        message,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        r = unit_kill(u, who, signo, error);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, NULL);
}