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
struct option_info {int /*<<< orphan*/  value; int /*<<< orphan*/  type; scalar_t__ seen; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int SUCCESS ; 
 int error (char*,...) ; 
 int parse_args (int /*<<< orphan*/ ,char const**) ; 
 int parse_option (struct option_info*,char*,char const*) ; 
 int parse_ref_formats (int /*<<< orphan*/ ,char const**) ; 
 int parse_view_settings (int /*<<< orphan*/ ,char const*,char const**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum status_code
option_update(struct option_info *option, int argc, const char *argv[])
{
	enum status_code code;

	if (option->seen)
		return SUCCESS;

	if (!strcmp(option->type, "const char **"))
		return parse_args(option->value, argv + 2);

	if (argc < 3)
		return error("Invalid set command: set option = value");

	if (!strcmp(option->type, "view_settings"))
		return parse_view_settings(option->value, argv[0], argv + 2);

	if (!strcmp(option->type, "struct ref_format **"))
		return parse_ref_formats(option->value, argv + 2);

	code = parse_option(option, "", argv[2]);
	if (code == SUCCESS && argc != 3)
		return error("Option %s only takes one value", argv[0]);

	return code;
}