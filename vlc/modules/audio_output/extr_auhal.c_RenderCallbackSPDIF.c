#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_16__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_17__ {size_t i_stream_index; } ;
typedef  TYPE_3__ aout_sys_t ;
struct TYPE_18__ {int mFlags; int /*<<< orphan*/  mHostTime; TYPE_1__* mBuffers; } ;
struct TYPE_15__ {size_t mDataByteSize; int /*<<< orphan*/ * mData; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  TYPE_4__ AudioTimeStamp ;
typedef  TYPE_4__ const* AudioDeviceID ;
typedef  TYPE_4__ AudioBufferList ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (TYPE_4__ const*) ; 
 int /*<<< orphan*/  ca_Render (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int kAudioTimeStampHostTimeValid ; 
 int /*<<< orphan*/  noErr ; 

__attribute__((used)) static OSStatus
RenderCallbackSPDIF(AudioDeviceID inDevice, const AudioTimeStamp * inNow,
                    const AudioBufferList * inInputData,
                    const AudioTimeStamp * inInputTime,
                    AudioBufferList * outOutputData,
                    const AudioTimeStamp * inOutputTime, void *p_data)
{
    VLC_UNUSED(inNow);
    VLC_UNUSED(inDevice);
    VLC_UNUSED(inInputData);
    VLC_UNUSED(inInputTime);
    VLC_UNUSED(inOutputTime);

    audio_output_t * p_aout = p_data;
    aout_sys_t *p_sys = p_aout->sys;
    uint8_t *p_output = outOutputData->mBuffers[p_sys->i_stream_index].mData;
    size_t i_size = outOutputData->mBuffers[p_sys->i_stream_index].mDataByteSize;

    uint64_t i_host_time = (inNow->mFlags & kAudioTimeStampHostTimeValid)
                         ? inNow->mHostTime : 0;

    ca_Render(p_aout, 0, i_host_time, p_output, i_size);

    return noErr;
}