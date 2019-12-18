#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/ * p_head; int /*<<< orphan*/ ** pp_last; } ;
struct TYPE_32__ {int i_last_dts; int /*<<< orphan*/  p_proc; int /*<<< orphan*/  p_sections_proc; TYPE_6__ prepcr; TYPE_13__* p_es; } ;
typedef  TYPE_9__ ts_stream_t ;
struct TYPE_31__ {int i_current; } ;
struct TYPE_28__ {int i_size; TYPE_11__** p_elems; } ;
struct TYPE_18__ {TYPE_8__ pcr; TYPE_5__ e_streams; } ;
typedef  TYPE_10__ ts_pmt_t ;
struct TYPE_30__ {TYPE_9__* p_stream; } ;
struct TYPE_19__ {scalar_t__ type; int i_cc; TYPE_7__ u; scalar_t__ i_dup; } ;
typedef  TYPE_11__ ts_pid_t ;
struct TYPE_27__ {int i_size; TYPE_3__** p_elems; } ;
struct TYPE_20__ {TYPE_4__ programs; } ;
typedef  TYPE_12__ ts_pat_t ;
struct TYPE_21__ {int /*<<< orphan*/  i_next_block_flags; struct TYPE_21__* p_next; } ;
typedef  TYPE_13__ ts_es_t ;
struct TYPE_22__ {int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_14__ demux_t ;
typedef  int /*<<< orphan*/  demux_sys_t ;
struct TYPE_25__ {TYPE_10__* p_pmt; } ;
struct TYPE_26__ {TYPE_2__ u; } ;
struct TYPE_24__ {TYPE_12__* p_pat; } ;
struct TYPE_23__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  FlushESBuffer (TYPE_9__*) ; 
 TYPE_16__* GetPID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_STREAM ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_sections_processor_Reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_stream_processor_Reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ReadyQueuesPostSeek( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    ts_pat_t *p_pat = GetPID(p_sys, 0)->u.p_pat;
    for( int i=0; i< p_pat->programs.i_size; i++ )
    {
        ts_pmt_t *p_pmt = p_pat->programs.p_elems[i]->u.p_pmt;
        for( int j=0; j<p_pmt->e_streams.i_size; j++ )
        {
            ts_pid_t *pid = p_pmt->e_streams.p_elems[j];
            ts_stream_t *p_pes = pid->u.p_stream;

            if( pid->type != TYPE_STREAM )
                continue;

            for( ts_es_t *p_es = p_pes->p_es; p_es; p_es = p_es->p_next )
                p_es->i_next_block_flags |= BLOCK_FLAG_DISCONTINUITY;

            pid->i_cc = 0xff;
            pid->i_dup = 0;
            pid->u.p_stream->i_last_dts = -1;

            if( pid->u.p_stream->prepcr.p_head )
            {
                block_ChainRelease( pid->u.p_stream->prepcr.p_head );
                pid->u.p_stream->prepcr.p_head = NULL;
                pid->u.p_stream->prepcr.pp_last = &pid->u.p_stream->prepcr.p_head;
            }

            ts_sections_processor_Reset( pid->u.p_stream->p_sections_proc );
            ts_stream_processor_Reset( pid->u.p_stream->p_proc );

            FlushESBuffer( pid->u.p_stream );
        }
        p_pmt->pcr.i_current = -1;
    }
}