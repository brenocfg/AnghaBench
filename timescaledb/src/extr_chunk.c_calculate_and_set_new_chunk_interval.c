#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_12__ {scalar_t__ interval_length; int /*<<< orphan*/  id; } ;
struct TYPE_16__ {TYPE_2__ fd; } ;
struct TYPE_15__ {int num_dimensions; TYPE_6__* dimensions; } ;
struct TYPE_11__ {scalar_t__ chunk_target_size; } ;
struct TYPE_14__ {TYPE_1__ fd; int /*<<< orphan*/  chunk_sizing_func; int /*<<< orphan*/  main_table_relid; TYPE_5__* space; } ;
struct TYPE_13__ {scalar_t__* coordinates; } ;
typedef  TYPE_3__ Point ;
typedef  TYPE_4__ Hypertable ;
typedef  TYPE_5__ Hyperspace ;
typedef  TYPE_6__ Dimension ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetInt64 (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_OPEN_DIMENSION (TYPE_6__*) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (scalar_t__) ; 
 int /*<<< orphan*/  OidFunctionCall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimension_set_chunk_interval (TYPE_6__*,scalar_t__) ; 

__attribute__((used)) static bool
calculate_and_set_new_chunk_interval(Hypertable *ht, Point *p)
{
	Hyperspace *hs = ht->space;
	Dimension *dim = NULL;
	Datum datum;
	int64 chunk_interval, coord;
	int i;

	if (!OidIsValid(ht->chunk_sizing_func) || ht->fd.chunk_target_size <= 0)
		return false;

	/* Find first open dimension */
	for (i = 0; i < hs->num_dimensions; i++)
	{
		dim = &hs->dimensions[i];

		if (IS_OPEN_DIMENSION(dim))
			break;

		dim = NULL;
	}

	/* Nothing to do if no open dimension */
	if (NULL == dim)
	{
		elog(WARNING,
			 "adaptive chunking enabled on hypertable \"%s\" without an open (time) dimension",
			 get_rel_name(ht->main_table_relid));

		return false;
	}

	coord = p->coordinates[i];
	datum = OidFunctionCall3(ht->chunk_sizing_func,
							 Int32GetDatum(dim->fd.id),
							 Int64GetDatum(coord),
							 Int64GetDatum(ht->fd.chunk_target_size));
	chunk_interval = DatumGetInt64(datum);

	/* Check if the function didn't set and interval or nothing changed */
	if (chunk_interval <= 0 || chunk_interval == dim->fd.interval_length)
		return false;

	/* Update the dimension */
	ts_dimension_set_chunk_interval(dim, chunk_interval);

	return true;
}