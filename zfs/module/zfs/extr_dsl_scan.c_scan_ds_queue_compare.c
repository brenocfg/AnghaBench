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
struct TYPE_2__ {scalar_t__ sds_dsobj; } ;
typedef  TYPE_1__ scan_ds_t ;

/* Variables and functions */

__attribute__((used)) static int
scan_ds_queue_compare(const void *a, const void *b)
{
	const scan_ds_t *sds_a = a, *sds_b = b;

	if (sds_a->sds_dsobj < sds_b->sds_dsobj)
		return (-1);
	if (sds_a->sds_dsobj == sds_b->sds_dsobj)
		return (0);
	return (1);
}