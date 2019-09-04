#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_6__ {int /*<<< orphan*/  pi_exprContext; } ;
typedef  TYPE_1__ ProjectionInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* ExecBuildProjectionInfoCompat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  get_projection_info_slot_compat (TYPE_1__*) ; 
 scalar_t__ map_variable_attnos_compat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ProjectionInfo *
get_adjusted_projection_info_returning(ProjectionInfo *orig, List *returning_clauses,
									   AttrNumber *map, int map_size, Index varno, Oid rowtype,
									   TupleDesc chunk_desc)
{
	bool found_whole_row;

	Assert(returning_clauses != NIL);

	/* map hypertable attnos -> chunk attnos */
	returning_clauses = (List *) map_variable_attnos_compat((Node *) returning_clauses,
															varno,
															0,
															map,
															map_size,
															rowtype,
															&found_whole_row);

	return ExecBuildProjectionInfoCompat(returning_clauses,
										 orig->pi_exprContext,
										 get_projection_info_slot_compat(orig),
										 NULL,
										 chunk_desc);
}