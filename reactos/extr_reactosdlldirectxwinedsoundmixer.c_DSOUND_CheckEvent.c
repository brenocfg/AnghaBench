#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nrofnotifies; int buflen; scalar_t__ state; TYPE_1__* notifies; } ;
struct TYPE_5__ {int dwOffset; TYPE_2__ const* hEventNotify; } ;
typedef  TYPE_1__* LPDSBPOSITIONNOTIFY ;
typedef  TYPE_2__ IDirectSoundBufferImpl ;
typedef  int DWORD ;

/* Variables and functions */
 int DSBPN_OFFSETSTOP ; 
 scalar_t__ STATE_STOPPED ; 
 int /*<<< orphan*/  SetEvent (TYPE_2__ const*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

void DSOUND_CheckEvent(const IDirectSoundBufferImpl *dsb, DWORD playpos, int len)
{
	int			i;
	DWORD			offset;
	LPDSBPOSITIONNOTIFY	event;
	TRACE("(%p,%d)\n",dsb,len);

	if (dsb->nrofnotifies == 0)
		return;

	TRACE("(%p) buflen = %d, playpos = %d, len = %d\n",
		dsb, dsb->buflen, playpos, len);
	for (i = 0; i < dsb->nrofnotifies ; i++) {
		event = dsb->notifies + i;
		offset = event->dwOffset;
		TRACE("checking %d, position %d, event = %p\n",
			i, offset, event->hEventNotify);
		/* DSBPN_OFFSETSTOP has to be the last element. So this is */
		/* OK. [Inside DirectX, p274] */
		/* Windows does not seem to enforce this, and some apps rely */
		/* on that, so we can't stop there. */
		/*  */
		/* This also means we can't sort the entries by offset, */
		/* because DSBPN_OFFSETSTOP == -1 */
		if (offset == DSBPN_OFFSETSTOP) {
			if (dsb->state == STATE_STOPPED) {
				SetEvent(event->hEventNotify);
				TRACE("signalled event %p (%d)\n", event->hEventNotify, i);
			}
                        continue;
		}
		if ((playpos + len) >= dsb->buflen) {
			if ((offset < ((playpos + len) % dsb->buflen)) ||
			    (offset >= playpos)) {
				TRACE("signalled event %p (%d)\n", event->hEventNotify, i);
				SetEvent(event->hEventNotify);
			}
		} else {
			if ((offset >= playpos) && (offset < (playpos + len))) {
				TRACE("signalled event %p (%d)\n", event->hEventNotify, i);
				SetEvent(event->hEventNotify);
			}
		}
	}
}