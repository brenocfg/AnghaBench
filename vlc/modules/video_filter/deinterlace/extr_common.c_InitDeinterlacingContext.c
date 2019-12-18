#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int b_double_rate; int b_half_height; int b_use_frame_history; int b_custom_pts; } ;
struct deinterlace_ctx {int /*<<< orphan*/ ** pp_history; scalar_t__ i_frame_offset; TYPE_2__* meta; TYPE_1__ settings; } ;
struct TYPE_4__ {int pi_nb_fields; int pb_top_field_first; int /*<<< orphan*/  pi_date; } ;

/* Variables and functions */
 int HISTORY_SIZE ; 
 int METADATA_SIZE ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 

void InitDeinterlacingContext( struct deinterlace_ctx *p_context )
{
    p_context->settings.b_double_rate = false;
    p_context->settings.b_half_height = false;
    p_context->settings.b_use_frame_history = false;
    p_context->settings.b_custom_pts = false;

    p_context->meta[0].pi_date = VLC_TICK_INVALID;
    p_context->meta[0].pi_nb_fields = 2;
    p_context->meta[0].pb_top_field_first = true;
    for( int i = 1; i < METADATA_SIZE; i++ )
        p_context->meta[i] = p_context->meta[i-1];

    p_context->i_frame_offset = 0; /* start with default value (first-ever frame
                                  cannot have offset) */
    for( int i = 0; i < HISTORY_SIZE; i++ )
        p_context->pp_history[i] = NULL;
}