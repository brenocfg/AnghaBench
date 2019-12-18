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
typedef  int /*<<< orphan*/  audio_output_t ;
typedef  int /*<<< orphan*/  AudioDeviceID ;

/* Variables and functions */
 int AO_GETPROP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AudioStreamID ; 
 int FALSE ; 
 int TRUE ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  kAudioDevicePropertyStreams ; 
 int /*<<< orphan*/  kAudioObjectPropertyScopeOutput ; 

__attribute__((used)) static int
AudioDeviceHasOutput(audio_output_t *p_aout, AudioDeviceID i_dev_id)
{
    size_t i_streams;
    int ret = AO_GETPROP(i_dev_id, AudioStreamID, &i_streams, NULL,
                          kAudioDevicePropertyStreams,
                          kAudioObjectPropertyScopeOutput);
    if (ret != VLC_SUCCESS || i_streams == 0)
        return FALSE;

    return TRUE;
}