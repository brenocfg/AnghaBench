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
typedef  int uint_t ;

/* Variables and functions */
 int /*<<< orphan*/  UU_ERROR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  UU_ERROR_UNKNOWN_FLAG ; 
 int UU_NAME_DOMAIN ; 
 int UU_NAME_PATH ; 
 int /*<<< orphan*/  is_valid_component (char const*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  uu_set_error (int /*<<< orphan*/ ) ; 

int
uu_check_name(const char *name, uint_t flags)
{
	const char *end = name + strlen(name);
	const char *p;

	if (flags & ~(UU_NAME_DOMAIN | UU_NAME_PATH)) {
		uu_set_error(UU_ERROR_UNKNOWN_FLAG);
		return (-1);
	}

	if (!(flags & UU_NAME_PATH)) {
		if (!is_valid_component(name, end, flags))
			goto bad;
		return (0);
	}

	while ((p = strchr(name, '/')) != NULL) {
		if (!is_valid_component(name, p - 1, flags))
			goto bad;
		name = p + 1;
	}
	if (!is_valid_component(name, end, flags))
		goto bad;

	return (0);

bad:
	uu_set_error(UU_ERROR_INVALID_ARGUMENT);
	return (-1);
}