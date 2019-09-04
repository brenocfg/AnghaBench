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
struct pci_vtnet_softc {int /*<<< orphan*/  vms; } ;
struct iovec {char* iov_base; size_t iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmn_write (int /*<<< orphan*/ ,struct iovec*,int) ; 

__attribute__((used)) static void
pci_vtnet_tap_tx(struct pci_vtnet_softc *sc, struct iovec *iov, int iovcnt,
		 int len)
{
	static char pad[60]; /* all zero bytes */

	if (!sc->vms)
		return;

	/*
	 * If the length is < 60, pad out to that and add the
	 * extra zero'd segment to the iov. It is guaranteed that
	 * there is always an extra iov available by the caller.
	 */
	if (len < 60) {
		iov[iovcnt].iov_base = pad;
		iov[iovcnt].iov_len = (size_t) (60 - len);
		iovcnt++;
	}
	vmn_write(sc->vms, iov, iovcnt);
}