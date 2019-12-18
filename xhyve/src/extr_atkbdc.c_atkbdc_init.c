#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inout_port {char* name; int size; struct atkbdc_softc* arg; int /*<<< orphan*/  handler; void* flags; int /*<<< orphan*/  port; } ;
struct TYPE_4__ {void* irq; } ;
struct TYPE_3__ {void* irq; } ;
struct atkbdc_softc {int /*<<< orphan*/  ps2mouse_sc; int /*<<< orphan*/  ps2kbd_sc; TYPE_2__ aux; TYPE_1__ kbd; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 void* AUX_DEV_IRQ ; 
 void* IOPORT_F_INOUT ; 
 int /*<<< orphan*/  KBD_DATA_PORT ; 
 void* KBD_DEV_IRQ ; 
 int /*<<< orphan*/  KBD_STS_CTL_PORT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atkbdc_data_handler ; 
 int /*<<< orphan*/  atkbdc_sts_ctl_handler ; 
 int /*<<< orphan*/  bzero (struct inout_port*,int) ; 
 struct atkbdc_softc* calloc (int,int) ; 
 int /*<<< orphan*/  pci_irq_reserve (void*) ; 
 int /*<<< orphan*/  ps2kbd_init (struct atkbdc_softc*) ; 
 int /*<<< orphan*/  ps2mouse_init (struct atkbdc_softc*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int register_inout (struct inout_port*) ; 

void
atkbdc_init()
{
	struct inout_port iop;
	struct atkbdc_softc *sc;
	int error;

	sc = calloc(1, sizeof(struct atkbdc_softc));

	pthread_mutex_init(&sc->mtx, NULL);

	bzero(&iop, sizeof(struct inout_port));
	iop.name = "atkdbc";
	iop.port = KBD_STS_CTL_PORT;
	iop.size = 1;
	iop.flags = IOPORT_F_INOUT;
	iop.handler = atkbdc_sts_ctl_handler;
	iop.arg = sc;

	error = register_inout(&iop);
	assert(error == 0);

	bzero(&iop, sizeof(struct inout_port));
	iop.name = "atkdbc";
	iop.port = KBD_DATA_PORT;
	iop.size = 1;
	iop.flags = IOPORT_F_INOUT;
	iop.handler = atkbdc_data_handler;
	iop.arg = sc;

	error = register_inout(&iop);
	assert(error == 0);

	pci_irq_reserve(KBD_DEV_IRQ);
	sc->kbd.irq = KBD_DEV_IRQ;

	pci_irq_reserve(AUX_DEV_IRQ);
	sc->aux.irq = AUX_DEV_IRQ;

	sc->ps2kbd_sc = ps2kbd_init(sc);
	sc->ps2mouse_sc = ps2mouse_init(sc);
}