#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Var ;
typedef  int /*<<< orphan*/  TargetEntry ;
struct TYPE_9__ {int /*<<< orphan*/  varattno_map; TYPE_2__* info; } ;
struct TYPE_8__ {int /*<<< orphan*/  relid; } ;
struct TYPE_7__ {TYPE_1__* compressed_rel; TYPE_3__* compressed_rte; } ;
struct TYPE_6__ {int /*<<< orphan*/  relid; } ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_4__ DecompressChunkPath ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ INT4OID ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ get_attnum (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_atttype (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lappend_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * makeTargetEntry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * makeVar (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TargetEntry *
make_compressed_scan_meta_targetentry(DecompressChunkPath *path, char *column_name, int id,
									  int tle_index)
{
	Var *scan_var;
	AttrNumber compressed_attno = get_attnum(path->info->compressed_rte->relid, column_name);
	if (compressed_attno == InvalidAttrNumber)
		elog(ERROR, "lookup failed for column \"%s\"", column_name);

	/*
	 * this is called for adding the count and sequence num column which are both int4
	 * if we ever need columns with different datatype here we need to add
	 * dynamic type lookup
	 */
	Assert(get_atttype(path->info->compressed_rte->relid, compressed_attno) == INT4OID);
	scan_var = makeVar(path->info->compressed_rel->relid, compressed_attno, INT4OID, -1, 0, 0);
	path->varattno_map = lappend_int(path->varattno_map, id);

	return makeTargetEntry((Expr *) scan_var, tle_index, NULL, false);
}