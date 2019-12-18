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
struct lpc_uart_softc {char* name; char* opts; int enabled; int /*<<< orphan*/  iobase; int /*<<< orphan*/  uart_softc; int /*<<< orphan*/  irq; } ;
struct inout_port {char* name; struct lpc_uart_softc* arg; int /*<<< orphan*/  handler; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOPORT_F_INOUT ; 
 int LPC_UART_NUM ; 
 int /*<<< orphan*/  UART_IO_BAR_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int bootrom_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct inout_port*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  lpc_uart_intr_assert ; 
 int /*<<< orphan*/  lpc_uart_intr_deassert ; 
 int /*<<< orphan*/  lpc_uart_io_handler ; 
 struct lpc_uart_softc* lpc_uart_softc ; 
 int /*<<< orphan*/  pci_irq_reserve (int /*<<< orphan*/ ) ; 
 int register_inout (struct inout_port*) ; 
 int /*<<< orphan*/ * romfile ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uart_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpc_uart_softc*) ; 
 scalar_t__ uart_legacy_alloc (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uart_set_backend (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
lpc_init(void)
{
	struct lpc_uart_softc *sc;
	struct inout_port iop;
	int unit, error;

    if (romfile != NULL) {
        error = bootrom_init(romfile);
        if (error)
            return error;
    }

	/* COM1 and COM2 */
	for (unit = 0; unit < LPC_UART_NUM; unit++) {
		sc = &lpc_uart_softc[unit];

		if (uart_legacy_alloc(unit, &sc->iobase, &sc->irq) != 0) {
			fprintf(stderr, "Unable to allocate resources for "
			    "LPC device %s\n", sc->name);
			return (-1);
		}
		pci_irq_reserve(sc->irq);

		sc->uart_softc = uart_init(lpc_uart_intr_assert,
				    lpc_uart_intr_deassert, sc);

		if (uart_set_backend(sc->uart_softc, sc->opts, sc->name) != 0) {
			fprintf(stderr, "Unable to initialize backend '%s' "
			    "for LPC device %s\n", sc->opts, sc->name);
			return (-1);
		}

		bzero(&iop, sizeof(struct inout_port));
		iop.name = sc->name;
		iop.port = sc->iobase;
		iop.size = UART_IO_BAR_SIZE;
		iop.flags = IOPORT_F_INOUT;
		iop.handler = lpc_uart_io_handler;
		iop.arg = sc;

		error = register_inout(&iop);
		assert(error == 0);
		sc->enabled = 1;
	}

	return (0);
}