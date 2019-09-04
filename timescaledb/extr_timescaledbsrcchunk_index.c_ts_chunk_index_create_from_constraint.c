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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_index_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_constraint_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 

void
ts_chunk_index_create_from_constraint(int32 hypertable_id, Oid hypertable_constraint,
									  int32 chunk_id, Oid chunk_constraint)
{
	Oid chunk_indexrelid = get_constraint_index(chunk_constraint);
	Oid hypertable_indexrelid = get_constraint_index(hypertable_constraint);

	Assert(OidIsValid(chunk_indexrelid));
	Assert(OidIsValid(hypertable_indexrelid));

	chunk_index_insert(chunk_id,
					   get_rel_name(chunk_indexrelid),
					   hypertable_id,
					   get_rel_name(hypertable_indexrelid));
}