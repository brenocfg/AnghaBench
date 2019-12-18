#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct deinterlace_ctx {int /*<<< orphan*/ ** pp_history; scalar_t__ i_frame_offset; TYPE_1__* meta; } ;
struct TYPE_2__ {int pi_nb_fields; int pb_top_field_first; int /*<<< orphan*/  pi_date; } ;

/* Variables and functions */
 int HISTORY_SIZE ; 
 int METADATA_SIZE ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 

void FlushDeinterlacing(struct deinterlace_ctx *p_context)
{
    p_context->meta[0].pi_date = VLC_TICK_INVALID;
    p_context->meta[0].pi_nb_fields = 2;
    p_context->meta[0].pb_top_field_first = true;
    for( int i = 1; i < METADATA_SIZE; i++ )
        p_context->meta[i] = p_context->meta[i-1];

    p_context->i_frame_offset = 0; /* reset to default value (first frame after
                                      flush cannot have offset) */
    for( int i = 0; i < HISTORY_SIZE; i++ )
    {
        if( p_context->pp_history[i] )
            picture_Release( p_context->pp_history[i] );
        p_context->pp_history[i] = NULL;
    }
}