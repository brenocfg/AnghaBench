#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_7__ {int /*<<< orphan*/  tablespace_oid; } ;
typedef  TYPE_2__ Tablespace ;
struct TYPE_8__ {TYPE_1__* rd_rel; } ;
struct TYPE_6__ {int /*<<< orphan*/  reltablespace; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_INDEX_TABLESPACE_OFFSET ; 
 int /*<<< orphan*/  InvalidOid ; 
 TYPE_2__* ts_hypertable_get_tablespace_at_offset_from (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
chunk_index_select_tablespace(int32 hypertable_id, Relation chunkrel)
{
	Tablespace *tspc;
	Oid tablespace_oid = InvalidOid;

	tspc = ts_hypertable_get_tablespace_at_offset_from(hypertable_id,
													   chunkrel->rd_rel->reltablespace,
													   CHUNK_INDEX_TABLESPACE_OFFSET);

	if (NULL != tspc)
		tablespace_oid = tspc->tablespace_oid;

	return tablespace_oid;
}