#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  audio_output_t ;
struct TYPE_8__ {scalar_t__ i_format; } ;
struct TYPE_6__ {int /*<<< orphan*/  delay; int /*<<< orphan*/  clock; int /*<<< orphan*/  resamp_type; } ;
struct TYPE_7__ {TYPE_4__ mixer_format; TYPE_1__ sync; int /*<<< orphan*/ * filters; int /*<<< orphan*/  filters_cfg; TYPE_4__ filter_format; int /*<<< orphan*/  volume; TYPE_4__ input_format; int /*<<< orphan*/  restart; } ;
typedef  TYPE_2__ aout_owner_t ;

/* Variables and functions */
 int AOUT_DEC_CHANGED ; 
 int AOUT_DEC_FAILED ; 
 int AOUT_DEC_SUCCESS ; 
 int /*<<< orphan*/  AOUT_FILTERS_CFG_INIT ; 
 int /*<<< orphan*/  AOUT_RESAMPLING_NONE ; 
 int AOUT_RESTART_OUTPUT ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_FiltersDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * aout_FiltersNewWithClock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_FiltersSetClockDelay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_OutputDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ aout_OutputNew (int /*<<< orphan*/ *) ; 
 TYPE_2__* aout_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aout_volume_SetFormat (int /*<<< orphan*/ ,scalar_t__) ; 
 int atomic_exchange_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_acquire ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aout_CheckReady (audio_output_t *aout)
{
    aout_owner_t *owner = aout_owner (aout);
    int status = AOUT_DEC_SUCCESS;

    int restart = atomic_exchange_explicit(&owner->restart, 0,
                                           memory_order_acquire);
    if (unlikely(restart))
    {
        if (owner->mixer_format.i_format)
            aout_FiltersDelete (aout, owner->filters);

        if (restart & AOUT_RESTART_OUTPUT)
        {   /* Reinitializes the output */
            msg_Dbg (aout, "restarting output...");
            if (owner->mixer_format.i_format)
                aout_OutputDelete (aout);
            owner->filter_format = owner->mixer_format = owner->input_format;
            owner->filters_cfg = AOUT_FILTERS_CFG_INIT;
            if (aout_OutputNew (aout))
                owner->mixer_format.i_format = 0;
            aout_volume_SetFormat (owner->volume,
                                   owner->mixer_format.i_format);

            /* Notify the decoder that the aout changed in order to try a new
             * suitable codec (like an HDMI audio format). However, keep the
             * same codec if the aout was restarted because of a stereo-mode
             * change from the user. */
            if (restart == AOUT_RESTART_OUTPUT)
                status = AOUT_DEC_CHANGED;
        }

        msg_Dbg (aout, "restarting filters...");
        owner->sync.resamp_type = AOUT_RESAMPLING_NONE;

        if (owner->mixer_format.i_format)
        {
            owner->filters = aout_FiltersNewWithClock(VLC_OBJECT(aout),
                                                      owner->sync.clock,
                                                      &owner->filter_format,
                                                      &owner->mixer_format,
                                                      &owner->filters_cfg);
            if (owner->filters == NULL)
            {
                aout_OutputDelete (aout);
                owner->mixer_format.i_format = 0;
            }
            aout_FiltersSetClockDelay(owner->filters, owner->sync.delay);
        }
        /* TODO: This would be a good time to call clean up any video output
         * left over by an audio visualization:
        input_resource_TerminatVout(MAGIC HERE); */
    }
    return (owner->mixer_format.i_format) ? status : AOUT_DEC_FAILED;
}