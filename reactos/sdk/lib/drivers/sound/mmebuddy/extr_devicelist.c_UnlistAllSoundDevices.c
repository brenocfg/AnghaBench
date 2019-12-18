#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ MMRESULT ;
typedef  scalar_t__ MMDEVICE_TYPE ;

/* Variables and functions */
 scalar_t__ MAX_SOUND_DEVICE_TYPE ; 
 scalar_t__ MIN_SOUND_DEVICE_TYPE ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  SND_ASSERT (int) ; 
 int /*<<< orphan*/  SND_TRACE (char*) ; 
 scalar_t__ UnlistSoundDevices (scalar_t__) ; 

VOID
UnlistAllSoundDevices()
{
    MMDEVICE_TYPE Type;

    SND_TRACE(L"Unlisting all sound devices\n");

    for ( Type = MIN_SOUND_DEVICE_TYPE; Type <= MAX_SOUND_DEVICE_TYPE; ++ Type )
    {
        MMRESULT Result;
        Result = UnlistSoundDevices(Type);
        SND_ASSERT( Result == MMSYSERR_NOERROR );
    }
}