#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_7__ {TYPE_1__* rd_rel; } ;
struct TYPE_6__ {int /*<<< orphan*/  reltablespace; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_index_select_tablespace (int /*<<< orphan*/ ,TYPE_2__*) ; 

Oid
ts_chunk_index_get_tablespace(int32 hypertable_id, Relation template_indexrel, Relation chunkrel)
{
	/*
	 * Determine the index's tablespace. Use the main index's tablespace, or,
	 * if not set, select one at an offset from the chunk's tablespace.
	 */
	if (OidIsValid(template_indexrel->rd_rel->reltablespace))
		return template_indexrel->rd_rel->reltablespace;
	else
		return chunk_index_select_tablespace(hypertable_id, chunkrel);
}