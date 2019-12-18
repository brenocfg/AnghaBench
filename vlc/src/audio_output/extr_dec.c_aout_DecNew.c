#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ i_bitspersample; scalar_t__ i_channels; int i_rate; int /*<<< orphan*/  i_format; } ;
typedef  TYPE_3__ const vlc_clock_t ;
typedef  TYPE_3__ audio_sample_format_t ;
typedef  int /*<<< orphan*/  audio_replay_gain_t ;
typedef  TYPE_3__ const audio_output_t ;
struct TYPE_23__ {int /*<<< orphan*/  update; } ;
struct TYPE_22__ {float rate; int discontinuity; scalar_t__ request_delay; scalar_t__ delay; int /*<<< orphan*/  resamp_type; TYPE_3__ const* clock; } ;
struct TYPE_25__ {int input_profile; TYPE_2__ vp; int /*<<< orphan*/  buffers_played; int /*<<< orphan*/  buffers_lost; TYPE_1__ sync; int /*<<< orphan*/  original_pts; int /*<<< orphan*/ * volume; int /*<<< orphan*/ * filters; int /*<<< orphan*/  filters_cfg; TYPE_3__ mixer_format; TYPE_3__ filter_format; TYPE_3__ input_format; int /*<<< orphan*/  restart; } ;
typedef  TYPE_6__ aout_owner_t ;

/* Variables and functions */
 int AOUT_CHAN_MAX ; 
 int /*<<< orphan*/  AOUT_FILTERS_CFG_INIT ; 
 int /*<<< orphan*/  AOUT_RESAMPLING_NONE ; 
 scalar_t__ INPUT_CHAN_MAX ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__ const*) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/ * aout_FiltersNewWithClock (int /*<<< orphan*/ ,TYPE_3__ const*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int aout_FormatNbChannels (TYPE_3__ const*) ; 
 int /*<<< orphan*/  aout_OutputDelete (TYPE_3__ const*) ; 
 scalar_t__ aout_OutputNew (TYPE_3__ const*) ; 
 TYPE_6__* aout_owner (TYPE_3__ const*) ; 
 int /*<<< orphan*/  aout_volume_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * aout_volume_New (TYPE_3__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  aout_volume_SetFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_3__ const*) ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__ const*,char*,...) ; 

int aout_DecNew(audio_output_t *p_aout, const audio_sample_format_t *p_format,
                int profile, vlc_clock_t *clock,
                const audio_replay_gain_t *p_replay_gain)
{
    assert(p_aout);
    assert(p_format);
    assert(clock);
    if( p_format->i_bitspersample > 0 )
    {
        /* Sanitize audio format, input need to have a valid physical channels
         * layout or a valid number of channels. */
        int i_map_channels = aout_FormatNbChannels( p_format );
        if( ( i_map_channels == 0 && p_format->i_channels == 0 )
           || i_map_channels > AOUT_CHAN_MAX || p_format->i_channels > INPUT_CHAN_MAX )
        {
            msg_Err( p_aout, "invalid audio channels count" );
            return -1;
        }
    }

    if( p_format->i_rate > 384000 )
    {
        msg_Err( p_aout, "excessive audio sample frequency (%u)",
                 p_format->i_rate );
        return -1;
    }
    if( p_format->i_rate < 4000 )
    {
        msg_Err( p_aout, "too low audio sample frequency (%u)",
                 p_format->i_rate );
        return -1;
    }

    aout_owner_t *owner = aout_owner(p_aout);

    /* Create the audio output stream */
    owner->volume = aout_volume_New (p_aout, p_replay_gain);

    atomic_store_explicit(&owner->restart, 0, memory_order_relaxed);
    owner->input_profile = profile;
    owner->filter_format = owner->mixer_format = owner->input_format = *p_format;

    owner->sync.clock = clock;

    owner->filters_cfg = AOUT_FILTERS_CFG_INIT;
    if (aout_OutputNew (p_aout))
        goto error;
    aout_volume_SetFormat (owner->volume, owner->mixer_format.i_format);

    /* Create the audio filtering "input" pipeline */
    owner->filters = aout_FiltersNewWithClock(VLC_OBJECT(p_aout), clock,
                                              &owner->filter_format,
                                              &owner->mixer_format,
                                              &owner->filters_cfg);
    if (owner->filters == NULL)
    {
        aout_OutputDelete (p_aout);
error:
        aout_volume_Delete (owner->volume);
        owner->volume = NULL;
        return -1;
    }

    owner->sync.rate = 1.f;
    owner->sync.resamp_type = AOUT_RESAMPLING_NONE;
    owner->sync.discontinuity = true;
    owner->original_pts = VLC_TICK_INVALID;
    owner->sync.delay = owner->sync.request_delay = 0;

    atomic_init (&owner->buffers_lost, 0);
    atomic_init (&owner->buffers_played, 0);
    atomic_store_explicit(&owner->vp.update, true, memory_order_relaxed);
    return 0;
}