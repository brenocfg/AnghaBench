#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * p_head; int /*<<< orphan*/ ** pp_last; } ;
struct TYPE_7__ {scalar_t__ i_saved; int /*<<< orphan*/ * p_data; int /*<<< orphan*/ ** pp_last; scalar_t__ i_gathered; scalar_t__ i_data_size; } ;
struct TYPE_9__ {int b_broken_PUSI_conformance; int b_always_receive; int i_last_dts; TYPE_2__ prepcr; int /*<<< orphan*/ * p_proc; int /*<<< orphan*/ * p_sections_proc; TYPE_1__ gather; int /*<<< orphan*/  transport; scalar_t__ i_stream_type; int /*<<< orphan*/  p_es; } ;
typedef  TYPE_3__ ts_stream_t ;
typedef  int /*<<< orphan*/  ts_pmt_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  TS_TRANSPORT_PES ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  ts_es_New (int /*<<< orphan*/ *) ; 

ts_stream_t *ts_stream_New( demux_t *p_demux, ts_pmt_t *p_program )
{
    VLC_UNUSED(p_demux);
    ts_stream_t *pes = malloc( sizeof( ts_stream_t ) );
    if( !pes )
        return NULL;

    pes->p_es = ts_es_New( p_program );
    if( !pes->p_es )
    {
        free( pes );
        return NULL;
    }
    pes->i_stream_type = 0;
    pes->transport = TS_TRANSPORT_PES;
    pes->gather.i_data_size = 0;
    pes->gather.i_gathered = 0;
    pes->gather.p_data = NULL;
    pes->gather.pp_last = &pes->gather.p_data;
    pes->gather.i_saved = 0;
    pes->b_broken_PUSI_conformance = false;
    pes->b_always_receive = false;
    pes->p_sections_proc = NULL;
    pes->p_proc = NULL;
    pes->prepcr.p_head = NULL;
    pes->prepcr.pp_last = &pes->prepcr.p_head;
    pes->i_last_dts = -1;

    return pes;
}