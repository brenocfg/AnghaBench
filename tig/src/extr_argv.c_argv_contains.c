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
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

bool
argv_contains(const char **argv, const char *arg)
{
	int i;

	for (i = 0; argv && argv[i]; i++)
		if (!strcmp(argv[i], arg))
			return true;
	return false;
}