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
typedef  scalar_t__ key_code ;

/* Variables and functions */
 int xterm_keys_modifiers (char const*,size_t,size_t*,scalar_t__*) ; 

__attribute__((used)) static int
xterm_keys_match(const char *template, const char *buf, size_t len,
    size_t *size, key_code *modifiers)
{
	size_t	pos;
	int	retval;

	*modifiers = 0;

	if (len == 0)
		return (0);

	pos = 0;
	do {
		if (*template == '_') {
			retval = xterm_keys_modifiers(buf, len, &pos,
			    modifiers);
			if (retval != 0)
				return (retval);
			continue;
		}
		if (buf[pos] != *template)
			return (-1);
		pos++;
	} while (*++template != '\0' && pos != len);

	if (*template != '\0')	/* partial */
		return (1);

	*size = pos;
	return (0);
}