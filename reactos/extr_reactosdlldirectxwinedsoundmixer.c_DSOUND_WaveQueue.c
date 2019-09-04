#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WAVEHDR ;
struct TYPE_3__ {size_t pwplay; size_t pwqueue; size_t helfrags; size_t fraglen; size_t prebuf; size_t mixpos; int /*<<< orphan*/  mixlock; int /*<<< orphan*/ * pwave; int /*<<< orphan*/  hwo; } ;
typedef  TYPE_1__ DirectSoundDevice ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  waveOutWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void DSOUND_WaveQueue(DirectSoundDevice *device, BOOL force)
{
	DWORD prebuf_frags, wave_writepos, wave_fragpos, i;
	TRACE("(%p)\n", device);

	/* calculate the current wave frag position */
	wave_fragpos = (device->pwplay + device->pwqueue) % device->helfrags;

	/* calculate the current wave write position */
	wave_writepos = wave_fragpos * device->fraglen;

	TRACE("wave_fragpos = %i, wave_writepos = %i, pwqueue = %i, prebuf = %i\n",
		wave_fragpos, wave_writepos, device->pwqueue, device->prebuf);

	if (!force)
	{
		/* check remaining prebuffered frags */
		prebuf_frags = device->mixpos / device->fraglen;
		if (prebuf_frags == device->helfrags)
			--prebuf_frags;
		TRACE("wave_fragpos = %d, mixpos_frags = %d\n", wave_fragpos, prebuf_frags);
		if (prebuf_frags < wave_fragpos)
			prebuf_frags += device->helfrags;
		prebuf_frags -= wave_fragpos;
		TRACE("wanted prebuf_frags = %d\n", prebuf_frags);
	}
	else
		/* buffer the maximum amount of frags */
		prebuf_frags = device->prebuf;

	/* limit to the queue we have left */
	if ((prebuf_frags + device->pwqueue) > device->prebuf)
		prebuf_frags = device->prebuf - device->pwqueue;

	TRACE("prebuf_frags = %i\n", prebuf_frags);

	/* adjust queue */
	device->pwqueue += prebuf_frags;

	/* get out of CS when calling the wave system */
	LeaveCriticalSection(&(device->mixlock));
	/* **** */

	/* queue up the new buffers */
	for(i=0; i<prebuf_frags; i++){
		TRACE("queueing wave buffer %i\n", wave_fragpos);
		waveOutWrite(device->hwo, &device->pwave[wave_fragpos], sizeof(WAVEHDR));
		wave_fragpos++;
		wave_fragpos %= device->helfrags;
	}

	/* **** */
	EnterCriticalSection(&(device->mixlock));

	TRACE("queue now = %i\n", device->pwqueue);
}