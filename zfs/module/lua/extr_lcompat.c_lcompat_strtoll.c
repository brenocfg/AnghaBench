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
typedef  int int64_t ;
typedef  int boolean_t ;

/* Variables and functions */

int64_t
lcompat_strtoll(const char *str, char **ptr)
{
	int base;
	const char *cp;
	int digits;
	int64_t value;
	boolean_t is_negative;

	cp = str;
	while (*cp == ' ' || *cp == '\t' || *cp == '\n') {
		cp++;
	}
	is_negative = (*cp == '-');
	if (is_negative) {
		cp++;
	}
	base = 10;

	if (*cp == '0') {
		base = 8;
		cp++;
		if (*cp == 'x' || *cp == 'X') {
			base = 16;
			cp++;
		}
	}

	value = 0;
	for (; *cp != '\0'; cp++) {
		if (*cp >= '0' && *cp <= '9') {
			digits = *cp - '0';
		} else if (*cp >= 'a' && *cp <= 'f') {
			digits = *cp - 'a' + 10;
		} else if (*cp >= 'A' && *cp <= 'F') {
			digits = *cp - 'A' + 10;
		} else {
			break;
		}
		if (digits >= base) {
			break;
		}
		value = (value * base) + digits;
	}

	if (ptr != NULL) {
		*ptr = (char *)cp;
	}
	if (is_negative) {
		value = -value;
	}
	return (value);
}