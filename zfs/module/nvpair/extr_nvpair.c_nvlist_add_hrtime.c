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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  hrtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_TYPE_HRTIME ; 
 int nvlist_add_common (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
nvlist_add_hrtime(nvlist_t *nvl, const char *name, hrtime_t val)
{
	return (nvlist_add_common(nvl, name, DATA_TYPE_HRTIME, 1, &val));
}