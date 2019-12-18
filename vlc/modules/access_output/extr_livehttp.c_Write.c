#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_12__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_13__ {int b_segment_has_data; TYPE_3__** ongoing_segment_end; TYPE_3__* ongoing_segment; TYPE_3__** full_segments_end; scalar_t__ b_splitanywhere; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;
struct TYPE_14__ {int i_flags; struct TYPE_14__* p_next; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_HEADER ; 
 scalar_t__ CheckSegmentChange (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  block_ChainLastAppend (TYPE_3__***,TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

__attribute__((used)) static ssize_t Write( sout_access_out_t *p_access, block_t *p_buffer )
{
    size_t i_write = 0;
    sout_access_out_sys_t *p_sys = p_access->p_sys;
    while( p_buffer )
    {
        /* Check if current block is already past segment-length
            and we want to write gathered blocks into segment
            and update playlist */
        if( p_sys->ongoing_segment && ( p_sys->b_splitanywhere  || ( p_buffer->i_flags & BLOCK_FLAG_HEADER ) ) )
        {
            msg_Dbg( p_access, "Moving ongoing segment to full segments-queue" );
            block_ChainLastAppend( &p_sys->full_segments_end, p_sys->ongoing_segment );
            p_sys->ongoing_segment = NULL;
            p_sys->ongoing_segment_end = &p_sys->ongoing_segment;
            p_sys->b_segment_has_data = true;
        }

        ssize_t ret = CheckSegmentChange( p_access, p_buffer );
        if( ret < 0 )
        {
            msg_Err( p_access, "Error in write loop");
            return ret;
        }
        i_write += ret;

        block_t *p_temp = p_buffer->p_next;
        p_buffer->p_next = NULL;
        block_ChainLastAppend( &p_sys->ongoing_segment_end, p_buffer );
        p_buffer = p_temp;
    }

    return i_write;
}