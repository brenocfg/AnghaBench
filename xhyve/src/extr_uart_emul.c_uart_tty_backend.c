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
struct TYPE_2__ {int fd; int opened; } ;
struct uart_softc {TYPE_1__ tty; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDWR ; 
 scalar_t__ isatty (int) ; 
 int open (char const*,int) ; 

__attribute__((used)) static int
uart_tty_backend(struct uart_softc *sc, const char *backend)
{
	int fd;
	int retval;

	retval = -1;

	fd = open(backend, O_RDWR | O_NONBLOCK);
	if (fd > 0 && isatty(fd)) {
		sc->tty.fd = fd;
		sc->tty.opened = true;
		retval = 0;
	}

	return (retval);
}