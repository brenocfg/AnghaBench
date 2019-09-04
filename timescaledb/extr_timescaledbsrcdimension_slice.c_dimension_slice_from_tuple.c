#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Form_dimension_slice ;
typedef  int /*<<< orphan*/  DimensionSlice ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dimension_slice_from_form_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline DimensionSlice *
dimension_slice_from_tuple(HeapTuple tuple)
{
	return dimension_slice_from_form_data((Form_dimension_slice) GETSTRUCT(tuple));
}