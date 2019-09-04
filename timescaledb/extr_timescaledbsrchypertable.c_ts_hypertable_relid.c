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
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hypertable_relid_lookup (int /*<<< orphan*/ ) ; 

Oid
ts_hypertable_relid(RangeVar *rv)
{
	return hypertable_relid_lookup(RangeVarGetRelid(rv, NoLock, true));
}