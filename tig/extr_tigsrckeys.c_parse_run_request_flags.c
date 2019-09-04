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
struct run_request_flags {int internal; int silent; int confirm; int exit; int echo; int quick; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 char* COMMAND_FLAGS ; 
 int SUCCESS ; 
 int error (char*,...) ; 
 int /*<<< orphan*/  strchr (char*,char const) ; 

enum status_code
parse_run_request_flags(struct run_request_flags *flags, const char **argv)
{
	if (!argv[0])
		return error("No arguments");

	if (!strchr(COMMAND_FLAGS, *argv[0]))
		return error("Unknown command flag '%c'; expected one of %s", argv[0][0], COMMAND_FLAGS);

	while (*argv[0]) {
		if (*argv[0] == ':') {
			flags->internal = 1;
			argv[0]++;
			break;
		} else if (*argv[0] == '@') {
			flags->silent = 1;
		} else if (*argv[0] == '?') {
			flags->confirm = 1;
		} else if (*argv[0] == '<') {
			flags->exit = 1;
		} else if (*argv[0] == '+') {
			flags->echo = 1;
		} else if (*argv[0] == '>') {
			flags->quick = 1;
		} else if (*argv[0] != '!') {
			break;
		}
		argv[0]++;
	}

	return SUCCESS;
}