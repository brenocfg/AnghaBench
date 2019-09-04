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
 char* basename (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isalnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ispunct (int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* xstrdup (char const*) ; 

char *
parse_window_name(const char *in)
{
	char	*copy, *name, *ptr;

	name = copy = xstrdup(in);
	if (strncmp(name, "exec ", (sizeof "exec ") - 1) == 0)
		name = name + (sizeof "exec ") - 1;

	while (*name == ' ' || *name == '-')
		name++;
	if ((ptr = strchr(name, ' ')) != NULL)
		*ptr = '\0';

	if (*name != '\0') {
		ptr = name + strlen(name) - 1;
		while (ptr > name &&
		    !isalnum((u_char)*ptr) &&
		    !ispunct((u_char)*ptr))
			*ptr-- = '\0';
	}

	if (*name == '/')
		name = basename(name);
	name = xstrdup(name);
	free(copy);
	return (name);
}