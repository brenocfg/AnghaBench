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
struct TYPE_2__ {scalar_t__ width; scalar_t__ size; int /*<<< orphan*/  data; } ;
struct grid_cell {scalar_t__ fg; scalar_t__ bg; scalar_t__ attr; scalar_t__ flags; TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
grid_cells_equal(const struct grid_cell *gca, const struct grid_cell *gcb)
{
	if (gca->fg != gcb->fg || gca->bg != gcb->bg)
		return (0);
	if (gca->attr != gcb->attr || gca->flags != gcb->flags)
		return (0);
	if (gca->data.width != gcb->data.width)
		return (0);
	if (gca->data.size != gcb->data.size)
		return (0);
	return (memcmp(gca->data.data, gcb->data.data, gca->data.size) == 0);
}