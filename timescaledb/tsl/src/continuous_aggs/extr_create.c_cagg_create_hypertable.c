#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {char const* colname; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  DimensionInfo ;
typedef  TYPE_1__ ChunkSizingInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INT8OID ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* ts_chunk_sizing_info_get_default_disabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_dimension_info_create_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ts_hypertable_create_from_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
cagg_create_hypertable(int32 hypertable_id, Oid mat_tbloid, const char *matpartcolname,
					   int64 mat_tbltimecol_interval)
{
	bool created;
	int flags = 0;
	NameData mat_tbltimecol;
	DimensionInfo *time_dim_info;
	ChunkSizingInfo *chunk_sizing_info;
	namestrcpy(&mat_tbltimecol, matpartcolname);
	time_dim_info = ts_dimension_info_create_open(mat_tbloid,
												  &mat_tbltimecol,
												  Int64GetDatum(mat_tbltimecol_interval),
												  INT8OID,
												  InvalidOid);
	// TODO fix this after change in C interface
	chunk_sizing_info = ts_chunk_sizing_info_get_default_disabled(mat_tbloid);
	chunk_sizing_info->colname = matpartcolname;
	created = ts_hypertable_create_from_info(mat_tbloid,
											 hypertable_id,
											 flags,
											 time_dim_info,
											 NULL,
											 NULL,
											 NULL,
											 chunk_sizing_info);
	if (!created)
	{
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("continuous agg could not create hypertable for relid")));
	}
}