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
 int SUCCESS ; 
 size_t strcspn (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static enum status_code
parse_view_column_config_expr(char **pos, const char **name, const char **value, bool first)
{
	size_t len = strcspn(*pos, ",");
	size_t optlen;

	if (strlen(*pos) > len)
		(*pos)[len] = 0;
	optlen = strcspn(*pos, ":=");

	if (first) {
		*name = "display";

		if (optlen == len) {
			*value = len ? *pos : "yes";
			*pos += len + 1;
			return SUCCESS;
		}

		/* Fake boolean enum value. */
		*value = "yes";
		return SUCCESS;
	}

	*name = *pos;
	if (optlen == len)
		*value = "yes";
	else
		*value = *pos + optlen + 1;
	(*pos)[optlen] = 0;
	*pos += len + 1;

	return SUCCESS;
}