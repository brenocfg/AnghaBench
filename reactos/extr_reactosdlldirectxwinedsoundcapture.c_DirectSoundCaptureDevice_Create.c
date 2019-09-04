#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* DebugInfo; } ;
struct TYPE_8__ {int ref; TYPE_4__ lock; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ DirectSoundCaptureDevice ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_4__*) ; 
 int /*<<< orphan*/  STATE_STOPPED ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__**) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static HRESULT DirectSoundCaptureDevice_Create(
    DirectSoundCaptureDevice ** ppDevice)
{
    DirectSoundCaptureDevice * device;
    TRACE("(%p)\n", ppDevice);

    /* Allocate memory */
    device = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(DirectSoundCaptureDevice));

    if (device == NULL) {
	WARN("out of memory\n");
        return DSERR_OUTOFMEMORY;
    }

    device->ref = 1;
    device->state = STATE_STOPPED;

    InitializeCriticalSection( &(device->lock) );
    device->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": DirectSoundCaptureDevice.lock");

    *ppDevice = device;

    return DS_OK;
}