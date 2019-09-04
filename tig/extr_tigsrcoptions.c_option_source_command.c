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
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int ERROR_FILE_DOES_NOT_EXIST ; 
 int error (char*,...) ; 
 int load_option_file (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum status_code
option_source_command(int argc, const char *argv[])
{
	enum status_code code;
	bool quiet = false;

	if ((argc < 1) || (argc > 2))
		return error("Invalid source command: source [-q] <path>");

	if (argc == 2) {
		if (!strcmp(argv[0], "-q"))
			quiet = true;
		else
			return error("Invalid source option: %s", argv[0]);
	}

	code = load_option_file(argv[argc - 1]);

	if (quiet)
		return code == ERROR_FILE_DOES_NOT_EXIST ? 0 : code;

	return code == ERROR_FILE_DOES_NOT_EXIST
		? error("File does not exist: %s", argv[argc - 1]) : code;
}