#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_6__ {scalar_t__ i_type; } ;
struct TYPE_5__ {scalar_t__ i_chunk_fourcc; TYPE_3__* p_next; TYPE_3__* p_first; } ;
struct TYPE_7__ {TYPE_2__ list; TYPE_1__ common; } ;
typedef  TYPE_3__ avi_chunk_t ;

/* Variables and functions */

int  AVI_ChunkCount_( avi_chunk_t *p_chk, vlc_fourcc_t i_fourcc, bool b_list )
{
    if( !p_chk )
        return 0;

    int i_count = 0;
    for( avi_chunk_t *p_child = p_chk->common.p_first;
                      p_child; p_child = p_child->common.p_next )
    {
        if( b_list && p_child->list.i_type == 0 )
            continue;

        if( p_child->common.i_chunk_fourcc != i_fourcc &&
            (!b_list || p_child->list.i_type != i_fourcc) )
            continue;

        i_count++;
    }

    return i_count;
}