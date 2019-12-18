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
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_chunk (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_relation_constraint_oid (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  process_add_constraint_chunk ; 

__attribute__((used)) static void
process_altertable_add_constraint(Hypertable *ht, const char *constraint_name)
{
	Oid hypertable_constraint_oid =
		get_relation_constraint_oid(ht->main_table_relid, constraint_name, false);

	Assert(constraint_name != NULL);

	foreach_chunk(ht, process_add_constraint_chunk, &hypertable_constraint_oid);
}