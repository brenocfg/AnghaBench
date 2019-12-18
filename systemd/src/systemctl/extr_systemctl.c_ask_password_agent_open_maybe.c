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

/* Variables and functions */
 scalar_t__ UNIT_FILE_SYSTEM ; 
 int /*<<< orphan*/  arg_ask_password ; 
 scalar_t__ arg_dry_run ; 
 scalar_t__ arg_scope ; 
 int /*<<< orphan*/  arg_transport ; 
 int /*<<< orphan*/  ask_password_agent_open_if_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ask_password_agent_open_maybe(void) {
        /* Open the password agent as a child process if necessary */

        if (arg_dry_run)
                return;

        if (arg_scope != UNIT_FILE_SYSTEM)
                return;

        ask_password_agent_open_if_enabled(arg_transport, arg_ask_password);
}