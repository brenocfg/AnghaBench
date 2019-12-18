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
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ DeltaDeltaDecompressionIterator ;
typedef  int /*<<< orphan*/  DecompressionIterator ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ PG_DETOAST_DATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int64_decompression_iterator_init_forward (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc (int) ; 

DecompressionIterator *
delta_delta_decompression_iterator_from_datum_forward(Datum deltadelta_compressed, Oid element_type)
{
	DeltaDeltaDecompressionIterator *iterator = palloc(sizeof(*iterator));
	int64_decompression_iterator_init_forward(iterator,
											  (void *) PG_DETOAST_DATUM(deltadelta_compressed),
											  element_type);
	return &iterator->base;
}