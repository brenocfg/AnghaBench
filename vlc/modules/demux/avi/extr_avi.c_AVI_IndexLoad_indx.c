#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_15__ {int /*<<< orphan*/  s; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_16__ {unsigned int i_track; int /*<<< orphan*/  b_seekable; scalar_t__ b_odml; int /*<<< orphan*/  ck_root; } ;
typedef  TYPE_4__ demux_sys_t ;
typedef  int /*<<< orphan*/  avi_index_t ;
struct TYPE_14__ {TYPE_1__* super; } ;
struct TYPE_18__ {scalar_t__ i_indextype; unsigned int i_entriesinuse; TYPE_2__ idx; } ;
struct TYPE_17__ {TYPE_6__ indx; } ;
typedef  TYPE_5__ avi_chunk_t ;
typedef  int /*<<< orphan*/  avi_chunk_list_t ;
typedef  TYPE_6__ avi_chunk_indx_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVIFOURCC_RIFF ; 
 int /*<<< orphan*/  AVIFOURCC_hdrl ; 
 int /*<<< orphan*/  AVIFOURCC_indx ; 
 int /*<<< orphan*/  AVIFOURCC_strl ; 
 int /*<<< orphan*/  AVI_ChunkClean (int /*<<< orphan*/ ,TYPE_5__*) ; 
 void* AVI_ChunkFind (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ AVI_ChunkRead (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ AVI_INDEX_OF_CHUNKS ; 
 scalar_t__ AVI_INDEX_OF_INDEXES ; 
 int /*<<< orphan*/  __Parse_indx (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*,...) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AVI_IndexLoad_indx( demux_t *p_demux,
                                avi_index_t p_index[], uint64_t *pi_last_offset )
{
    demux_sys_t         *p_sys = p_demux->p_sys;

    avi_chunk_list_t    *p_riff;
    avi_chunk_list_t    *p_hdrl;

    p_riff = AVI_ChunkFind( &p_sys->ck_root, AVIFOURCC_RIFF, 0, true);
    p_hdrl = AVI_ChunkFind( p_riff, AVIFOURCC_hdrl, 0, true );

    for( unsigned i_stream = 0; i_stream < p_sys->i_track; i_stream++ )
    {
        avi_chunk_list_t    *p_strl;
        avi_chunk_indx_t    *p_indx;

#define p_stream  p_sys->track[i_stream]
        p_strl = AVI_ChunkFind( p_hdrl, AVIFOURCC_strl, i_stream, true );
        p_indx = AVI_ChunkFind( p_strl, AVIFOURCC_indx, 0, false );

        if( !p_indx )
        {
            if( p_sys->b_odml )
                msg_Warn( p_demux, "cannot find indx (misdetect/broken OpenDML "
                                   "file?)" );
            continue;
        }

        if( p_indx->i_indextype == AVI_INDEX_OF_CHUNKS )
        {
            __Parse_indx( p_demux, &p_index[i_stream], pi_last_offset, p_indx );
        }
        else if( p_indx->i_indextype == AVI_INDEX_OF_INDEXES )
        {
            if ( !p_sys->b_seekable )
                return;
            avi_chunk_t    ck_sub;
            for( unsigned i = 0; i < p_indx->i_entriesinuse; i++ )
            {
                if( vlc_stream_Seek( p_demux->s,
                                     p_indx->idx.super[i].i_offset ) ||
                    AVI_ChunkRead( p_demux->s, &ck_sub, NULL  ) )
                {
                    break;
                }
                if( ck_sub.indx.i_indextype == AVI_INDEX_OF_CHUNKS )
                    __Parse_indx( p_demux, &p_index[i_stream], pi_last_offset, &ck_sub.indx );
                AVI_ChunkClean( p_demux->s, &ck_sub );
            }
        }
        else
        {
            msg_Warn( p_demux, "unknown type index(0x%x)", p_indx->i_indextype );
        }
#undef p_stream
    }
}