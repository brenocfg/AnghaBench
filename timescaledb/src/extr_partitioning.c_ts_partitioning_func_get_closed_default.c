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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ANYELEMENTOID ; 
 int /*<<< orphan*/  DEFAULT_PARTITIONING_FUNC_NAME ; 
 int /*<<< orphan*/  DEFAULT_PARTITIONING_FUNC_SCHEMA ; 
 int /*<<< orphan*/  closed_dim_partitioning_func_filter ; 
 int /*<<< orphan*/  ts_lookup_proc_filtered (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Oid
ts_partitioning_func_get_closed_default(void)
{
	Oid argtype = ANYELEMENTOID;

	return ts_lookup_proc_filtered(DEFAULT_PARTITIONING_FUNC_SCHEMA,
								   DEFAULT_PARTITIONING_FUNC_NAME,
								   NULL,
								   closed_dim_partitioning_func_filter,
								   &argtype);
}