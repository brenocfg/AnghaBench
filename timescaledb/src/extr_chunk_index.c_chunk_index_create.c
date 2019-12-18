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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_index_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_relation_index_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_index_create(Relation hypertable_rel, int32 hypertable_id, Relation hypertable_idxrel,
				   int32 chunk_id, Relation chunkrel, Oid constraint_oid)
{
	Oid chunk_indexrelid;

	if (OidIsValid(constraint_oid))
	{
		/*
		 * If there is an associated constraint then that constraint created
		 * both the index and the catalog entry for the index
		 */
		return;
	}

	chunk_indexrelid =
		chunk_relation_index_create(hypertable_rel, hypertable_idxrel, chunkrel, false, InvalidOid);

	chunk_index_insert(chunk_id,
					   get_rel_name(chunk_indexrelid),
					   hypertable_id,
					   get_rel_name(RelationGetRelid(hypertable_idxrel)));
}