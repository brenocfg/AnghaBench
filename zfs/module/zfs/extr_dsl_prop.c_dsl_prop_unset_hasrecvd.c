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
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPROP_SRC_NONE ; 
 int /*<<< orphan*/  dsl_prop_set_hasrecvd_impl (char const*,int /*<<< orphan*/ ) ; 

void
dsl_prop_unset_hasrecvd(const char *dsname)
{
	VERIFY0(dsl_prop_set_hasrecvd_impl(dsname, ZPROP_SRC_NONE));
}