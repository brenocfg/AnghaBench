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
typedef  int /*<<< orphan*/  zoneid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GLOBAL_ZONEID ; 
 int /*<<< orphan*/  GLOBAL_ZONEID_NAME ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

zoneid_t
getzoneidbyname(const char *name)
{
	if (name == NULL)
		return (GLOBAL_ZONEID);

	if (strcmp(name, GLOBAL_ZONEID_NAME) == 0)
		return (GLOBAL_ZONEID);

	return (EINVAL);
}