#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_7__ {scalar_t__ i_chunk_fourcc; TYPE_2__* p_first; TYPE_2__* p_next; } ;
struct TYPE_8__ {TYPE_1__ common; } ;
typedef  TYPE_2__ avi_chunk_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* AVI_ChunkFree_function ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int AVI_ChunkFunctionFind (scalar_t__) ; 
 TYPE_5__* AVI_Chunk_Function ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void AVI_ChunkClean( stream_t *s,
                     avi_chunk_t *p_chk )
{
    int i_index;
    avi_chunk_t *p_child, *p_next;

    if( !p_chk )
    {
        return;
    }

    /* Free all child chunk */
    p_child = p_chk->common.p_first;
    while( p_child )
    {
        p_next = p_child->common.p_next;
        AVI_ChunkClean( s, p_child );
        free( p_child );
        p_child = p_next;
    }

    i_index = AVI_ChunkFunctionFind( p_chk->common.i_chunk_fourcc );
    if( AVI_Chunk_Function[i_index].AVI_ChunkFree_function )
    {
#ifdef AVI_DEBUG
        msg_Dbg( (vlc_object_t*)s, "free chunk %4.4s",
                 (char*)&p_chk->common.i_chunk_fourcc );
#endif
        AVI_Chunk_Function[i_index].AVI_ChunkFree_function( p_chk);
    }
    else if( p_chk->common.i_chunk_fourcc != 0 )
    {
        msg_Warn( (vlc_object_t*)s, "unknown chunk: %4.4s (not unloaded)",
                (char*)&p_chk->common.i_chunk_fourcc );
    }
    p_chk->common.p_first = NULL;

    return;
}