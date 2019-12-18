#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {scalar_t__ i_type; } ;
struct TYPE_3__ {int i_chunk_size; scalar_t__ i_chunk_fourcc; union avi_chunk_u* p_next; union avi_chunk_u* p_first; } ;
union avi_chunk_u {TYPE_2__ list; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  union avi_chunk_u avi_chunk_t ;

/* Variables and functions */
 scalar_t__ AVIFOURCC_AVI ; 
 scalar_t__ AVIFOURCC_LIST ; 
 scalar_t__ AVIFOURCC_ON2 ; 
 scalar_t__ AVIFOURCC_ON2f ; 
 scalar_t__ AVIFOURCC_RIFF ; 
 scalar_t__ AVIFOURCC_movi ; 
 int /*<<< orphan*/  AVI_ChunkClean (int /*<<< orphan*/ *,union avi_chunk_u*) ; 
 scalar_t__ AVI_ChunkEnd (union avi_chunk_u*) ; 
 int AVI_ChunkRead (int /*<<< orphan*/ *,union avi_chunk_u*,union avi_chunk_u*) ; 
 int AVI_GotoNextChunk (int /*<<< orphan*/ *,union avi_chunk_u*) ; 
 int AVI_NextChunk (int /*<<< orphan*/ *,union avi_chunk_u*) ; 
 int AVI_ZEROSIZED_CHUNK ; 
 int AVI_ZERO_FOURCC ; 
 scalar_t__ GetFOURCC (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  STREAM_CAN_SEEK ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 union avi_chunk_u* calloc (int,int) ; 
 int /*<<< orphan*/  free (union avi_chunk_u*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_stream_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int) ; 
 int vlc_stream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int AVI_ChunkRead_list( stream_t *s, avi_chunk_t *p_container )
{
    avi_chunk_t *p_chk;
    const uint8_t *p_peek;
    bool b_seekable;
    int i_ret = VLC_SUCCESS;

    if( p_container->common.i_chunk_size > 0 && p_container->common.i_chunk_size < 4 )
    {
        /* empty box */
        msg_Warn( (vlc_object_t*)s, "empty list chunk" );
        return VLC_EGENERIC;
    }
    if( vlc_stream_Peek( s, &p_peek, 12 ) < 12 )
    {
        msg_Warn( (vlc_object_t*)s, "cannot peek while reading list chunk" );
        return VLC_EGENERIC;
    }

    vlc_stream_Control( s, STREAM_CAN_SEEK, &b_seekable );

    p_container->list.i_type = GetFOURCC( p_peek + 8 );

    /* XXX fixed for on2 hack */
    if( p_container->common.i_chunk_fourcc == AVIFOURCC_ON2 && p_container->list.i_type == AVIFOURCC_ON2f )
    {
        p_container->common.i_chunk_fourcc = AVIFOURCC_RIFF;
        p_container->list.i_type = AVIFOURCC_AVI;
    }

    if( p_container->common.i_chunk_fourcc == AVIFOURCC_LIST &&
        p_container->list.i_type == AVIFOURCC_movi )
    {
        if( !b_seekable )
            return VLC_SUCCESS;
        msg_Dbg( (vlc_object_t*)s, "skipping movi chunk" );
        return AVI_NextChunk( s, p_container ); /* points at begining of LIST-movi if not seekable */
    }

    if( vlc_stream_Read( s, NULL, 12 ) != 12 )
    {
        msg_Warn( (vlc_object_t*)s, "cannot enter chunk" );
        return VLC_EGENERIC;
    }

#ifdef AVI_DEBUG
    msg_Dbg( (vlc_object_t*)s,
             "found LIST chunk: \'%4.4s\'",
             (char*)&p_container->list.i_type );
#endif
    msg_Dbg( (vlc_object_t*)s, "<list \'%4.4s\'>", (char*)&p_container->list.i_type );

    union  avi_chunk_u **pp_append = &p_container->common.p_first;
    for( ; ; )
    {
        p_chk = calloc( 1, sizeof( avi_chunk_t ) );
        if( !p_chk )
            return VLC_EGENERIC;

        i_ret = AVI_ChunkRead( s, p_chk, p_container );
        if( i_ret )
        {
            AVI_ChunkClean( s, p_chk );
            free( p_chk );
            p_chk = NULL;
            if( i_ret != AVI_ZEROSIZED_CHUNK )
                break;
        }

        if( p_chk )
        {
            *pp_append = p_chk;
            while( *pp_append )
                pp_append = &((*pp_append)->common.p_next);
        }

        if( p_container->common.i_chunk_size > 0 &&
            vlc_stream_Tell( s ) >= AVI_ChunkEnd( p_container ) )
        {
            break;
        }

        /* If we can't seek then stop when we 've found LIST-movi */
        if( p_chk &&
            p_chk->common.i_chunk_fourcc == AVIFOURCC_LIST &&
            p_chk->list.i_type == AVIFOURCC_movi &&
            ( !b_seekable || p_chk->common.i_chunk_size == 0 ) )
        {
            break;
        }

    }
    msg_Dbg( (vlc_object_t*)s, "</list \'%4.4s\'>%x", (char*)&p_container->list.i_type, i_ret );

    if( i_ret == AVI_ZERO_FOURCC || i_ret == AVI_ZEROSIZED_CHUNK )
        return AVI_GotoNextChunk( s, p_container );

    return VLC_SUCCESS;
}