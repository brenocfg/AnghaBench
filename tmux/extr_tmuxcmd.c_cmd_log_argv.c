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
 int /*<<< orphan*/  log_debug (char*,char const*,int,char*) ; 

void
cmd_log_argv(int argc, char **argv, const char *prefix)
{
	int	i;

	for (i = 0; i < argc; i++)
		log_debug("%s: argv[%d]=%s", prefix, i, argv[i]);
}