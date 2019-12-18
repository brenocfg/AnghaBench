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
struct TYPE_7__ {int /*<<< orphan*/  p_next; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_8__ {int b_streamswap; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ sout_stream_id_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_DISCONTINUITY ; 
 int sout_StreamIdSend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int Send( sout_stream_t *p_stream, void *_id, block_t *p_buffer )
{
    sout_stream_id_sys_t *id = (sout_stream_id_sys_t *)_id;
    if ( id->b_streamswap )
    {
        id->b_streamswap = false;
        p_buffer->i_flags |= BLOCK_FLAG_DISCONTINUITY;
    }
    return sout_StreamIdSend( p_stream->p_next, id->id, p_buffer );
}