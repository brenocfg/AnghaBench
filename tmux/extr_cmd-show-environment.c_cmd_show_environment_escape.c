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
struct environ_entry {char* value; } ;

/* Variables and functions */
 int strlen (char const*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *
cmd_show_environment_escape(struct environ_entry *envent)
{
	const char	*value = envent->value;
	char		 c, *out, *ret;

	out = ret = xmalloc(strlen(value) * 2 + 1); /* at most twice the size */
	while ((c = *value++) != '\0') {
		/* POSIX interprets $ ` " and \ in double quotes. */
		if (c == '$' || c == '`' || c == '"' || c == '\\')
			*out++ = '\\';
		*out++ = c;
	}
	*out = '\0';

	return (ret);
}