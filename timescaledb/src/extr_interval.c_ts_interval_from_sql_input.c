#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  integer_now_func_schema; int /*<<< orphan*/  integer_now_func; } ;
struct TYPE_13__ {TYPE_1__ fd; } ;
struct TYPE_12__ {int is_time_interval; int /*<<< orphan*/  integer_interval; int /*<<< orphan*/  time_interval; } ;
struct TYPE_11__ {int /*<<< orphan*/  space; } ;
typedef  int Oid ;
typedef  TYPE_2__ Hypertable ;
typedef  TYPE_3__ FormData_ts_interval ;
typedef  TYPE_4__ Dimension ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetIntervalP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_TS_HYPERTABLE_NOT_EXIST ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
#define  INT2OID 131 
#define  INT4OID 130 
#define  INT8OID 129 
#define  INTERVALOID 128 
 int /*<<< orphan*/  IS_INTEGER_TYPE (int) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 int /*<<< orphan*/  get_rel_name (int) ; 
 TYPE_4__* hyperspace_get_open_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* palloc0 (int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 int ts_dimension_get_partition_type (TYPE_4__*) ; 
 int /*<<< orphan*/  ts_dimension_open_typecheck (int const,int,char*) ; 
 TYPE_2__* ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 int /*<<< orphan*/  ts_hypertable_permissions_check (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_time_value_to_internal (int /*<<< orphan*/ ,int) ; 

FormData_ts_interval *
ts_interval_from_sql_input(Oid relid, Datum interval, Oid interval_type, char *parameter_name,
						   char *caller_name)
{
	Hypertable *hypertable;
	Cache *hcache;
	FormData_ts_interval *invl = palloc0(sizeof(FormData_ts_interval));
	Oid partitioning_type;
	Dimension *open_dim;

	ts_hypertable_permissions_check(relid, GetUserId());

	hcache = ts_hypertable_cache_pin();
	hypertable = ts_hypertable_cache_get_entry(hcache, relid);
	/* First verify that the hypertable corresponds to a valid table */
	if (hypertable == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_TS_HYPERTABLE_NOT_EXIST),
				 errmsg("could not add drop_chunks policy because \"%s\" is not a hypertable",
						get_rel_name(relid))));
	/* validate that the open dimension uses a time type */
	open_dim = hyperspace_get_open_dimension(hypertable->space, 0);

	if (NULL == open_dim)
		elog(ERROR, "internal error: no open dimension found while parsing interval");

	partitioning_type = ts_dimension_get_partition_type(open_dim);
	ts_cache_release(hcache);

	switch (interval_type)
	{
		case INTERVALOID:
			if (IS_INTEGER_TYPE(partitioning_type))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("invalid parameter value for %s", parameter_name),
						 errhint("INTERVAL time duration cannot be used with hypertables with "
								 "integer-based time dimensions")));
			ts_dimension_open_typecheck(INTERVALOID, partitioning_type, caller_name);
			invl->is_time_interval = true;
			invl->time_interval = *DatumGetIntervalP(interval);
			break;
		case INT2OID:
		case INT4OID:
		case INT8OID:
			if (!IS_INTEGER_TYPE(partitioning_type))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("invalid parameter value for %s", parameter_name),
						 errhint("integer-based time duration cannot be used with hypertables with "
								 "a timestamp-based time dimensions")));

			if (strlen(NameStr(open_dim->fd.integer_now_func)) == 0 ||
				strlen(NameStr(open_dim->fd.integer_now_func_schema)) == 0)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("integer_now_func not set on hypertable %s", get_rel_name(relid))));

			invl->is_time_interval = false;
			invl->integer_interval = ts_time_value_to_internal(interval, interval_type);

			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("invalid type for parameter %s in %s", parameter_name, caller_name)));
	}

	return invl;
}