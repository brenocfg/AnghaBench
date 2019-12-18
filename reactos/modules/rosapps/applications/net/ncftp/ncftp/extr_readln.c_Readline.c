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
typedef  int /*<<< orphan*/  lbuf ;

/* Variables and functions */
 char* StrDup (char*) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gIsTTYr ; 
 char* getline (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

char *
Readline(char *prompt)
{
	char *linecopy, *line, *cp;
	char lbuf[256];

	if (gIsTTYr) {
		line = getline(prompt);
	} else {
		line = fgets(lbuf, sizeof(lbuf) - 1, stdin);
		if (line != NULL) {
			cp = line + strlen(line) - 1;
			if (*cp == '\n')
				*cp = '\0';
		}
	}

	if (line != NULL) {
		if (line[0] == '\0')
			return NULL;	/* EOF */
		linecopy = StrDup(line);
		line = linecopy;
	}
	return (line);
}