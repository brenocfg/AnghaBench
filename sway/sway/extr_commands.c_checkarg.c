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
struct cmd_results {int dummy; } ;
typedef  enum expected_args { ____Placeholder_expected_args } expected_args ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INVALID ; 
#define  EXPECTED_AT_LEAST 130 
#define  EXPECTED_AT_MOST 129 
#define  EXPECTED_EQUAL_TO 128 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,char const*,char const*,int,char*,int) ; 

struct cmd_results *checkarg(int argc, const char *name, enum expected_args type, int val) {
	const char *error_name = NULL;
	switch (type) {
	case EXPECTED_AT_LEAST:
		if (argc < val) {
			error_name = "at least ";
		}
		break;
	case EXPECTED_AT_MOST:
		if (argc > val) {
			error_name = "at most ";
		}
		break;
	case EXPECTED_EQUAL_TO:
		if (argc != val) {
			error_name = "";
		}
	}
	return error_name ?
		cmd_results_new(CMD_INVALID, "Invalid %s command "
				"(expected %s%d argument%s, got %d)",
				name, error_name, val, val != 1 ? "s" : "", argc)
		: NULL;
}