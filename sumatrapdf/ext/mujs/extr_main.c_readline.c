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
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 

char *readline(const char *prompt)
{
	static char line[500], *p;
	int n;
	fputs(prompt, stdout);
	p = fgets(line, sizeof line, stdin);
	if (p) {
		n = strlen(line);
		if (n > 0 && line[n-1] == '\n')
			line[--n] = 0;
		p = malloc(n+1);
		memcpy(p, line, n+1);
		return p;
	}
	return NULL;
}