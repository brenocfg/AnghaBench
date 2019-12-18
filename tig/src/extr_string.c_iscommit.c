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

/* Variables and functions */
 int SIZEOF_REV ; 
 int /*<<< orphan*/  isxdigit (char const) ; 

bool
iscommit(const char *str)
{
	int pos;

	for (pos = 0; str[pos]; pos++) {
		if (!isxdigit(str[pos]))
			return false;
	}

	return 7 <= pos && pos < SIZEOF_REV;
}