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
 char* find_home () ; 
 int /*<<< orphan*/  global_options ; 
 char* options_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*,char const*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *
status_prompt_find_history_file(void)
{
	const char	*home, *history_file;
	char		*path;

	history_file = options_get_string(global_options, "history-file");
	if (*history_file == '\0')
		return (NULL);
	if (*history_file == '/')
		return (xstrdup(history_file));

	if (history_file[0] != '~' || history_file[1] != '/')
		return (NULL);
	if ((home = find_home()) == NULL)
		return (NULL);
	xasprintf(&path, "%s%s", home, history_file + 1);
	return (path);
}