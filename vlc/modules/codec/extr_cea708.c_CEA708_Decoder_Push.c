#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {scalar_t__ i_clock; scalar_t__ suspended_deadline; int /*<<< orphan*/  input_buffer; } ;
typedef  TYPE_1__ cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708_Decode_ServiceBuffer (TYPE_1__*) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  cea708_input_buffer_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t cea708_input_buffer_remain (int /*<<< orphan*/ *) ; 
 size_t vlc_tick_from_samples (int,int) ; 

void CEA708_Decoder_Push( cea708_t *h, vlc_tick_t i_time,
                          const uint8_t *p_data, size_t i_data )
{
    /* Set new buffer start time */
    h->i_clock = i_time;

    for( size_t i=0; i<i_data; )
    {
        /* Never push more than buffer */
        size_t i_push = cea708_input_buffer_remain(&h->input_buffer);
        if( (i_data - i) < i_push )
            i_push = (i_data - i);
        else
            h->suspended_deadline = VLC_TICK_INVALID; /* Full buffer cancels pause */

        for( size_t j=0; j<i_push; j++ )
        {
            uint8_t byte = p_data[i+j];
            cea708_input_buffer_add( &h->input_buffer, byte );
        }

        if( h->suspended_deadline != VLC_TICK_INVALID )
        {
            /* Decoding is paused */
            if ( h->suspended_deadline > h->i_clock )
            {
                /* Increase internal clock */
                if( i_push )
                    h->i_clock += vlc_tick_from_samples(1, 1200) * i_push;
                continue;
            }
            h->suspended_deadline = VLC_TICK_INVALID;
        }

        /* Decode Buffer */
        CEA708_Decode_ServiceBuffer( h );

        i += i_push;
    }
}