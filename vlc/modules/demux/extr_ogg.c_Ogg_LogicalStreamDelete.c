#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  p_blocks; } ;
struct TYPE_10__ {TYPE_1__ queue; int /*<<< orphan*/ * p_skel; int /*<<< orphan*/ * idx; int /*<<< orphan*/  fmt; int /*<<< orphan*/  fmt_old; struct TYPE_10__* p_headers; int /*<<< orphan*/  os; scalar_t__ p_es; } ;
typedef  TYPE_2__ logical_stream_t ;
struct TYPE_11__ {int /*<<< orphan*/  out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_12__ {TYPE_2__* p_skelstream; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Ogg_CleanSpecificData (TYPE_2__*) ; 
 int /*<<< orphan*/  Ogg_FreeSkeleton (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  ogg_stream_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oggseek_index_entries_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Ogg_LogicalStreamDelete( demux_t *p_demux, logical_stream_t *p_stream )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if( p_stream->p_es )
        es_out_Del( p_demux->out, p_stream->p_es );

    ogg_stream_clear( &p_stream->os );
    free( p_stream->p_headers );

    Ogg_CleanSpecificData( p_stream );

    es_format_Clean( &p_stream->fmt_old );
    es_format_Clean( &p_stream->fmt );

    if ( p_stream->idx != NULL)
    {
        oggseek_index_entries_free( p_stream->idx );
    }

    Ogg_FreeSkeleton( p_stream->p_skel );
    p_stream->p_skel = NULL;
    if( p_sys->p_skelstream == p_stream )
        p_sys->p_skelstream = NULL;

    /* Shouldn't happen */
    block_ChainRelease( p_stream->queue.p_blocks );

    free( p_stream );
}