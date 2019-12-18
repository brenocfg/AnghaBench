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
struct TYPE_4__ {int use_or; int /*<<< orphan*/  type; int /*<<< orphan*/ * values; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ DimensionValues ;

/* Variables and functions */
 TYPE_1__* palloc (int) ; 

__attribute__((used)) static DimensionValues *
dimension_values_create(List *values, Oid type, bool use_or)
{
	DimensionValues *dimvalues;

	dimvalues = palloc(sizeof(DimensionValues));
	dimvalues->values = values;
	dimvalues->use_or = use_or;
	dimvalues->type = type;

	return dimvalues;
}