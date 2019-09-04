#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cmd_results {int dummy; } ;
struct TYPE_5__ {TYPE_1__* seat_config; } ;
struct TYPE_6__ {TYPE_2__ handler_context; } ;
struct TYPE_4__ {int /*<<< orphan*/  fallback; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FAILURE ; 
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_EQUAL_TO ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  parse_boolean (char*,int) ; 

struct cmd_results *seat_cmd_fallback(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "fallback", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}
	if (!config->handler_context.seat_config) {
		return cmd_results_new(CMD_FAILURE, "No seat defined");
	}

	config->handler_context.seat_config->fallback =
		parse_boolean(argv[0], false);

	return cmd_results_new(CMD_SUCCESS, NULL);
}