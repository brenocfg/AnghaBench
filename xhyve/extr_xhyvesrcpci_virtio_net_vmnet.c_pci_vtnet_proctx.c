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
typedef  int /*<<< orphan*/  uint16_t ;
struct vqueue_info {int dummy; } ;
struct pci_vtnet_softc {int dummy; } ;
struct iovec {scalar_t__ iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int VTNET_MAXSEGS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pci_vtnet_tap_tx (struct pci_vtnet_softc*,struct iovec*,int,int) ; 
 int vq_getchain (struct vqueue_info*,int /*<<< orphan*/ *,struct iovec*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_relchain (struct vqueue_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_vtnet_proctx(struct pci_vtnet_softc *sc, struct vqueue_info *vq)
{
	struct iovec iov[VTNET_MAXSEGS + 1];
	int i, n;
	int plen, tlen;
	uint16_t idx;

	/*
	 * Obtain chain of descriptors.  The first one is
	 * really the header descriptor, so we need to sum
	 * up two lengths: packet length and transfer length.
	 */
	n = vq_getchain(vq, &idx, iov, VTNET_MAXSEGS, NULL);
	assert(n >= 1 && n <= VTNET_MAXSEGS);
	plen = 0;
	tlen = (int) iov[0].iov_len;
	for (i = 1; i < n; i++) {
		plen += iov[i].iov_len;
		tlen += iov[i].iov_len;
	}

	DPRINTF(("virtio: packet send, %d bytes, %d segs\n\r", plen, n));
	pci_vtnet_tap_tx(sc, &iov[1], n - 1, plen);

	/* chain is processed, release it and set tlen */
	vq_relchain(vq, idx, ((uint32_t) tlen));
}