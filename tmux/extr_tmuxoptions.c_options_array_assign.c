#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct options_entry {TYPE_1__* tableentry; } ;
struct TYPE_2__ {char* separator; } ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * options_array_item (struct options_entry*,scalar_t__) ; 
 scalar_t__ options_array_set (struct options_entry*,scalar_t__,char const*,int /*<<< orphan*/ ,char**) ; 
 char* strsep (char**,char const*) ; 
 char* xstrdup (char const*) ; 

int
options_array_assign(struct options_entry *o, const char *s, char **cause)
{
	const char	*separator;
	char		*copy, *next, *string;
	u_int		 i;

	separator = o->tableentry->separator;
	if (separator == NULL)
		separator = " ,";
	if (*separator == '\0') {
		if (*s == '\0')
			return (0);
		for (i = 0; i < UINT_MAX; i++) {
			if (options_array_item(o, i) == NULL)
				break;
		}
		return (options_array_set(o, i, s, 0, cause));
	}

	if (*s == '\0')
		return (0);
	copy = string = xstrdup(s);
	while ((next = strsep(&string, separator)) != NULL) {
		if (*next == '\0')
			continue;
		for (i = 0; i < UINT_MAX; i++) {
			if (options_array_item(o, i) == NULL)
				break;
		}
		if (i == UINT_MAX)
			break;
		if (options_array_set(o, i, next, 0, cause) != 0) {
			free(copy);
			return (-1);
		}
	}
	free(copy);
	return (0);
}