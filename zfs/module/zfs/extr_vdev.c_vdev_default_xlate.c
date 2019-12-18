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
typedef  int /*<<< orphan*/  vdev_t ;
struct TYPE_4__ {int /*<<< orphan*/  rs_end; int /*<<< orphan*/  rs_start; } ;
typedef  TYPE_1__ range_seg64_t ;

/* Variables and functions */

void
vdev_default_xlate(vdev_t *vd, const range_seg64_t *in, range_seg64_t *res)
{
	res->rs_start = in->rs_start;
	res->rs_end = in->rs_end;
}