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
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_8__ {int /*<<< orphan*/  typlen; int /*<<< orphan*/  typbyval; } ;
struct TYPE_7__ {int isnull; int /*<<< orphan*/  value; int /*<<< orphan*/  time; } ;
struct TYPE_6__ {int isnull; } ;
struct TYPE_9__ {TYPE_3__ base; TYPE_2__ prev; TYPE_1__ next; } ;
typedef  TYPE_4__ GapFillInterpolateColumnState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gapfill_interpolate_tuple_returned(GapFillInterpolateColumnState *column, int64 time, Datum value,
								   bool isnull)
{
	column->next.isnull = true;
	column->prev.isnull = isnull;
	if (!isnull)
	{
		column->prev.time = time;
		column->prev.value = datumCopy(value, column->base.typbyval, column->base.typlen);
	}
}