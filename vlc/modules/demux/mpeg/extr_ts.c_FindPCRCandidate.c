#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int i_size; TYPE_8__** p_elems; } ;
struct TYPE_17__ {int i_pid_pcr; TYPE_1__ e_streams; } ;
typedef  TYPE_7__ ts_pmt_t ;
struct TYPE_16__ {TYPE_5__* p_stream; } ;
struct TYPE_12__ {scalar_t__ i_pcr_count; } ;
struct TYPE_18__ {int i_pid; TYPE_6__ u; TYPE_2__ probed; } ;
typedef  TYPE_8__ ts_pid_t ;
struct TYPE_15__ {TYPE_4__* p_es; } ;
struct TYPE_13__ {scalar_t__ i_cat; } ;
struct TYPE_14__ {TYPE_3__ fmt; } ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ SEEN (TYPE_8__*) ; 
 scalar_t__ VIDEO_ES ; 

int FindPCRCandidate( ts_pmt_t *p_pmt )
{
    ts_pid_t *p_cand = NULL;
    int i_previous = p_pmt->i_pid_pcr;

    for( int i=0; i<p_pmt->e_streams.i_size; i++ )
    {
        ts_pid_t *p_pid = p_pmt->e_streams.p_elems[i];
        if( SEEN(p_pid) && p_pid->i_pid != i_previous )
        {
            if( p_pid->probed.i_pcr_count ) /* check PCR frequency first */
            {
                if( !p_cand || p_pid->probed.i_pcr_count > p_cand->probed.i_pcr_count )
                {
                    p_cand = p_pid;
                    continue;
                }
            }

            if( p_pid->u.p_stream->p_es->fmt.i_cat == AUDIO_ES )
            {
                if( !p_cand )
                    p_cand = p_pid;
            }
            else if ( p_pid->u.p_stream->p_es->fmt.i_cat == VIDEO_ES ) /* Otherwise prioritize video dts */
            {
                if( !p_cand || p_cand->u.p_stream->p_es->fmt.i_cat == AUDIO_ES )
                    p_cand = p_pid;
            }
        }
    }

    if( p_cand )
        return p_cand->i_pid;
    else
        return 0x1FFF;
}