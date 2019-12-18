#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ p_head; } ;
struct TYPE_6__ {scalar_t__ p_data; } ;
struct TYPE_8__ {TYPE_2__ prepcr; scalar_t__ p_proc; scalar_t__ p_sections_proc; TYPE_1__ gather; int /*<<< orphan*/  p_es; } ;
typedef  TYPE_3__ ts_stream_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  ts_pes_ChainDelete_es (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_sections_processor_ChainDelete (scalar_t__) ; 
 int /*<<< orphan*/  ts_stream_processor_Delete (scalar_t__) ; 

void ts_stream_Del( demux_t *p_demux, ts_stream_t *pes )
{
    ts_pes_ChainDelete_es( p_demux, pes->p_es );

    if( pes->gather.p_data )
        block_ChainRelease( pes->gather.p_data );

    if( pes->p_sections_proc )
        ts_sections_processor_ChainDelete( pes->p_sections_proc );

    if( pes->p_proc )
        ts_stream_processor_Delete( pes->p_proc );

    if( pes->prepcr.p_head )
        block_ChainRelease( pes->prepcr.p_head );

    free( pes );
}