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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 char* dm_get_underlying_path (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 

boolean_t
zfs_dev_is_dm(const char *dev_name)
{

	char *tmp;
	tmp = dm_get_underlying_path(dev_name);
	if (tmp == NULL)
		return (B_FALSE);

	free(tmp);
	return (B_TRUE);
}