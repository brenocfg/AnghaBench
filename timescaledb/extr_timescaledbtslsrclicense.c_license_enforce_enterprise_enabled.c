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
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  license_enterprise_enabled () ; 

void
license_enforce_enterprise_enabled(void)
{
	if (!license_enterprise_enabled())
		elog(ERROR, "cannot execute an enterprise function with an invalid enterprise license");
}