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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/ * colname; int /*<<< orphan*/  num_slices; int /*<<< orphan*/  num_slices_is_set; int /*<<< orphan*/  coltype; int /*<<< orphan*/  partitioning_func; } ;
typedef  TYPE_1__ DimensionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DIMENSION_TYPE_CLOSED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_FUNCTION_DEFINITION ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IS_VALID_NUM_SLICES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_INT16_MAX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  ts_partitioning_func_get_closed_default () ; 
 int /*<<< orphan*/  ts_partitioning_func_is_valid (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dimension_info_validate_closed(DimensionInfo *info)
{
	Assert(info->type == DIMENSION_TYPE_CLOSED);

	if (!OidIsValid(info->partitioning_func))
		info->partitioning_func = ts_partitioning_func_get_closed_default();
	else if (!ts_partitioning_func_is_valid(info->partitioning_func, info->type, info->coltype))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_FUNCTION_DEFINITION),
				 errmsg("invalid partitioning function"),
				 errhint("A valid partitioning function for closed (space) dimensions must be "
						 "IMMUTABLE "
						 "and have the signature (anyelement) -> integer.")));

	if (!info->num_slices_is_set || !IS_VALID_NUM_SLICES(info->num_slices))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid number of partitions for dimension \"%s\"",
						NameStr(*info->colname)),
				 errhint("A closed (space) dimension must specify between 1 and %d partitions.",
						 PG_INT16_MAX)));
}