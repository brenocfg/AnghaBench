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
struct vhpet {int config; } ;

/* Variables and functions */
 int HPET_CNF_ENABLE ; 

__attribute__((used)) static __inline bool
vhpet_counter_enabled(struct vhpet *vhpet)
{

	return ((vhpet->config & HPET_CNF_ENABLE) ? true : false);
}