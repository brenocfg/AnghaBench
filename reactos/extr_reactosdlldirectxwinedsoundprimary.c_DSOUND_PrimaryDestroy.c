#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mixlock; int /*<<< orphan*/ * pwfx; int /*<<< orphan*/ * pwave; scalar_t__ hwbuf; scalar_t__ driver; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DirectSoundDevice ;

/* Variables and functions */
 int /*<<< orphan*/  DSOUND_PrimaryClose (TYPE_1__*) ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IDsDriverBuffer_Release (scalar_t__) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

HRESULT DSOUND_PrimaryDestroy(DirectSoundDevice *device)
{
	TRACE("(%p)\n", device);

	/* **** */
	EnterCriticalSection(&(device->mixlock));

	DSOUND_PrimaryClose(device);
	if (device->driver) {
		if (device->hwbuf) {
			if (IDsDriverBuffer_Release(device->hwbuf) == 0)
				device->hwbuf = 0;
		}
	} else
                HeapFree(GetProcessHeap(),0,device->pwave);
        HeapFree(GetProcessHeap(),0,device->pwfx);
        device->pwfx=NULL;

	LeaveCriticalSection(&(device->mixlock));
	/* **** */

	return DS_OK;
}