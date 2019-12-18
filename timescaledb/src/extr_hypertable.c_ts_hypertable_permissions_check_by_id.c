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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  ts_hypertable_id_to_relid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_hypertable_permissions_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ts_hypertable_permissions_check_by_id(int32 hypertable_id)
{
	Oid table_relid = ts_hypertable_id_to_relid(hypertable_id);
	ts_hypertable_permissions_check(table_relid, GetUserId());
}