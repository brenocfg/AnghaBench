#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_12__ {scalar_t__ (* time_get ) (TYPE_2__*,scalar_t__*) ;} ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_11__ {int /*<<< orphan*/  rate; int /*<<< orphan*/  clock; scalar_t__ discontinuity; } ;
struct TYPE_13__ {TYPE_1__ sync; } ;
typedef  TYPE_3__ aout_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_DecSilence (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  aout_RequestRetiming (TYPE_2__*,scalar_t__,scalar_t__) ; 
 TYPE_3__* aout_owner (TYPE_2__*) ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__*) ; 
 scalar_t__ stub2 (TYPE_2__*,scalar_t__*) ; 
 scalar_t__ vlc_clock_ConvertToSystem (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aout_DecSynchronize(audio_output_t *aout, vlc_tick_t system_now,
                                vlc_tick_t dec_pts)
{
    /**
     * Depending on the drift between the actual and intended playback times,
     * the audio core may ignore the drift, trigger upsampling or downsampling,
     * insert silence or even discard samples.
     * Future VLC versions may instead adjust the input rate.
     *
     * The audio output plugin is responsible for estimating its actual
     * playback time, or rather the estimated time when the next sample will
     * be played. (The actual playback time is always the current time, that is
     * to say vlc_tick_now(). It is not an useful statistic.)
     *
     * Most audio output plugins can estimate the delay until playback of
     * the next sample to be written to the buffer, or equally the time until
     * all samples in the buffer will have been played. Then:
     *    pts = vlc_tick_now() + delay
     */
    aout_owner_t *owner = aout_owner (aout);
    vlc_tick_t delay;

    if (aout->time_get(aout, &delay) != 0)
        return; /* nothing can be done if timing is unknown */

    if (owner->sync.discontinuity)
    {
        /* Chicken-egg situation for most aout modules that can't be started
         * deferred (all except PulseAudio). These modules will start to play
         * data immediately and ignore the given play_date (that take the clock
         * jitter into account). We don't want to let aout_RequestRetiming()
         * handle the first silence (from the "Early audio output" case) since
         * this function will first update the clock without taking the jitter
         * into account. Therefore, we manually insert silence that correspond
         * to the clock jitter value before updating the clock.
         */
        vlc_tick_t play_date =
            vlc_clock_ConvertToSystem(owner->sync.clock, system_now + delay,
                                      dec_pts, owner->sync.rate);
        vlc_tick_t jitter = play_date - system_now;
        if (jitter > 0)
        {
            aout_DecSilence (aout, jitter, dec_pts - delay);
            if (aout->time_get(aout, &delay) != 0)
                return;
        }
    }

    aout_RequestRetiming(aout, system_now + delay, dec_pts);
}