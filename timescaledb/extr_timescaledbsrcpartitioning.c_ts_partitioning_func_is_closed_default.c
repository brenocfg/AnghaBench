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
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEFAULT_PARTITIONING_FUNC_NAME ; 
 int /*<<< orphan*/  DEFAULT_PARTITIONING_FUNC_SCHEMA ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool
ts_partitioning_func_is_closed_default(const char *schema, const char *funcname)
{
	Assert(schema != NULL && funcname != NULL);

	return strcmp(DEFAULT_PARTITIONING_FUNC_SCHEMA, schema) == 0 &&
		   strcmp(DEFAULT_PARTITIONING_FUNC_NAME, funcname) == 0;
}