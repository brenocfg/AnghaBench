#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ i_start; scalar_t__ i_stop; } ;
typedef  TYPE_3__ webvtt_cue_t ;
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_16__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_14__ {scalar_t__ i_current; } ;
struct TYPE_13__ {size_t i_count; TYPE_3__* p_array; } ;
struct TYPE_17__ {TYPE_2__ index; TYPE_1__ cues; } ;
typedef  TYPE_5__ demux_sys_t ;
struct TYPE_18__ {struct TYPE_18__* p_next; } ;
typedef  TYPE_6__ block_t ;

/* Variables and functions */
 TYPE_6__* ConvertWEBVTT (TYPE_3__ const*,int) ; 
 TYPE_6__* block_ChainGather (TYPE_6__*) ; 

__attribute__((used)) static block_t *demux_From( demux_t *p_demux, vlc_tick_t i_start )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    block_t *p_list = NULL;
    block_t **pp_append = &p_list;
    for( size_t i=0; i<p_sys->cues.i_count; i++ )
    {
        const webvtt_cue_t *p_cue = &p_sys->cues.p_array[i];
        if( p_cue->i_start > i_start )
        {
            break;
        }
        else if( p_cue->i_start <= i_start && p_cue->i_stop > i_start )
        {
            *pp_append = ConvertWEBVTT( p_cue, p_sys->index.i_current > 0 );
            if( *pp_append )
                pp_append = &((*pp_append)->p_next);
        }
    }

    return ( p_list ) ? block_ChainGather( p_list ) : NULL;
}