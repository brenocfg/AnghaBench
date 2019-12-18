#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  audio_replay_gain_t ;
struct TYPE_5__ {float output_factor; int /*<<< orphan*/  replay_gain; int /*<<< orphan*/ * module; } ;
typedef  TYPE_1__ aout_volume_t ;

/* Variables and functions */
 int /*<<< orphan*/  ReplayGainCallback ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_AddCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  var_TriggerCallback (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 

aout_volume_t *aout_volume_New(vlc_object_t *parent,
                               const audio_replay_gain_t *gain)
{
    aout_volume_t *vol = vlc_custom_create(parent, sizeof (aout_volume_t),
                                           "volume");
    if (unlikely(vol == NULL))
        return NULL;
    vol->module = NULL;
    vol->output_factor = 1.f;

    //audio_volume_t *obj = &vol->object;

    /* Gain */
    if (gain != NULL)
        memcpy(&vol->replay_gain, gain, sizeof (vol->replay_gain));
    else
        memset(&vol->replay_gain, 0, sizeof (vol->replay_gain));

    var_AddCallback(parent, "audio-replay-gain-mode",
                    ReplayGainCallback, vol);
    var_TriggerCallback(parent, "audio-replay-gain-mode");

    return vol;
}