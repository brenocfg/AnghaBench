#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_9__ {scalar_t__ i_id; int b_drop; scalar_t__ p_out; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
struct TYPE_10__ {int /*<<< orphan*/  fmt; scalar_t__ id; scalar_t__ p_first; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  OutputStart (TYPE_1__*) ; 
 int /*<<< orphan*/  TAB_REMOVE (scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_ChainRelease (scalar_t__) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  sout_StreamIdDel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void Del( sout_stream_t *p_stream, void *_id )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;

    if( !p_sys->p_out )
        OutputStart( p_stream );

    if( id->p_first )
        block_ChainRelease( id->p_first );

    assert( !id->id || p_sys->p_out );
    if( id->id )
        sout_StreamIdDel( p_sys->p_out, id->id );

    es_format_Clean( &id->fmt );

    TAB_REMOVE( p_sys->i_id, p_sys->id, id );

    if( p_sys->i_id <= 0 )
    {
        if( !p_sys->p_out )
            p_sys->b_drop = false;
    }

    free( id );
}