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
struct options_table_entry {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* options_parse (char const*,int*) ; 
 struct options_table_entry* options_table ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,size_t) ; 
 char* xstrdup (int /*<<< orphan*/ *) ; 

char *
options_match(const char *s, int *idx, int *ambiguous)
{
	const struct options_table_entry	*oe, *found;
	char					*name;
	size_t					 namelen;

	name = options_parse(s, idx);
	if (name == NULL)
		return (NULL);
	namelen = strlen(name);

	if (*name == '@') {
		*ambiguous = 0;
		return (name);
	}

	found = NULL;
	for (oe = options_table; oe->name != NULL; oe++) {
		if (strcmp(oe->name, name) == 0) {
			found = oe;
			break;
		}
		if (strncmp(oe->name, name, namelen) == 0) {
			if (found != NULL) {
				*ambiguous = 1;
				free(name);
				return (NULL);
			}
			found = oe;
		}
	}
	free(name);
	if (found == NULL) {
		*ambiguous = 0;
		return (NULL);
	}
	return (xstrdup(found->name));
}