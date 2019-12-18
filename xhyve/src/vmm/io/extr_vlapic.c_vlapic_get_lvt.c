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
typedef  int /*<<< orphan*/  uint32_t ;
struct vlapic {int /*<<< orphan*/ * lvt_last; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_load_acq_32 (int /*<<< orphan*/ *) ; 
 int lvt_off_to_idx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint32_t
vlapic_get_lvt(struct vlapic *vlapic, uint32_t offset)
{
	int idx;
	uint32_t val;

	idx = lvt_off_to_idx(offset);
	val = atomic_load_acq_32(&vlapic->lvt_last[idx]);
	return (val);
}