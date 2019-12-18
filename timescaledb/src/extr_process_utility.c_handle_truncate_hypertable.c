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
typedef  int /*<<< orphan*/  TruncateStmt ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  ProcessUtilityArgs ;
typedef  TYPE_2__ Hypertable ;

/* Variables and functions */
 int /*<<< orphan*/  foreach_chunk (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_add_hypertable (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  process_truncate_chunk ; 
 int /*<<< orphan*/  ts_chunk_delete_by_hypertable_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_truncate_hypertable(ProcessUtilityArgs *args, TruncateStmt *stmt, Hypertable *ht)
{
	process_add_hypertable(args, ht);

	/* Delete the metadata */
	ts_chunk_delete_by_hypertable_id(ht->fd.id);

	/* Drop the chunk tables */
	foreach_chunk(ht, process_truncate_chunk, stmt);
}