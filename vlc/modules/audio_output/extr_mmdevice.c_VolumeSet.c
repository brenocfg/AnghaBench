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
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  work; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int VolumeSetLocked (TYPE_1__*,float) ; 
 int /*<<< orphan*/  WakeConditionVariable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int VolumeSet(audio_output_t *aout, float vol)
{
    aout_sys_t *sys = aout->sys;

    EnterCriticalSection(&sys->lock);
    int ret = VolumeSetLocked(aout, vol);
    WakeConditionVariable(&sys->work);
    LeaveCriticalSection(&sys->lock);
    return ret;
}