#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  audio_sample_format_t ;
struct TYPE_12__ {int /*<<< orphan*/  headphones; } ;
struct TYPE_13__ {TYPE_1__ current_sink_info; TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_14__ {int /*<<< orphan*/ * au_unit; int /*<<< orphan*/  b_mute; int /*<<< orphan*/  f_volume; int /*<<< orphan*/  i_selected_dev; } ;
typedef  TYPE_3__ aout_sys_t ;
typedef  int /*<<< orphan*/  UInt32 ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/  AudioObjectID ;
typedef  int /*<<< orphan*/  AudioChannelLayout ;

/* Variables and functions */
 int /*<<< orphan*/  AudioComponentInstanceDispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AudioDeviceIsAHeadphone (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ AudioOutputUnitStart (int /*<<< orphan*/ *) ; 
 scalar_t__ AudioUnitGetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ AudioUnitGetPropertyInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ AudioUnitSetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MuteSet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VolumeSet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WarnConfiguration (TYPE_2__*) ; 
 scalar_t__ aout_FormatNbChannels (int /*<<< orphan*/ *) ; 
 int au_Initialize (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * au_NewOutputInstance (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_Uninitialize (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ca_LogErr (char*) ; 
 int /*<<< orphan*/  ca_LogWarn (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kAudioDevicePropertyPreferredChannelLayout ; 
 int /*<<< orphan*/  kAudioOutputUnitProperty_CurrentDevice ; 
 int /*<<< orphan*/  kAudioUnitScope_Global ; 
 int /*<<< orphan*/  kAudioUnitScope_Output ; 
 int /*<<< orphan*/  kAudioUnitSubType_HALOutput ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ noErr ; 

__attribute__((used)) static int
StartAnalog(audio_output_t *p_aout, audio_sample_format_t *fmt)
{
    aout_sys_t                  *p_sys = p_aout->sys;
    OSStatus                    err = noErr;
    UInt32                      i_param_size;
    AudioChannelLayout          *layout = NULL;

    if (aout_FormatNbChannels(fmt) == 0)
        return VLC_EGENERIC;

    p_sys->au_unit = au_NewOutputInstance(p_aout, kAudioUnitSubType_HALOutput);
    if (p_sys->au_unit == NULL)
        return VLC_EGENERIC;

    p_aout->current_sink_info.headphones = AudioDeviceIsAHeadphone(p_aout, p_sys->i_selected_dev);

    /* Set the device we will use for this output unit */
    err = AudioUnitSetProperty(p_sys->au_unit,
                               kAudioOutputUnitProperty_CurrentDevice,
                               kAudioUnitScope_Global, 0,
                               &p_sys->i_selected_dev, sizeof(AudioObjectID));

    if (err != noErr)
    {
        ca_LogErr("cannot select audio output device, PCM output failed");
        goto error;
    }

    /* Get the channel layout of the device side of the unit (vlc -> unit ->
     * device) */
    err = AudioUnitGetPropertyInfo(p_sys->au_unit,
                                   kAudioDevicePropertyPreferredChannelLayout,
                                   kAudioUnitScope_Output, 0, &i_param_size,
                                   NULL);
    if (err == noErr)
    {
        layout = (AudioChannelLayout *)malloc(i_param_size);
        if (layout == NULL)
            goto error;

        OSStatus err =
            AudioUnitGetProperty(p_sys->au_unit,
                                 kAudioDevicePropertyPreferredChannelLayout,
                                 kAudioUnitScope_Output, 0, layout,
                                 &i_param_size);
        if (err != noErr)
            goto error;
    }
    else
        ca_LogWarn("device driver does not support "
                   "kAudioDevicePropertyPreferredChannelLayout - using stereo");

    /* Do the last VLC aout setups */
    bool warn_configuration;
    int ret = au_Initialize(p_aout, p_sys->au_unit, fmt, layout, 0,
                            &warn_configuration);
    if (ret != VLC_SUCCESS)
        goto error;

    err = AudioOutputUnitStart(p_sys->au_unit);
    if (err != noErr)
    {
        ca_LogErr("AudioUnitStart failed");
        au_Uninitialize(p_aout, p_sys->au_unit);
        goto error;
    }

    /* Set volume for output unit */
    VolumeSet(p_aout, p_sys->f_volume);
    MuteSet(p_aout, p_sys->b_mute);

    free(layout);

    if (warn_configuration)
        WarnConfiguration(p_aout);

    return VLC_SUCCESS;
error:
    AudioComponentInstanceDispose(p_sys->au_unit);
    free(layout);
    return VLC_EGENERIC;
}