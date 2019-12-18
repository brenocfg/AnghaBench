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
 int /*<<< orphan*/  is_pool (char*) ; 

__attribute__((used)) static int
are_all_pools(int argc, char **argv)
{
	if ((argc == 0) || !*argv)
		return (0);

	while (--argc >= 0)
		if (!is_pool(argv[argc]))
			return (0);

	return (1);
}