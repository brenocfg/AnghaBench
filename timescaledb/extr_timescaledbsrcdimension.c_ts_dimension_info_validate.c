#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_2__ fd; } ;
struct TYPE_10__ {int skip; int set_not_null; int /*<<< orphan*/  adaptive_chunking; int /*<<< orphan*/  interval_datum; int /*<<< orphan*/  interval_type; int /*<<< orphan*/ * colname; int /*<<< orphan*/  interval; int /*<<< orphan*/  partitioning_func; int /*<<< orphan*/  coltype; int /*<<< orphan*/  type; int /*<<< orphan*/  num_slices; scalar_t__ num_slices_is_set; int /*<<< orphan*/  dimension_id; int /*<<< orphan*/  if_not_exists; TYPE_1__* ht; int /*<<< orphan*/  table_relid; } ;
struct TYPE_8__ {int /*<<< orphan*/  space; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ DimensionInfo ;
typedef  TYPE_4__ Dimension ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNAME ; 
 int /*<<< orphan*/  Anum_pg_attribute_attnotnull ; 
 int /*<<< orphan*/  Anum_pg_attribute_atttypid ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DIMENSION_INFO_IS_SET (TYPE_3__*) ; 
 int /*<<< orphan*/  DIMENSION_TYPE_ANY ; 
 int /*<<< orphan*/  DIMENSION_TYPE_CLOSED ; 
 int /*<<< orphan*/  DIMENSION_TYPE_OPEN ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetObjectId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_FUNCTION_DEFINITION ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_TS_DUPLICATE_DIMENSION ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_VALID_NUM_SLICES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_INT16_MAX ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheAttName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dimension_interval_to_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_func_rettype (int /*<<< orphan*/ ) ; 
 TYPE_4__* ts_hyperspace_get_dimension_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_partitioning_func_get_closed_default () ; 
 int /*<<< orphan*/  ts_partitioning_func_is_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ts_dimension_info_validate(DimensionInfo *info)
{
	Dimension *dim;
	HeapTuple tuple;
	Datum datum;
	bool isnull = false;
	bool not_null_is_set;

	if (!DIMENSION_INFO_IS_SET(info))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE), errmsg("invalid dimension info")));

	if (info->num_slices_is_set && OidIsValid(info->interval_type))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("cannot specify both the number of partitions and an interval")));

	/* Check that the column exists and get its NOT NULL status */
	tuple = SearchSysCacheAttName(info->table_relid, NameStr(*info->colname));

	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_COLUMN),
				 errmsg("column \"%s\" does not exist", NameStr(*info->colname))));

	datum = SysCacheGetAttr(ATTNAME, tuple, Anum_pg_attribute_atttypid, &isnull);
	Assert(!isnull);

	info->coltype = DatumGetObjectId(datum);

	datum = SysCacheGetAttr(ATTNAME, tuple, Anum_pg_attribute_attnotnull, &isnull);
	Assert(!isnull);

	not_null_is_set = DatumGetBool(datum);

	ReleaseSysCache(tuple);

	if (NULL != info->ht)
	{
		/* Check if the dimension already exists */
		dim = ts_hyperspace_get_dimension_by_name(info->ht->space,
												  DIMENSION_TYPE_ANY,
												  NameStr(*info->colname));

		if (NULL != dim)
		{
			if (!info->if_not_exists)
				ereport(ERROR,
						(errcode(ERRCODE_TS_DUPLICATE_DIMENSION),
						 errmsg("column \"%s\" is already a dimension", NameStr(*info->colname))));

			info->dimension_id = dim->fd.id;
			info->skip = true;

			ereport(NOTICE,
					(errmsg("column \"%s\" is already a dimension, skipping",
							NameStr(*info->colname))));
			return;
		}
	}

	if (info->num_slices_is_set)
	{
		/* Closed ("space") dimension */
		info->type = DIMENSION_TYPE_CLOSED;

		if (!OidIsValid(info->partitioning_func))
			info->partitioning_func = ts_partitioning_func_get_closed_default();
		else if (!ts_partitioning_func_is_valid(info->partitioning_func, info->type, info->coltype))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
					 errmsg("invalid partitioning function"),
					 errhint("A valid partitioning function for closed (space) dimensions must be "
							 "IMMUTABLE "
							 "and have the signature (anyelement) -> integer.")));

		if (!IS_VALID_NUM_SLICES(info->num_slices))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("invalid number of partitions: must be between 1 and %d",
							PG_INT16_MAX)));
	}
	else
	{
		/* Open ("time") dimension */
		Oid dimtype = info->coltype;

		info->type = DIMENSION_TYPE_OPEN;
		info->set_not_null = !not_null_is_set;

		if (OidIsValid(info->partitioning_func))
		{
			if (!ts_partitioning_func_is_valid(info->partitioning_func, info->type, info->coltype))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
						 errmsg("invalid partitioning function"),
						 errhint("A valid partitioning function for open (time) dimensions must be "
								 "IMMUTABLE, "
								 "take the column type as input, and return an integer or "
								 "timestamp type.")));

			dimtype = get_func_rettype(info->partitioning_func);
		}

		info->interval = dimension_interval_to_internal(NameStr(*info->colname),
														dimtype,
														info->interval_type,
														info->interval_datum,
														info->adaptive_chunking);
	}
}