#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_13__ {int i_nb_streams; TYPE_1__** pp_streams; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
struct TYPE_14__ {scalar_t__* pp_ids; } ;
typedef  TYPE_3__ sout_stream_id_sys_t ;
struct TYPE_15__ {struct TYPE_15__* p_next; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 TYPE_4__* block_Duplicate (TYPE_4__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  sout_StreamIdSend (TYPE_1__*,scalar_t__,TYPE_4__*) ; 

__attribute__((used)) static int Send( sout_stream_t *p_stream, void *_id, block_t *p_buffer )
{
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;
    sout_stream_t     *p_dup_stream;
    int               i_stream;

    /* Loop through the linked list of buffers */
    while( p_buffer )
    {
        block_t *p_next = p_buffer->p_next;

        p_buffer->p_next = NULL;

        for( i_stream = 0; i_stream < p_sys->i_nb_streams - 1; i_stream++ )
        {
            p_dup_stream = p_sys->pp_streams[i_stream];

            if( id->pp_ids[i_stream] )
            {
                block_t *p_dup = block_Duplicate( p_buffer );

                if( p_dup )
                    sout_StreamIdSend( p_dup_stream, id->pp_ids[i_stream], p_dup );
            }
        }

        if( i_stream < p_sys->i_nb_streams && id->pp_ids[i_stream] )
        {
            p_dup_stream = p_sys->pp_streams[i_stream];
            sout_StreamIdSend( p_dup_stream, id->pp_ids[i_stream], p_buffer );
        }
        else
        {
            block_Release( p_buffer );
        }

        p_buffer = p_next;
    }
    return VLC_SUCCESS;
}