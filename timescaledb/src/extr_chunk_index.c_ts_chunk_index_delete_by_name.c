#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* index_name; int drop_index; char const* schema; } ;
typedef  TYPE_1__ ChunkIndexDeleteData ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_INDEXID ; 
 int /*<<< orphan*/  chunk_index_name_and_schema_filter ; 
 int /*<<< orphan*/  chunk_index_scan_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  chunk_index_tuple_delete ; 

void
ts_chunk_index_delete_by_name(const char *schema, const char *index_name, bool drop_index)
{
	ChunkIndexDeleteData data = {
		.index_name = index_name,
		.drop_index = drop_index,
		.schema = schema,
	};

	chunk_index_scan_update(INVALID_INDEXID,
							NULL,
							0,
							chunk_index_tuple_delete,
							chunk_index_name_and_schema_filter,
							&data);
}