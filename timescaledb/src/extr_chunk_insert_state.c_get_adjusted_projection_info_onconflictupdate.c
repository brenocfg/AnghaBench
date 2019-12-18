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
typedef  int /*<<< orphan*/  TupleConversionMap ;
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
 int /*<<< orphan*/  INNER_VAR ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/ * adjust_hypertable_tlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_projection_info_slot_compat (TYPE_1__*) ; 
 scalar_t__ map_variable_attnos_compat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ProjectionInfo *
get_adjusted_projection_info_onconflictupdate(ProjectionInfo *orig, List *update_tles,
											  AttrNumber *variable_attnos_map,
											  int variable_attnos_map_size, Index varno,
											  Oid rowtype, TupleDesc chunk_desc,
											  TupleConversionMap *hypertable_to_chunk_map)
{
	bool found_whole_row;

	Assert(update_tles != NIL);
	/* copy the tles so as not to scribble on the hypertable tles */
	update_tles = copyObject(update_tles);

	/* map hypertable attnos -> chunk attnos for the hypertable */
	update_tles = (List *) map_variable_attnos_compat((Node *) update_tles,
													  varno,
													  0,
													  variable_attnos_map,
													  variable_attnos_map_size,
													  rowtype,
													  &found_whole_row);
	/* map hypertable attnos -> chunk attnos for the "excluded" table */
	update_tles = (List *) map_variable_attnos_compat((Node *) update_tles,
													  INNER_VAR,
													  0,
													  variable_attnos_map,
													  variable_attnos_map_size,
													  rowtype,
													  &found_whole_row);

	update_tles = adjust_hypertable_tlist(update_tles, hypertable_to_chunk_map);

	return ExecBuildProjectionInfoCompat(update_tles,
										 orig->pi_exprContext,
										 get_projection_info_slot_compat(orig),
										 NULL,
										 chunk_desc);
}