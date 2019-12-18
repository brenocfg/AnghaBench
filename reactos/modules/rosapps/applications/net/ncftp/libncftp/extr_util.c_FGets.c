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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int strlen (char*) ; 

char *
FGets(char *str, size_t size, FILE *fp)
{
	char *cp, *nlptr;

	cp = fgets(str, ((int) size) - 1, fp);
	if (cp != NULL) {
		cp[((int) size) - 1] = '\0';	/* ensure terminator */
		nlptr = cp + strlen(cp) - 1;
		if (*nlptr == '\n')
			*nlptr = '\0';
	} else {
		memset(str, 0, size);
	}
	return cp;
}