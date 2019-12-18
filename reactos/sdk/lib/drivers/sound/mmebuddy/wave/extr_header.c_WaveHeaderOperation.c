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
struct TYPE_3__ {int /*<<< orphan*/  Header; int /*<<< orphan*/  Function; } ;
typedef  TYPE_1__ THREADED_WAVEHEADER_PARAMETERS ;
typedef  int /*<<< orphan*/  PWAVEHDR ;
typedef  int /*<<< orphan*/  PSOUND_DEVICE_INSTANCE ;
typedef  int /*<<< orphan*/  MMWAVEHEADER_FUNC ;
typedef  int /*<<< orphan*/  MMRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CallSoundThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  WaveHeaderOperationInSoundThread ; 

MMRESULT
WaveHeaderOperation(
    MMWAVEHEADER_FUNC Function,
    PSOUND_DEVICE_INSTANCE SoundDeviceInstance,
    PWAVEHDR Header)
{
    THREADED_WAVEHEADER_PARAMETERS Parameters;

    Parameters.Function = Function;
    Parameters.Header = Header;

    return CallSoundThread(SoundDeviceInstance,
                           WaveHeaderOperationInSoundThread,
                           &Parameters);
}