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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {int i_microsecperframe; int i_maxbytespersec; int i_reserved1; int i_flags; int i_totalframes; int i_initialframes; int i_streams; int i_suggestedbuffersize; int i_width; int i_height; int i_scale; int i_rate; int i_start; int i_length; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_chunk_fourcc; } ;
struct TYPE_7__ {TYPE_2__ avih; TYPE_1__ common; } ;
typedef  TYPE_3__ avi_chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVIFOURCC_avih ; 
 int AVIF_HASINDEX ; 
 int AVIF_ISINTERLEAVED ; 
 int AVIF_MUSTUSEINDEX ; 
 int AVIF_TRUSTCKTYPE ; 
 int /*<<< orphan*/  AVI_READ4BYTES (int) ; 
 int /*<<< orphan*/  AVI_READCHUNK_ENTER ; 
 int /*<<< orphan*/  AVI_READCHUNK_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int,char*,char*,char*,char*,int,int) ; 

__attribute__((used)) static int AVI_ChunkRead_avih( stream_t *s, avi_chunk_t *p_chk )
{
    AVI_READCHUNK_ENTER;

    p_chk->common.i_chunk_fourcc = AVIFOURCC_avih;
    AVI_READ4BYTES( p_chk->avih.i_microsecperframe);
    AVI_READ4BYTES( p_chk->avih.i_maxbytespersec );
    AVI_READ4BYTES( p_chk->avih.i_reserved1 );
    AVI_READ4BYTES( p_chk->avih.i_flags );
    AVI_READ4BYTES( p_chk->avih.i_totalframes );
    AVI_READ4BYTES( p_chk->avih.i_initialframes );
    AVI_READ4BYTES( p_chk->avih.i_streams );
    AVI_READ4BYTES( p_chk->avih.i_suggestedbuffersize );
    AVI_READ4BYTES( p_chk->avih.i_width );
    AVI_READ4BYTES( p_chk->avih.i_height );
    AVI_READ4BYTES( p_chk->avih.i_scale );
    AVI_READ4BYTES( p_chk->avih.i_rate );
    AVI_READ4BYTES( p_chk->avih.i_start );
    AVI_READ4BYTES( p_chk->avih.i_length );
#ifdef AVI_DEBUG
    msg_Dbg( (vlc_object_t*)s,
             "avih: streams:%d flags:%s%s%s%s %dx%d",
             p_chk->avih.i_streams,
             p_chk->avih.i_flags&AVIF_HASINDEX?" HAS_INDEX":"",
             p_chk->avih.i_flags&AVIF_MUSTUSEINDEX?" MUST_USE_INDEX":"",
             p_chk->avih.i_flags&AVIF_ISINTERLEAVED?" IS_INTERLEAVED":"",
             p_chk->avih.i_flags&AVIF_TRUSTCKTYPE?" TRUST_CKTYPE":"",
             p_chk->avih.i_width, p_chk->avih.i_height );
#endif
    AVI_READCHUNK_EXIT( VLC_SUCCESS );
}