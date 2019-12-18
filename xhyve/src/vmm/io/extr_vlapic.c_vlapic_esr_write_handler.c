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
struct vlapic {scalar_t__ esr_pending; struct LAPIC* apic_page; } ;
struct LAPIC {scalar_t__ esr; } ;

/* Variables and functions */

void
vlapic_esr_write_handler(struct vlapic *vlapic)
{
	struct LAPIC *lapic;
	
	lapic = vlapic->apic_page;
	lapic->esr = vlapic->esr_pending;
	vlapic->esr_pending = 0;
}