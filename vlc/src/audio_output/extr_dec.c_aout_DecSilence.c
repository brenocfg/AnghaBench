#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* vlc_tick_t ;
struct TYPE_14__ {size_t i_nb_samples; void* i_length; void* i_dts; void* i_pts; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_2__ block_t ;
struct TYPE_15__ {size_t i_bytes_per_frame; size_t i_frame_length; int /*<<< orphan*/  i_rate; } ;
typedef  TYPE_3__ audio_sample_format_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* play ) (TYPE_4__*,TYPE_2__*,void* const) ;} ;
typedef  TYPE_4__ audio_output_t ;
struct TYPE_13__ {int /*<<< orphan*/  rate; int /*<<< orphan*/  clock; } ;
struct TYPE_17__ {TYPE_1__ sync; TYPE_3__ mixer_format; } ;
typedef  TYPE_5__ aout_owner_t ;

/* Variables and functions */
 TYPE_5__* aout_owner (TYPE_4__*) ; 
 TYPE_2__* block_Alloc (size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,size_t) ; 
 size_t samples_from_vlc_tick (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_2__*,void* const) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 void* vlc_clock_ConvertToSystem (int /*<<< orphan*/ ,void* const,void*,int /*<<< orphan*/ ) ; 
 void* vlc_tick_now () ; 

__attribute__((used)) static void aout_DecSilence (audio_output_t *aout, vlc_tick_t length, vlc_tick_t pts)
{
    aout_owner_t *owner = aout_owner (aout);
    const audio_sample_format_t *fmt = &owner->mixer_format;
    size_t frames = samples_from_vlc_tick(length, fmt->i_rate);

    block_t *block = block_Alloc (frames * fmt->i_bytes_per_frame
                                  / fmt->i_frame_length);
    if (unlikely(block == NULL))
        return; /* uho! */

    msg_Dbg (aout, "inserting %zu zeroes", frames);
    memset (block->p_buffer, 0, block->i_buffer);
    block->i_nb_samples = frames;
    block->i_pts = pts;
    block->i_dts = pts;
    block->i_length = length;

    const vlc_tick_t system_now = vlc_tick_now();
    const vlc_tick_t system_pts =
       vlc_clock_ConvertToSystem(owner->sync.clock, system_now, pts,
                                 owner->sync.rate);
    aout->play(aout, block, system_pts);
}