#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  main_table_relid; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  int /*<<< orphan*/  HypertableRestrictInfo ;
typedef  TYPE_1__ Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/ * find_inheritance_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_restrict_info_get_chunk_oids (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_hypertable_restrict_info_has_restrictions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
find_children_oids(HypertableRestrictInfo *hri, Hypertable *ht, LOCKMODE lockmode)
{
	/*
	 * Using the HRI only makes sense if we are not using all the chunks,
	 * otherwise using the cached inheritance hierarchy is faster.
	 */
	if (!ts_hypertable_restrict_info_has_restrictions(hri))
		return find_inheritance_children(ht->main_table_relid, lockmode);

	/*
	 * Unlike find_all_inheritors we do not include parent because if there
	 * are restrictions the parent table cannot fulfill them and since we do
	 * have a trigger blocking inserts on the parent table it cannot contain
	 * any rows.
	 */
	return ts_hypertable_restrict_info_get_chunk_oids(hri, ht, lockmode);
}