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
struct cmd_entry {char* alias; char* name; } ;

/* Variables and functions */
 struct cmd_entry** cmd_table ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlcat (char*,char*,int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*,...) ; 

__attribute__((used)) static const struct cmd_entry *
cmd_find(const char *name, char **cause)
{
	const struct cmd_entry	**loop, *entry, *found = NULL;
	int			  ambiguous;
	char			  s[8192];

	ambiguous = 0;
	for (loop = cmd_table; *loop != NULL; loop++) {
		entry = *loop;
		if (entry->alias != NULL && strcmp(entry->alias, name) == 0) {
			ambiguous = 0;
			found = entry;
			break;
		}

		if (strncmp(entry->name, name, strlen(name)) != 0)
			continue;
		if (found != NULL)
			ambiguous = 1;
		found = entry;

		if (strcmp(entry->name, name) == 0)
			break;
	}
	if (ambiguous)
		goto ambiguous;
	if (found == NULL) {
		xasprintf(cause, "unknown command: %s", name);
		return (NULL);
	}
	return (found);

ambiguous:
	*s = '\0';
	for (loop = cmd_table; *loop != NULL; loop++) {
		entry = *loop;
		if (strncmp(entry->name, name, strlen(name)) != 0)
			continue;
		if (strlcat(s, entry->name, sizeof s) >= sizeof s)
			break;
		if (strlcat(s, ", ", sizeof s) >= sizeof s)
			break;
	}
	s[strlen(s) - 2] = '\0';
	xasprintf(cause, "ambiguous command: %s, could be: %s", name, s);
	return (NULL);
}