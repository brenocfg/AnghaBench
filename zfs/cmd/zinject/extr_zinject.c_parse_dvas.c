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
typedef  int uint32_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int EINVAL ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
parse_dvas(const char *str, uint32_t *dvas_out)
{
	const char *c = str;
	uint32_t mask = 0;
	boolean_t need_delim = B_FALSE;

	/* max string length is 5 ("0,1,2") */
	if (strlen(str) > 5 || strlen(str) == 0)
		return (EINVAL);

	while (*c != '\0') {
		switch (*c) {
		case '0':
		case '1':
		case '2':
			/* check for pipe between DVAs */
			if (need_delim)
				return (EINVAL);

			/* check if this DVA has been set already */
			if (mask & (1 << ((*c) - '0')))
				return (EINVAL);

			mask |= (1 << ((*c) - '0'));
			need_delim = B_TRUE;
			break;
		case ',':
			need_delim = B_FALSE;
			break;
		default:
			/* check for invalid character */
			return (EINVAL);
		}
		c++;
	}

	/* check for dangling delimiter */
	if (!need_delim)
		return (EINVAL);

	*dvas_out = mask;
	return (0);
}