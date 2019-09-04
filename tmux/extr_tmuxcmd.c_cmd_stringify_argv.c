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
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 scalar_t__ strlen (char*) ; 
 char* xrealloc (char*,size_t) ; 
 char* xstrdup (char*) ; 

char *
cmd_stringify_argv(int argc, char **argv)
{
	char	*buf;
	int	 i;
	size_t	 len;

	if (argc == 0)
		return (xstrdup(""));

	len = 0;
	buf = NULL;

	for (i = 0; i < argc; i++) {
		len += strlen(argv[i]) + 1;
		buf = xrealloc(buf, len);

		if (i == 0)
			*buf = '\0';
		else
			strlcat(buf, " ", len);
		strlcat(buf, argv[i], len);
	}
	return (buf);
}