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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {float* pf_gain; float* pf_peak; scalar_t__* pb_peak; scalar_t__* pb_gain; } ;
typedef  TYPE_1__ audio_replay_gain_t ;

/* Variables and functions */
 unsigned int AUDIO_REPLAY_GAIN_ALBUM ; 
 unsigned int AUDIO_REPLAY_GAIN_MAX ; 
 unsigned int AUDIO_REPLAY_GAIN_TRACK ; 
 float fminf (float,float) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 float powf (float,float) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 float var_InheritFloat (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static float aout_ReplayGainSelect(vlc_object_t *obj, const char *str,
                                   const audio_replay_gain_t *replay_gain)
{
    unsigned mode = AUDIO_REPLAY_GAIN_MAX;

    if (likely(str != NULL))
    {   /* Find selectrf mode */
        if (!strcmp (str, "track"))
            mode = AUDIO_REPLAY_GAIN_TRACK;
        else
        if (!strcmp (str, "album"))
            mode = AUDIO_REPLAY_GAIN_ALBUM;
    }

    /* */
    float multiplier;

    if (mode == AUDIO_REPLAY_GAIN_MAX)
    {
        multiplier = 1.f;
    }
    else
    {
        float gain;

        /* If the selectrf mode is not available, prefer the other one */
        if (!replay_gain->pb_gain[mode] && replay_gain->pb_gain[!mode])
            mode = !mode;

        if (replay_gain->pb_gain[mode])
            gain = replay_gain->pf_gain[mode]
                 + var_InheritFloat (obj, "audio-replay-gain-preamp");
        else
            gain = var_InheritFloat (obj, "audio-replay-gain-default");

        multiplier = powf (10.f, gain / 20.f);

        if (var_InheritBool (obj, "audio-replay-gain-peak-protection"))
            multiplier = fminf (multiplier, replay_gain->pb_peak[mode]
                                            ? 1.f / replay_gain->pf_peak[mode]
                                            : 1.f);
    }

    /* Command line / configuration gain */
    multiplier *= var_InheritFloat (obj, "gain");

    return multiplier;
}