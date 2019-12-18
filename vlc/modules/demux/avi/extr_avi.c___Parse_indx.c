#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_16__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_17__ {int b_indexloaded; } ;
typedef  TYPE_5__ demux_sys_t ;
typedef  int /*<<< orphan*/  avi_index_t ;
struct TYPE_18__ {int i_length; int i_lengthtotal; scalar_t__ i_pos; void* i_flags; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_6__ avi_entry_t ;
struct TYPE_15__ {TYPE_2__* field; TYPE_1__* std; } ;
struct TYPE_19__ {unsigned int i_entriesinuse; scalar_t__ i_indexsubtype; TYPE_3__ idx; scalar_t__ i_baseoffset; int /*<<< orphan*/  i_id; int /*<<< orphan*/  i_indextype; } ;
typedef  TYPE_7__ avi_chunk_indx_t ;
struct TYPE_14__ {int i_size; scalar_t__ i_offset; } ;
struct TYPE_13__ {int i_size; scalar_t__ i_offset; } ;

/* Variables and functions */
 void* AVIIF_KEYFRAME ; 
 scalar_t__ AVI_INDEX_2FIELD ; 
 int /*<<< orphan*/  avi_index_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_4__*,char*,scalar_t__) ; 

__attribute__((used)) static void __Parse_indx( demux_t *p_demux, avi_index_t *p_index, uint64_t *pi_max_offset,
                          avi_chunk_indx_t *p_indx )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    avi_entry_t index;

    p_sys->b_indexloaded = true;

    msg_Dbg( p_demux, "loading subindex(0x%x) %d entries", p_indx->i_indextype, p_indx->i_entriesinuse );
    if( p_indx->i_indexsubtype == 0 )
    {
        for( unsigned i = 0; i < p_indx->i_entriesinuse; i++ )
        {
            index.i_id     = p_indx->i_id;
            index.i_flags  = p_indx->idx.std[i].i_size & 0x80000000 ? 0 : AVIIF_KEYFRAME;
            index.i_pos    = p_indx->i_baseoffset + p_indx->idx.std[i].i_offset - 8;
            index.i_length = p_indx->idx.std[i].i_size&0x7fffffff;
            index.i_lengthtotal = index.i_length;

            avi_index_Append( p_index, pi_max_offset, &index );
        }
    }
    else if( p_indx->i_indexsubtype == AVI_INDEX_2FIELD )
    {
        for( unsigned i = 0; i < p_indx->i_entriesinuse; i++ )
        {
            index.i_id     = p_indx->i_id;
            index.i_flags  = p_indx->idx.field[i].i_size & 0x80000000 ? 0 : AVIIF_KEYFRAME;
            index.i_pos    = p_indx->i_baseoffset + p_indx->idx.field[i].i_offset - 8;
            index.i_length = p_indx->idx.field[i].i_size;
            index.i_lengthtotal = index.i_length;

            avi_index_Append( p_index, pi_max_offset, &index );
        }
    }
    else
    {
        msg_Warn( p_demux, "unknown subtype index(0x%x)", p_indx->i_indexsubtype );
    }
}