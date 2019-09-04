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
struct TYPE_2__ {int /*<<< orphan*/  smart_gaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUCCESS ; 
 int /*<<< orphan*/  EXPECTED_AT_LEAST ; 
 int /*<<< orphan*/  arrange_root () ; 
 struct cmd_results* checkarg (int,char*,int /*<<< orphan*/ ,int) ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* config ; 
 int /*<<< orphan*/  parse_boolean (char*,int /*<<< orphan*/ ) ; 

struct cmd_results *cmd_smart_gaps(int argc, char **argv) {
	struct cmd_results *error = checkarg(argc, "smart_gaps", EXPECTED_AT_LEAST, 1);

	if (error) {
		return error;
	}

	config->smart_gaps = parse_boolean(argv[0], config->smart_gaps);

	arrange_root();

	return cmd_results_new(CMD_SUCCESS, NULL);
}