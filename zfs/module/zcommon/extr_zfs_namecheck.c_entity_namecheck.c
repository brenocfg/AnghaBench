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
typedef  int /*<<< orphan*/  namecheck_err_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  NAME_ERR_EMPTY_COMPONENT ; 
 int /*<<< orphan*/  NAME_ERR_INVALCHAR ; 
 int /*<<< orphan*/  NAME_ERR_LEADING_SLASH ; 
 int /*<<< orphan*/  NAME_ERR_MULTIPLE_DELIMITERS ; 
 int /*<<< orphan*/  NAME_ERR_PARENT_REF ; 
 int /*<<< orphan*/  NAME_ERR_SELF_REF ; 
 int /*<<< orphan*/  NAME_ERR_TOOLONG ; 
 int /*<<< orphan*/  NAME_ERR_TRAILING_SLASH ; 
 scalar_t__ ZFS_MAX_DATASET_NAME_LEN ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  valid_char (char const) ; 

int
entity_namecheck(const char *path, namecheck_err_t *why, char *what)
{
	const char *end;

	/*
	 * Make sure the name is not too long.
	 */
	if (strlen(path) >= ZFS_MAX_DATASET_NAME_LEN) {
		if (why)
			*why = NAME_ERR_TOOLONG;
		return (-1);
	}

	/* Explicitly check for a leading slash.  */
	if (path[0] == '/') {
		if (why)
			*why = NAME_ERR_LEADING_SLASH;
		return (-1);
	}

	if (path[0] == '\0') {
		if (why)
			*why = NAME_ERR_EMPTY_COMPONENT;
		return (-1);
	}

	const char *start = path;
	boolean_t found_delim = B_FALSE;
	for (;;) {
		/* Find the end of this component */
		end = start;
		while (*end != '/' && *end != '@' && *end != '#' &&
		    *end != '\0')
			end++;

		if (*end == '\0' && end[-1] == '/') {
			/* trailing slashes are not allowed */
			if (why)
				*why = NAME_ERR_TRAILING_SLASH;
			return (-1);
		}

		/* Validate the contents of this component */
		for (const char *loc = start; loc != end; loc++) {
			if (!valid_char(*loc) && *loc != '%') {
				if (why) {
					*why = NAME_ERR_INVALCHAR;
					*what = *loc;
				}
				return (-1);
			}
		}

		if (*end == '\0' || *end == '/') {
			int component_length = end - start;
			/* Validate the contents of this component is not '.' */
			if (component_length == 1) {
				if (start[0] == '.') {
					if (why)
						*why = NAME_ERR_SELF_REF;
					return (-1);
				}
			}

			/* Validate the content of this component is not '..' */
			if (component_length == 2) {
				if (start[0] == '.' && start[1] == '.') {
					if (why)
						*why = NAME_ERR_PARENT_REF;
					return (-1);
				}
			}
		}

		/* Snapshot or bookmark delimiter found */
		if (*end == '@' || *end == '#') {
			/* Multiple delimiters are not allowed */
			if (found_delim != 0) {
				if (why)
					*why = NAME_ERR_MULTIPLE_DELIMITERS;
				return (-1);
			}

			found_delim = B_TRUE;
		}

		/* Zero-length components are not allowed */
		if (start == end) {
			if (why)
				*why = NAME_ERR_EMPTY_COMPONENT;
			return (-1);
		}

		/* If we've reached the end of the string, we're OK */
		if (*end == '\0')
			return (0);

		/*
		 * If there is a '/' in a snapshot or bookmark name
		 * then report an error
		 */
		if (*end == '/' && found_delim != 0) {
			if (why)
				*why = NAME_ERR_TRAILING_SLASH;
			return (-1);
		}

		/* Update to the next component */
		start = end + 1;
	}
}