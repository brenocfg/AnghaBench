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
 scalar_t__ isspace (int) ; 

__attribute__((used)) static int
HaveCommandNameOnly(char *cmdstart)
{
	char *cp;
	for (cp = cmdstart; *cp != '\0'; cp++) {
		if (isspace((int) *cp))
			return (0);	/* At least one argument in progress. */
	}
	return (1);
}