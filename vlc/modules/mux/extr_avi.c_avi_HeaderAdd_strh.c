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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  bo_t ;
struct TYPE_7__ {int i_cat; int f_fps; int i_frames; int i_bitrate; TYPE_2__* p_wf; TYPE_1__* p_bih; } ;
typedef  TYPE_3__ avi_stream_t ;
struct TYPE_6__ {int nBlockAlign; } ;
struct TYPE_5__ {int biCompression; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; int /*<<< orphan*/  biBitCount; } ;

/* Variables and functions */
#define  AUDIO_ES 129 
 int /*<<< orphan*/  AVI_BOX_ENTER (char*) ; 
 int /*<<< orphan*/  AVI_BOX_EXIT (int /*<<< orphan*/ ) ; 
#define  VIDEO_ES 128 
 int /*<<< orphan*/  bo_add_16le (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_32le (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_fourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int avi_HeaderAdd_strh( bo_t *p_bo, avi_stream_t *p_stream )
{
    AVI_BOX_ENTER( "strh" );

    switch( p_stream->i_cat )
    {
        case VIDEO_ES:
            {
                bo_add_fourcc( p_bo, "vids" );
                if( p_stream->p_bih->biBitCount )
                    bo_add_fourcc( p_bo, "DIB " );
                else
#ifdef WORDS_BIGENDIAN
                bo_add_32be( p_bo, p_stream->p_bih->biCompression );
#else
                bo_add_32le( p_bo, p_stream->p_bih->biCompression );
#endif
                bo_add_32le( p_bo, 0 );   /* flags */
                bo_add_16le(  p_bo, 0 );   /* priority */
                bo_add_16le(  p_bo, 0 );   /* langage */
                bo_add_32le( p_bo, 0 );   /* initial frame */
                bo_add_32le( p_bo, 1000 );/* scale */
                bo_add_32le( p_bo, (uint32_t)( 1000 * p_stream->f_fps ));
                bo_add_32le( p_bo, 0 );   /* start */
                bo_add_32le( p_bo, p_stream->i_frames );
                bo_add_32le( p_bo, 1024 * 1024 );
                bo_add_32le( p_bo, -1 );  /* quality */
                bo_add_32le( p_bo, 0 );   /* samplesize */
                bo_add_16le(  p_bo, 0 );   /* ??? */
                bo_add_16le(  p_bo, 0 );   /* ??? */
                bo_add_16le(  p_bo, p_stream->p_bih->biWidth );
                bo_add_16le(  p_bo, p_stream->p_bih->biHeight );
            }
            break;
        case AUDIO_ES:
            {
                int i_rate, i_scale, i_samplesize;

                i_samplesize = p_stream->p_wf->nBlockAlign;
                if( i_samplesize > 1 )
                {
                    i_scale = i_samplesize;
                    i_rate = /*i_scale **/ p_stream->i_bitrate / 8;
                }
                else
                {
                    i_samplesize = 1;
                    i_scale = 1000;
                    i_rate = 1000 * p_stream->i_bitrate / 8;
                }
                bo_add_fourcc( p_bo, "auds" );
                bo_add_32le( p_bo, 0 );   /* tag */
                bo_add_32le( p_bo, 0 );   /* flags */
                bo_add_16le(  p_bo, 0 );   /* priority */
                bo_add_16le(  p_bo, 0 );   /* langage */
                bo_add_32le( p_bo, 0 );   /* initial frame */
                bo_add_32le( p_bo, i_scale );/* scale */
                bo_add_32le( p_bo, i_rate );
                bo_add_32le( p_bo, 0 );   /* start */
                bo_add_32le( p_bo, p_stream->i_frames );
                bo_add_32le( p_bo, 10 * 1024 );
                bo_add_32le( p_bo, -1 );  /* quality */
                bo_add_32le( p_bo, i_samplesize );
                bo_add_16le(  p_bo, 0 );   /* ??? */
                bo_add_16le(  p_bo, 0 );   /* ??? */
                bo_add_16le(  p_bo, 0 );
                bo_add_16le(  p_bo, 0 );
            }
            break;
    }

    AVI_BOX_EXIT( 0 );
}