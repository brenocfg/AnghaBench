#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_10__ {TYPE_1__* DebugInfo; } ;
struct TYPE_8__ {size_t dnDevNode; } ;
struct TYPE_9__ {TYPE_2__ drvdesc; TYPE_6__ lock; struct TYPE_9__* pwfx; scalar_t__ driver; scalar_t__ capture_buffer; int /*<<< orphan*/  ref; } ;
struct TYPE_7__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  LPDIRECTSOUNDCAPTUREBUFFER8 ;
typedef  TYPE_3__ DirectSoundCaptureDevice ;

/* Variables and functions */
 int /*<<< orphan*/ ** DSOUND_capture ; 
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_6__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IDirectSoundCaptureBufferImpl_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDsCaptureDriver_Close (scalar_t__) ; 
 int /*<<< orphan*/  IDsCaptureDriver_Release (scalar_t__) ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static ULONG DirectSoundCaptureDevice_Release(
    DirectSoundCaptureDevice * device)
{
    ULONG ref = InterlockedDecrement(&(device->ref));
    TRACE("(%p) ref was %d\n", device, ref + 1);

    if (!ref) {
        TRACE("deleting object\n");
        if (device->capture_buffer)
            IDirectSoundCaptureBufferImpl_Release(
		(LPDIRECTSOUNDCAPTUREBUFFER8) device->capture_buffer);

        if (device->driver) {
            IDsCaptureDriver_Close(device->driver);
            IDsCaptureDriver_Release(device->driver);
        }

        HeapFree(GetProcessHeap(), 0, device->pwfx);
        device->lock.DebugInfo->Spare[0] = 0;
        DeleteCriticalSection( &(device->lock) );
        DSOUND_capture[device->drvdesc.dnDevNode] = NULL;
        HeapFree(GetProcessHeap(), 0, device);
	TRACE("(%p) released\n", device);
    }
    return ref;
}