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
struct vlapic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVTT_TM_PERIODIC ; 
 int /*<<< orphan*/  APIC_OFFSET_TIMER_LVT ; 
 int /*<<< orphan*/  vlapic_get_lvt (struct vlapic*,int /*<<< orphan*/ ) ; 
 int vlapic_get_lvt_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
vlapic_periodic_timer(struct vlapic *vlapic)
{
	uint32_t lvt;
	
	lvt = vlapic_get_lvt(vlapic, APIC_OFFSET_TIMER_LVT);

	return (vlapic_get_lvt_field(lvt, APIC_LVTT_TM_PERIODIC));
}