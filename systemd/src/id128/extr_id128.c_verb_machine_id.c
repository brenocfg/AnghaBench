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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int /*<<< orphan*/  arg_app ; 
 int /*<<< orphan*/  arg_pretty ; 
 int id128_pretty_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*,char*) ; 
 int sd_id128_get_machine (int /*<<< orphan*/ *) ; 
 int sd_id128_get_machine_app_specific (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sd_id128_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verb_machine_id(int argc, char **argv, void *userdata) {
        sd_id128_t id;
        int r;

        if (sd_id128_is_null(arg_app))
                r = sd_id128_get_machine(&id);
        else
                r = sd_id128_get_machine_app_specific(arg_app, &id);
        if (r < 0)
                return log_error_errno(r, "Failed to get %smachine-ID: %m",
                                       sd_id128_is_null(arg_app) ? "" : "app-specific ");

        return id128_pretty_print(id, arg_pretty);
}