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
typedef  int uint16_t ;
struct vqueue_info {int vq_save_used; TYPE_2__* vq_avail; TYPE_1__* vq_used; struct virtio_softc* vq_vs; } ;
struct virtio_softc {int vs_negotiated_caps; } ;
struct TYPE_4__ {int va_flags; } ;
struct TYPE_3__ {int vu_idx; } ;

/* Variables and functions */
 int VIRTIO_F_NOTIFY_ON_EMPTY ; 
 int VIRTIO_RING_F_EVENT_IDX ; 
 int VQ_USED_EVENT_IDX (struct vqueue_info*) ; 
 int VRING_AVAIL_F_NO_INTERRUPT ; 
 int /*<<< orphan*/  vq_interrupt (struct virtio_softc*,struct vqueue_info*) ; 

void
vq_endchains(struct vqueue_info *vq, int used_all_avail)
{
	struct virtio_softc *vs;
	uint16_t event_idx, new_idx, old_idx;
	int intr;

	/*
	 * Interrupt generation: if we're using EVENT_IDX,
	 * interrupt if we've crossed the event threshold.
	 * Otherwise interrupt is generated if we added "used" entries,
	 * but suppressed by VRING_AVAIL_F_NO_INTERRUPT.
	 *
	 * In any case, though, if NOTIFY_ON_EMPTY is set and the
	 * entire avail was processed, we need to interrupt always.
	 */
	vs = vq->vq_vs;
	old_idx = vq->vq_save_used;
	vq->vq_save_used = new_idx = vq->vq_used->vu_idx;
	if (used_all_avail &&
	    (vs->vs_negotiated_caps & VIRTIO_F_NOTIFY_ON_EMPTY))
		intr = 1;
	else if (vs->vs_negotiated_caps & VIRTIO_RING_F_EVENT_IDX) {
		event_idx = VQ_USED_EVENT_IDX(vq);
		/*
		 * This calculation is per docs and the kernel
		 * (see src/sys/dev/virtio/virtio_ring.h).
		 */
		intr = (uint16_t)(new_idx - event_idx - 1) <
			(uint16_t)(new_idx - old_idx);
	} else {
		intr = new_idx != old_idx &&
		    !(vq->vq_avail->va_flags & VRING_AVAIL_F_NO_INTERRUPT);
	}
	if (intr)
		vq_interrupt(vs, vq);
}