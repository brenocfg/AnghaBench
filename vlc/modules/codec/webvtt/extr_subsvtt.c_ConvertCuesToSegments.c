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
struct TYPE_5__ {scalar_t__ type; scalar_t__ i_start; scalar_t__ i_stop; scalar_t__ p_next; } ;
typedef  TYPE_1__ webvtt_dom_cue_t ;
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  text_segment_t ;
struct render_variables_s {int dummy; } ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ChainCueSegments (TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * ConvertCueToSegments (int /*<<< orphan*/ *,struct render_variables_s*,TYPE_1__ const*) ; 
 scalar_t__ NODE_CUE ; 
 int /*<<< orphan*/  VLC_UNUSED (scalar_t__) ; 

__attribute__((used)) static text_segment_t * ConvertCuesToSegments( decoder_t *p_dec, vlc_tick_t i_start, vlc_tick_t i_stop,
                                               struct render_variables_s *p_vars,
                                               const webvtt_dom_cue_t *p_cue )
{
    text_segment_t *p_segments = NULL;
    text_segment_t **pp_append = &p_segments;
    VLC_UNUSED(i_stop);

    for( ; p_cue; p_cue = (const webvtt_dom_cue_t *) p_cue->p_next )
    {
        if( p_cue->type != NODE_CUE )
            continue;

        if( p_cue->i_start > i_start || p_cue->i_stop <= i_start )
            continue;

        text_segment_t *p_new = ConvertCueToSegments( p_dec, p_vars, p_cue );
        ChainCueSegments( p_cue, p_new, pp_append );
    }
    return p_segments;
}