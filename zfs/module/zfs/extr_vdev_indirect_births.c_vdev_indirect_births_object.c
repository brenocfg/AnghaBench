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
struct TYPE_4__ {int /*<<< orphan*/  vib_object; } ;
typedef  TYPE_1__ vdev_indirect_births_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_indirect_births_verify (TYPE_1__*) ; 

uint64_t
vdev_indirect_births_object(vdev_indirect_births_t *vib)
{
	ASSERT(vdev_indirect_births_verify(vib));

	return (vib->vib_object);
}