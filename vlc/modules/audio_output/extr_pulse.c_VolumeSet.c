#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pa_volume_t ;
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_8__ {int /*<<< orphan*/  channels; } ;
typedef  TYPE_1__ pa_sample_spec ;
typedef  int /*<<< orphan*/  pa_operation ;
typedef  int /*<<< orphan*/  pa_cvolume ;
struct TYPE_9__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_10__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  context; int /*<<< orphan*/  cvolume; scalar_t__ volume_force; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_3__ aout_sys_t ;

/* Variables and functions */
 scalar_t__ PA_VOLUME_MAX ; 
 float PA_VOLUME_NORM ; 
 int /*<<< orphan*/  aout_VolumeReport (TYPE_2__*,float) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ lroundf (float) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * pa_context_set_sink_input_volume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_cvolume_scale (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  pa_cvolume_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  pa_cvolume_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_stream_get_index (int /*<<< orphan*/ *) ; 
 TYPE_1__* pa_stream_get_sample_spec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_sw_cvolume_multiply_scalar (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int VolumeSet(audio_output_t *aout, float vol)
{
    aout_sys_t *sys = aout->sys;
    pa_stream *s = sys->stream;
    pa_operation *op;
    pa_volume_t volume;

    /* VLC provides the software volume so convert directly to PulseAudio
     * software volume, pa_volume_t. This is not a linear amplification factor
     * so do not use PulseAudio linear amplification! */
    vol *= PA_VOLUME_NORM;
    if (unlikely(vol >= (float)PA_VOLUME_MAX))
        volume = PA_VOLUME_MAX;
    else
        volume = lroundf(vol);

    if (s == NULL)
    {
        sys->volume_force = volume;
        aout_VolumeReport(aout, (float)volume / (float)PA_VOLUME_NORM);
        return 0;
    }

    pa_threaded_mainloop_lock(sys->mainloop);

    if (!pa_cvolume_valid(&sys->cvolume))
    {
        const pa_sample_spec *ss = pa_stream_get_sample_spec(s);

        msg_Warn(aout, "balance clobbered by volume change");
        pa_cvolume_set(&sys->cvolume, ss->channels, PA_VOLUME_NORM);
    }

    /* Preserve the balance (VLC does not support it). */
    pa_cvolume cvolume = sys->cvolume;
    pa_cvolume_scale(&cvolume, PA_VOLUME_NORM);
    pa_sw_cvolume_multiply_scalar(&cvolume, &cvolume, volume);
    assert(pa_cvolume_valid(&cvolume));

    op = pa_context_set_sink_input_volume(sys->context, pa_stream_get_index(s),
                                          &cvolume, NULL, NULL);
    if (likely(op != NULL))
        pa_operation_unref(op);
    pa_threaded_mainloop_unlock(sys->mainloop);
    return likely(op != NULL) ? 0 : -1;
}