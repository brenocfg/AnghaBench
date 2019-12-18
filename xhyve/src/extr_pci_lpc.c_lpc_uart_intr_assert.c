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
struct lpc_uart_softc {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  xh_vm_isa_pulse_irq (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
lpc_uart_intr_assert(void *arg)
{
	struct lpc_uart_softc *sc = arg;

	assert(sc->irq >= 0);

	xh_vm_isa_pulse_irq(sc->irq, sc->irq);
}