#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_7__ {int /*<<< orphan*/  device_events; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/ * requested_device; int /*<<< orphan*/ * it; } ;
typedef  TYPE_2__ aout_sys_t ;
typedef  int /*<<< orphan*/  IMMDeviceEnumerator ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DevicesEnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterMTA () ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_RegisterEndpointNotificationCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_UnregisterEndpointNotificationCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveMTA () ; 
 int /*<<< orphan*/  MMSession (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMThread_DevicesEnum_Added ; 
 int /*<<< orphan*/  SleepConditionVariableCS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *MMThread(void *data)
{
    audio_output_t *aout = data;
    aout_sys_t *sys = aout->sys;
    IMMDeviceEnumerator *it = sys->it;

    EnterMTA();
    IMMDeviceEnumerator_RegisterEndpointNotificationCallback(it,
                                                          &sys->device_events);
    HRESULT hr = DevicesEnum(it, MMThread_DevicesEnum_Added, aout);
    if (FAILED(hr))
        msg_Warn(aout, "cannot enumerate audio endpoints (error 0x%lX)", hr);

    EnterCriticalSection(&sys->lock);

    do
        if (sys->requested_device == NULL || FAILED(MMSession(aout, it)))
            SleepConditionVariableCS(&sys->work, &sys->lock, INFINITE);
    while (sys->it != NULL);

    LeaveCriticalSection(&sys->lock);

    IMMDeviceEnumerator_UnregisterEndpointNotificationCallback(it,
                                                          &sys->device_events);
    IMMDeviceEnumerator_Release(it);
    LeaveMTA();
    return NULL;
}