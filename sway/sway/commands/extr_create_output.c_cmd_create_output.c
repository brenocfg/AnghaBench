#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cmd_results {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  create_output ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  sway_assert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wlr_backend_is_multi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_multi_for_each_backend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

struct cmd_results *cmd_create_output(int argc, char **argv) {
	sway_assert(wlr_backend_is_multi(server.backend),
			"Expected a multi backend");

	bool done = false;
	wlr_multi_for_each_backend(server.backend, create_output, &done);

	if (!done) {
		return cmd_results_new(CMD_INVALID,
				"Can only create outputs for Wayland or X11 backends");
	}

	return cmd_results_new(CMD_SUCCESS, NULL);
}