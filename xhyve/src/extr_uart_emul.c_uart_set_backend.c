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
struct TYPE_2__ {int fd; int opened; char* name; } ;
struct uart_softc {TYPE_1__ tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int STDIN_FILENO ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int grantpt (int) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* ptsname (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  uart_opentty (struct uart_softc*) ; 
 int uart_stdio ; 
 scalar_t__ uart_tty_backend (struct uart_softc*,char const*) ; 
 int unlockpt (int) ; 

int
uart_set_backend(struct uart_softc *sc, const char *backend, const char *devname)
{
	int retval;
	int ptyfd;
	char *ptyname;

	retval = -1;

	if (backend == NULL)
		return (0);

	if (strcmp("stdio", backend) == 0 && !uart_stdio) {
		sc->tty.fd = STDIN_FILENO;
		sc->tty.opened = true;
		uart_stdio = true;
		retval = fcntl(sc->tty.fd, F_SETFL, O_NONBLOCK);
	} else if (strcmp("autopty", backend) == 0) {
		if ((ptyfd = open("/dev/ptmx", O_RDWR | O_NONBLOCK)) == -1) {
			fprintf(stderr, "error opening /dev/ptmx char device");
			return retval;
		}

		if ((ptyname = ptsname(ptyfd)) == NULL) {
			perror("ptsname: error getting name for slave pseudo terminal");
			return retval;
		}

		if ((retval = grantpt(ptyfd)) == -1) {
			perror("error setting up ownership and permissions on slave pseudo terminal");
			return retval;
		}

		if ((retval = unlockpt(ptyfd)) == -1) {
			perror("error unlocking slave pseudo terminal, to allow its usage");
			return retval;
		}

		fprintf(stdout, "%s connected to %s\n", devname, ptyname);
		sc->tty.fd = ptyfd;
		sc->tty.name = ptyname;
		sc->tty.opened = true;
		retval = 0;
	} else if (uart_tty_backend(sc, backend) == 0) {
		retval = 0;
	}

	if (retval == 0)
		uart_opentty(sc);

	return (retval);
}