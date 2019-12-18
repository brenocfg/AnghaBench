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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {TYPE_1__* sm_phys; } ;
typedef  TYPE_2__ space_map_t ;
struct TYPE_4__ {int /*<<< orphan*/  smp_length; } ;

/* Variables and functions */

uint64_t
space_map_length(space_map_t *sm)
{
	return (sm != NULL ? sm->sm_phys->smp_length : 0);
}