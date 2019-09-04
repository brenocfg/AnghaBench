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
struct TYPE_2__ {int irq_active; int /*<<< orphan*/  irq; } ;
struct atkbdc_softc {int* ram; TYPE_1__ aux; } ;

/* Variables and functions */
 int KBD_ENABLE_AUX_INT ; 
 int /*<<< orphan*/  xh_vm_isa_pulse_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atkbdc_assert_aux_intr(struct atkbdc_softc *sc)
{
	if ((sc->ram[0] & KBD_ENABLE_AUX_INT) != 0) {
		sc->aux.irq_active = true;
		xh_vm_isa_pulse_irq(sc->aux.irq, sc->aux.irq);
	}
}