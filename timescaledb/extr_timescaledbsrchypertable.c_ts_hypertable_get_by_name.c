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
typedef  int /*<<< orphan*/  Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  hypertable_scan (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hypertable_tuple_found ; 

Hypertable *
ts_hypertable_get_by_name(char *schema, char *name)
{
	Hypertable *ht = NULL;

	hypertable_scan(schema, name, hypertable_tuple_found, &ht, AccessShareLock, false);

	return ht;
}