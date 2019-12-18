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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  adaptive_chunking; int /*<<< orphan*/  interval_datum; int /*<<< orphan*/  interval_type; int /*<<< orphan*/ * colname; int /*<<< orphan*/  interval; int /*<<< orphan*/  partitioning_func; int /*<<< orphan*/  coltype; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ DimensionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DIMENSION_TYPE_OPEN ; 
 int /*<<< orphan*/  ERRCODE_INVALID_FUNCTION_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_interval_to_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  get_func_rettype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_partitioning_func_is_valid (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dimension_info_validate_open(DimensionInfo *info)
{
	Oid dimtype = info->coltype;

	Assert(info->type == DIMENSION_TYPE_OPEN);

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