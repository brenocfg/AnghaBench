#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  p_access; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ sout_mux_t ;
struct TYPE_15__ {size_t i_pos; unsigned int i_nb_streams; TYPE_4__** pp_streams; } ;
typedef  TYPE_3__ sout_mux_sys_t ;
struct TYPE_13__ {int /*<<< orphan*/ * p_last; TYPE_5__* p_first; } ;
struct TYPE_16__ {TYPE_1__ towrite; int /*<<< orphan*/  i_written_duration; } ;
typedef  TYPE_4__ mp4_stream_t ;
struct TYPE_17__ {struct TYPE_17__* p_next; TYPE_7__* p_block; TYPE_7__* b; } ;
typedef  TYPE_5__ mp4_fragentry_t ;
typedef  TYPE_5__ bo_t ;
struct TYPE_18__ {int /*<<< orphan*/  i_flags; scalar_t__ i_length; scalar_t__ i_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_I ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t bo_size (TYPE_5__*) ; 
 int /*<<< orphan*/  box_fix (TYPE_5__*,size_t) ; 
 TYPE_5__* box_new (char*) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  sout_AccessOutWrite (int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static void WriteFragmentMDAT(sout_mux_t *p_mux, size_t i_total_size)
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;

    /* Now add mdat header */
    bo_t *mdat = box_new("mdat");
    if(!mdat)
        return;
    /* force update of real size */
    assert(bo_size(mdat)==8);
    box_fix(mdat, bo_size(mdat) + i_total_size);
    p_sys->i_pos += bo_size(mdat);
    /* only write header */
    sout_AccessOutWrite(p_mux->p_access, mdat->b);
    free(mdat);
    /* Header and its size are written and good, now write content */
    for (unsigned int i_trak = 0; i_trak < p_sys->i_nb_streams; i_trak++)
    {
        mp4_stream_t *p_stream = p_sys->pp_streams[i_trak];

        while(p_stream->towrite.p_first)
        {
            mp4_fragentry_t *p_entry = p_stream->towrite.p_first;
            p_sys->i_pos += p_entry->p_block->i_buffer;
            p_stream->i_written_duration += p_entry->p_block->i_length;

            p_entry->p_block->i_flags &= ~BLOCK_FLAG_TYPE_I; // clear flag for http stream
            sout_AccessOutWrite(p_mux->p_access, p_entry->p_block);

            p_stream->towrite.p_first = p_entry->p_next;
            free(p_entry);
            if (!p_stream->towrite.p_first)
                p_stream->towrite.p_last = NULL;
        }
    }
}