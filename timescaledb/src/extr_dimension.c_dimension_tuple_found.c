#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleInfo ;
struct TYPE_2__ {int /*<<< orphan*/  main_table_relid; int /*<<< orphan*/  num_dimensions; int /*<<< orphan*/ * dimensions; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  TYPE_1__ Hyperspace ;
typedef  int /*<<< orphan*/  Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  dimension_fill_in_from_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
dimension_tuple_found(TupleInfo *ti, void *data)
{
	Hyperspace *hs = data;
	Dimension *d = &hs->dimensions[hs->num_dimensions++];

	dimension_fill_in_from_tuple(d, ti, hs->main_table_relid);

	return SCAN_CONTINUE;
}