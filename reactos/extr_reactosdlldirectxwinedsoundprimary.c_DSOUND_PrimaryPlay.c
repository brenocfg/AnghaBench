#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hwo; scalar_t__ hwbuf; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ DirectSoundDevice ;

/* Variables and functions */
 int /*<<< orphan*/  DSBPLAY_LOOPING ; 
 scalar_t__ DS_OK ; 
 scalar_t__ IDsDriverBuffer_Play (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ mmErr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveOutRestart (int /*<<< orphan*/ ) ; 

HRESULT DSOUND_PrimaryPlay(DirectSoundDevice *device)
{
	HRESULT err = DS_OK;
	TRACE("(%p)\n", device);

	if (device->hwbuf) {
		err = IDsDriverBuffer_Play(device->hwbuf, 0, 0, DSBPLAY_LOOPING);
		if (err != DS_OK)
			WARN("IDsDriverBuffer_Play failed\n");
	} else {
		err = mmErr(waveOutRestart(device->hwo));
		if (err != DS_OK)
			WARN("waveOutRestart failed\n");
	}

	return err;
}