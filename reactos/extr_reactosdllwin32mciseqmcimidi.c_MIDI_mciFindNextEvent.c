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
typedef  size_t WORD ;
struct TYPE_5__ {size_t nTracks; TYPE_2__* tracks; } ;
typedef  TYPE_1__ WINE_MCIMIDI ;
struct TYPE_6__ {scalar_t__ wStatus; int dwEventPulse; } ;
typedef  TYPE_2__ MCI_MIDITRACK ;
typedef  int* LPDWORD ;

/* Variables and functions */

__attribute__((used)) static MCI_MIDITRACK*	MIDI_mciFindNextEvent(WINE_MCIMIDI* wmm, LPDWORD hiPulse)
{
    WORD		cnt, nt;
    MCI_MIDITRACK*	mmt;

    *hiPulse = 0xFFFFFFFFul;
    cnt = 0xFFFFu;
    for (nt = 0; nt < wmm->nTracks; nt++) {
	mmt = &wmm->tracks[nt];

	if (mmt->wStatus == 0)
	    continue;
	if (mmt->dwEventPulse < *hiPulse) {
	    *hiPulse = mmt->dwEventPulse;
	    cnt = nt;
	}
    }
    return (cnt == 0xFFFFu) ? 0 /* no more event on all tracks */
	: &wmm->tracks[cnt];
}