#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  out; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_11__ {int i_height; int i_width; scalar_t__ i_incr; int /*<<< orphan*/  i_next_date; TYPE_9__* p_audios; scalar_t__ i_telx_count; scalar_t__ p_y; scalar_t__ b_vbi; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/ * p_es; scalar_t__ i_group; } ;

/* Variables and functions */
 scalar_t__ DecodeAudio (TYPE_1__*,TYPE_9__*) ; 
 scalar_t__ DecodeTelx (TYPE_1__*) ; 
 int /*<<< orphan*/  DecodeVideo (TYPE_1__*) ; 
 int /*<<< orphan*/  DecodeWSS (TYPE_1__*) ; 
 int MAX_AUDIOS ; 
 scalar_t__ NewFrame (TYPE_1__*) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int DecodeFrame( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if ( p_sys->b_vbi )
    {
        DecodeWSS( p_demux );

        if ( p_sys->i_height == 576 )
        {
            /* For PAL, erase first half of line 23, last half of line 623,
             * and line 624 ; no need to erase chrominance */
            memset( p_sys->p_y, 0, p_sys->i_width / 2 );
            memset( p_sys->p_y + p_sys->i_width * 574 + p_sys->i_width / 2,
                        0, p_sys->i_width * 3 / 2 );
        }
    }

    if ( p_sys->i_telx_count )
        if ( DecodeTelx( p_demux ) != VLC_SUCCESS )
            return VLC_ENOMEM;

    for ( int i = 0; i < MAX_AUDIOS; i++ )
    {
        if ( p_sys->p_audios[i].i_group && p_sys->p_audios[i].p_es != NULL )
            if( DecodeAudio( p_demux, &p_sys->p_audios[i] ) != VLC_SUCCESS )
                return VLC_EGENERIC;
    }

    DecodeVideo( p_demux );

    es_out_SetPCR( p_demux->out, p_sys->i_next_date );
    p_sys->i_next_date += p_sys->i_incr;

    if( NewFrame( p_demux ) != VLC_SUCCESS )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}