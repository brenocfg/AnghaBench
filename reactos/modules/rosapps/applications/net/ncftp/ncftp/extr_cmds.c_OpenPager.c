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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 char* gPager ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static FILE *
OpenPager(void)
{
	FILE *fp;
	char *pprog;

	(void) fflush(stdout);
	pprog = gPager;
	fp = popen((pprog[0] == '\0') ? "more" : pprog, "w");
	if (fp == NULL)
		return (stdout);
	return (fp);
}