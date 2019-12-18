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
typedef  int /*<<< orphan*/  proc_filter ;
struct TYPE_3__ {int /*<<< orphan*/  func_fmgr; int /*<<< orphan*/  rettype; int /*<<< orphan*/  name; int /*<<< orphan*/  schema; } ;
typedef  TYPE_1__ PartitioningFunc ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ DimensionType ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ DIMENSION_TYPE_CLOSED ; 
 scalar_t__ DIMENSION_TYPE_OPEN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closed_dim_partitioning_func_filter ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  fmgr_info_cxt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_dim_partitioning_func_filter ; 
 int /*<<< orphan*/  ts_lookup_proc_filtered (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
partitioning_func_set_func_fmgr(PartitioningFunc *pf, Oid argtype, DimensionType dimtype)
{
	Oid funcoid;
	proc_filter filter = dimtype == DIMENSION_TYPE_CLOSED ? closed_dim_partitioning_func_filter :
															open_dim_partitioning_func_filter;

	if (dimtype != DIMENSION_TYPE_CLOSED && dimtype != DIMENSION_TYPE_OPEN)
		elog(ERROR, "invalid dimension type %u", dimtype);

	funcoid = ts_lookup_proc_filtered(pf->schema, pf->name, &pf->rettype, filter, &argtype);

	if (!OidIsValid(funcoid))
	{
		if (dimtype == DIMENSION_TYPE_CLOSED)
			ereport(ERROR,
					(errmsg("invalid partitioning function"),
					 errhint("A partitioning function for a closed (space) dimension "
							 "must be IMMUTABLE and have the signature (anyelement) -> integer")));
		else
			ereport(ERROR,
					(errmsg("invalid partitioning function"),
					 errhint("A partitioning function for a open (time) dimension "
							 "must be IMMUTABLE, take one argument, and return a supported time "
							 "type")));
	}

	fmgr_info_cxt(funcoid, &pf->func_fmgr, CurrentMemoryContext);
}