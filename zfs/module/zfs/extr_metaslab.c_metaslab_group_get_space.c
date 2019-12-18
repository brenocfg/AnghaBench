#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_5__ {TYPE_1__* mg_vd; } ;
typedef  TYPE_2__ metaslab_group_t ;
struct TYPE_4__ {unsigned long long vdev_ms_shift; unsigned long long vdev_ms_count; } ;

/* Variables and functions */

uint64_t
metaslab_group_get_space(metaslab_group_t *mg)
{
	return ((1ULL << mg->mg_vd->vdev_ms_shift) * mg->mg_vd->vdev_ms_count);
}