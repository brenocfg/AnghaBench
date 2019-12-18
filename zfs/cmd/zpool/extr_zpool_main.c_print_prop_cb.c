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
 int ZPROP_CONT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ zpool_prop_readonly (int) ; 
 char* zpool_prop_to_name (int) ; 
 char* zpool_prop_values (int) ; 

__attribute__((used)) static int
print_prop_cb(int prop, void *cb)
{
	FILE *fp = cb;

	(void) fprintf(fp, "\t%-19s  ", zpool_prop_to_name(prop));

	if (zpool_prop_readonly(prop))
		(void) fprintf(fp, "  NO   ");
	else
		(void) fprintf(fp, " YES   ");

	if (zpool_prop_values(prop) == NULL)
		(void) fprintf(fp, "-\n");
	else
		(void) fprintf(fp, "%s\n", zpool_prop_values(prop));

	return (ZPROP_CONT);
}