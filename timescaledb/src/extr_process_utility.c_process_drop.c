#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int removeType; } ;
struct TYPE_12__ {scalar_t__ parsetree; } ;
typedef  TYPE_1__ ProcessUtilityArgs ;
typedef  TYPE_2__ DropStmt ;

/* Variables and functions */
#define  OBJECT_INDEX 130 
#define  OBJECT_TABLE 129 
#define  OBJECT_VIEW 128 
 int /*<<< orphan*/  block_dropping_continuous_aggregates_without_cascade (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  process_drop_chunk (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  process_drop_hypertable (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  process_drop_hypertable_index (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void
process_drop(ProcessUtilityArgs *args)
{
	DropStmt *stmt = (DropStmt *) args->parsetree;

	switch (stmt->removeType)
	{
		case OBJECT_TABLE:
			process_drop_hypertable(args, stmt);
			process_drop_chunk(args, stmt);
			break;
		case OBJECT_INDEX:
			process_drop_hypertable_index(args, stmt);
			break;
		case OBJECT_VIEW:
			block_dropping_continuous_aggregates_without_cascade(args, stmt);
			break;
		default:
			break;
	}
}