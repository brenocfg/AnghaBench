#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int inh; } ;
typedef  TYPE_1__ RangeVar ;

/* Variables and functions */

__attribute__((used)) static bool
relation_should_recurse(RangeVar *rv)
{
#if !PG96
	return rv->inh;
#else
	if (rv->inhOpt == INH_DEFAULT)
	{
		char *inherit_guc = GetConfigOptionByName("SQL_inheritance", NULL, false);

		return strncmp(inherit_guc, "on", 2) == 0;
	}
	return rv->inhOpt == INH_YES;
#endif
}