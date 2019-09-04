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
union options_value {char const* string; } ;
struct options_entry {int dummy; } ;
struct options_array_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_free_argv (int,char**) ; 
 scalar_t__ cmd_string_split (char const*,int*,char***) ; 
 int /*<<< orphan*/  global_options ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 struct options_array_item* options_array_first (struct options_entry*) ; 
 union options_value* options_array_item_value (struct options_array_item*) ; 
 struct options_array_item* options_array_next (struct options_array_item*) ; 
 struct options_entry* options_get_only (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 
 char** xcalloc (int,int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int
cmd_try_alias(int *argc, char ***argv)
{
	struct options_entry		 *o;
	struct options_array_item	 *a;
	union options_value		 *ov;
	int				  old_argc = *argc, new_argc, i;
	char				**old_argv = *argv, **new_argv;
	size_t				  wanted;
	const char			 *cp = NULL;

	o = options_get_only(global_options, "command-alias");
	if (o == NULL)
		return (-1);
	wanted = strlen(old_argv[0]);

	a = options_array_first(o);
	while (a != NULL) {
		ov = options_array_item_value(a);
		cp = strchr(ov->string, '=');
		if (cp != NULL &&
		    (size_t)(cp - ov->string) == wanted &&
		    strncmp(old_argv[0], ov->string, wanted) == 0)
			break;
		a = options_array_next(a);
	}
	if (a == NULL)
		return (-1);

	if (cmd_string_split(cp + 1, &new_argc, &new_argv) != 0)
		return (-1);

	*argc = new_argc + old_argc - 1;
	*argv = xcalloc((*argc) + 1, sizeof **argv);

	for (i = 0; i < new_argc; i++)
		(*argv)[i] = xstrdup(new_argv[i]);
	for (i = 1; i < old_argc; i++)
		(*argv)[new_argc + i - 1] = xstrdup(old_argv[i]);

	log_debug("alias: %s=%s", old_argv[0], cp + 1);
	for (i = 0; i < *argc; i++)
		log_debug("alias: argv[%d] = %s", i, (*argv)[i]);

	cmd_free_argv(new_argc, new_argv);
	return (0);
}