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
struct TYPE_3__ {int lot_attr_count; scalar_t__* lot_attrs; } ;
typedef  TYPE_1__ sa_lot_t ;
typedef  scalar_t__ sa_attr_type_t ;
typedef  int boolean_t ;

/* Variables and functions */

boolean_t
sa_layout_equal(sa_lot_t *tbf, sa_attr_type_t *attrs, int count)
{
	int i;

	if (count != tbf->lot_attr_count)
		return (1);

	for (i = 0; i != count; i++) {
		if (attrs[i] != tbf->lot_attrs[i])
			return (1);
	}
	return (0);
}