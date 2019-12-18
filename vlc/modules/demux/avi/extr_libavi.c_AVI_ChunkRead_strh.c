#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_4__ {scalar_t__ i_scale; scalar_t__ i_rate; scalar_t__ i_samplesize; int /*<<< orphan*/  i_handler; int /*<<< orphan*/  i_type; scalar_t__ i_quality; scalar_t__ i_suggestedbuffersize; scalar_t__ i_length; scalar_t__ i_start; scalar_t__ i_initialframes; scalar_t__ i_reserved1; scalar_t__ i_flags; } ;
struct TYPE_5__ {TYPE_1__ strh; } ;
typedef  TYPE_2__ avi_chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_READ4BYTES (scalar_t__) ; 
 int /*<<< orphan*/  AVI_READCHUNK_ENTER ; 
 int /*<<< orphan*/  AVI_READCHUNK_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVI_READFOURCC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,scalar_t__,float) ; 

__attribute__((used)) static int AVI_ChunkRead_strh( stream_t *s, avi_chunk_t *p_chk )
{
    AVI_READCHUNK_ENTER;

    AVI_READFOURCC( p_chk->strh.i_type );
    AVI_READFOURCC( p_chk->strh.i_handler );
    AVI_READ4BYTES( p_chk->strh.i_flags );
    AVI_READ4BYTES( p_chk->strh.i_reserved1 );
    AVI_READ4BYTES( p_chk->strh.i_initialframes );
    AVI_READ4BYTES( p_chk->strh.i_scale );
    AVI_READ4BYTES( p_chk->strh.i_rate );
    AVI_READ4BYTES( p_chk->strh.i_start );
    AVI_READ4BYTES( p_chk->strh.i_length );
    AVI_READ4BYTES( p_chk->strh.i_suggestedbuffersize );
    AVI_READ4BYTES( p_chk->strh.i_quality );
    AVI_READ4BYTES( p_chk->strh.i_samplesize );
#ifdef AVI_DEBUG
    msg_Dbg( (vlc_object_t*)s,
             "strh: type:%4.4s handler:0x%8.8x samplesize:%d %.2ffps",
             (char*)&p_chk->strh.i_type,
             p_chk->strh.i_handler,
             p_chk->strh.i_samplesize,
             ( p_chk->strh.i_scale ?
                (float)p_chk->strh.i_rate / (float)p_chk->strh.i_scale : -1) );
#endif

    AVI_READCHUNK_EXIT( VLC_SUCCESS );
}