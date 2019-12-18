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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_15__ {int /*<<< orphan*/  i_last_dts; TYPE_8__* p_es; } ;
typedef  TYPE_5__ ts_stream_t ;
struct TYPE_12__ {int i_size; TYPE_7__** p_elems; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_current; } ;
struct TYPE_16__ {TYPE_2__ e_streams; TYPE_1__ pcr; } ;
typedef  TYPE_6__ ts_pmt_t ;
struct TYPE_14__ {TYPE_5__* p_stream; } ;
struct TYPE_17__ {int i_flags; scalar_t__ type; TYPE_4__ u; } ;
typedef  TYPE_7__ ts_pid_t ;
struct TYPE_13__ {scalar_t__ i_cat; } ;
struct TYPE_18__ {TYPE_3__ fmt; } ;
typedef  TYPE_8__ ts_es_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int FLAG_FILTERED ; 
 scalar_t__ SEEN (TYPE_7__ const*) ; 
 scalar_t__ SETANDVALID (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_STREAM ; 
 scalar_t__ VIDEO_ES ; 

__attribute__((used)) static vlc_tick_t GetTimeForUntimed( const ts_pmt_t *p_pmt )
{
    vlc_tick_t i_ts = p_pmt->pcr.i_current;
    const ts_stream_t *p_cand = NULL;
    for( int i=0; i< p_pmt->e_streams.i_size; i++ )
    {
        const ts_pid_t *p_pid = p_pmt->e_streams.p_elems[i];
        if( (p_pid->i_flags & FLAG_FILTERED) && SEEN(p_pid) &&
             p_pid->type == TYPE_STREAM &&
             p_pid->u.p_stream->p_es &&
             SETANDVALID(p_pid->u.p_stream->i_last_dts) )
        {
            const ts_es_t *p_es = p_pid->u.p_stream->p_es;
            if( p_es->fmt.i_cat == VIDEO_ES || p_es->fmt.i_cat == AUDIO_ES )
            {
                if( !p_cand || (p_es->fmt.i_cat == VIDEO_ES &&
                                p_cand->p_es->fmt.i_cat != VIDEO_ES) )
                {
                    p_cand = p_pid->u.p_stream;
                    i_ts = p_cand->i_last_dts;
                }
            }
        }
    }
    return i_ts;
}