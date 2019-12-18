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
struct args {int argc; int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  args_free (struct args*) ; 
 int /*<<< orphan*/  args_set (struct args*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_copy_argv (int,char**) ; 
 int getopt (int,char**,char const*) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/ * strchr (char const*,int) ; 
 struct args* xcalloc (int,int) ; 

struct args *
args_parse(const char *template, int argc, char **argv)
{
	struct args	*args;
	int		 opt;

	args = xcalloc(1, sizeof *args);

	optreset = 1;
	optind = 1;

	while ((opt = getopt(argc, argv, template)) != -1) {
		if (opt < 0)
			continue;
		if (opt == '?' || strchr(template, opt) == NULL) {
			args_free(args);
			return (NULL);
		}
		args_set(args, opt, optarg);
	}
	argc -= optind;
	argv += optind;

	args->argc = argc;
	args->argv = cmd_copy_argv(argc, argv);

	return (args);
}