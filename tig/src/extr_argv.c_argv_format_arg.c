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
struct argv_env {int dummy; } ;

/* Variables and functions */
 scalar_t__ argv_format (struct argv_env*,char const***,char const**,int,int) ; 
 int /*<<< orphan*/  free (char const**) ; 

char *
argv_format_arg(struct argv_env *argv_env, const char *src_arg)
{
	const char *src_argv[] = { src_arg, NULL };
	const char **dst_argv = NULL;
	char *dst_arg = NULL;

	if (argv_format(argv_env, &dst_argv, src_argv, false, true))
		dst_arg = (char *) dst_argv[0];

	free(dst_argv);
	return dst_arg;
}