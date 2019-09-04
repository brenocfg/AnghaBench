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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,int*) ; 
 char* strchr (char*,char) ; 
 char* xstrdup (char const*) ; 

char *
options_parse(const char *name, int *idx)
{
	char	*copy, *cp, *end;

	if (*name == '\0')
		return (NULL);
	copy = xstrdup(name);
	if ((cp = strchr(copy, '[')) == NULL) {
		*idx = -1;
		return (copy);
	}
	end = strchr(cp + 1, ']');
	if (end == NULL || end[1] != '\0' || !isdigit((u_char)end[-1])) {
		free(copy);
		return (NULL);
	}
	if (sscanf(cp, "[%d]", idx) != 1 || *idx < 0) {
		free(copy);
		return (NULL);
	}
	*cp = '\0';
	return (copy);
}