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
struct config_state {int errors; int /*<<< orphan*/  lineno; int /*<<< orphan*/  path; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int ERROR_NO_OPTION_VALUE ; 
 int SIZEOF_ARG ; 
 int SUCCESS ; 
 int /*<<< orphan*/  argv_from_string (char const**,int*,char*) ; 
 int error (char*,char*) ; 
 int /*<<< orphan*/  get_status_message (int) ; 
 int set_option (char*,int,char const**) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum status_code
read_option(char *opt, size_t optlen, char *value, size_t valuelen, void *data)
{
	struct config_state *config = data;
	enum status_code status = ERROR_NO_OPTION_VALUE;

	/* Check for comment markers, since read_properties() will
	 * only ensure opt and value are split at first " \t". */
	optlen = strcspn(opt, "#");
	if (optlen == 0)
		return SUCCESS;

	if (opt[optlen] == 0) {
		/* Look for comment endings in the value. */
		size_t len = strcspn(value, "#");
		const char *argv[SIZEOF_ARG];
		int argc = 0;

		if (len < valuelen) {
			valuelen = len;
			value[valuelen] = 0;
		}

		if (!argv_from_string(argv, &argc, value))
			status = error("Too many option arguments for %s", opt);
		else
			status = set_option(opt, argc, argv);
	}

	if (status != SUCCESS) {
		warn("%s:%zu: %s", config->path, config->lineno,
		     get_status_message(status));
		config->errors = true;
	}

	/* Always keep going if errors are encountered. */
	return SUCCESS;
}