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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  bo_t ;
struct TYPE_7__ {int i_cat; TYPE_2__* p_bih; int /*<<< orphan*/  i_bih; TYPE_1__* p_wf; } ;
typedef  TYPE_3__ avi_stream_t ;
typedef  int /*<<< orphan*/  VLC_BITMAPINFOHEADER ;
struct TYPE_6__ {int /*<<< orphan*/  biClrImportant; int /*<<< orphan*/  biClrUsed; int /*<<< orphan*/  biYPelsPerMeter; int /*<<< orphan*/  biXPelsPerMeter; int /*<<< orphan*/  biSizeImage; int /*<<< orphan*/  biCompression; int /*<<< orphan*/  biBitCount; int /*<<< orphan*/  biPlanes; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; int /*<<< orphan*/  biSize; } ;
struct TYPE_5__ {int /*<<< orphan*/  cbSize; int /*<<< orphan*/  wBitsPerSample; int /*<<< orphan*/  nBlockAlign; int /*<<< orphan*/  nAvgBytesPerSec; int /*<<< orphan*/  nSamplesPerSec; int /*<<< orphan*/  nChannels; int /*<<< orphan*/  wFormatTag; } ;

/* Variables and functions */
#define  AUDIO_ES 129 
 int /*<<< orphan*/  AVI_BOX_ENTER (char*) ; 
 int /*<<< orphan*/  AVI_BOX_EXIT (int /*<<< orphan*/ ) ; 
#define  VIDEO_ES 128 
 int /*<<< orphan*/  bo_add_16le (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_32le (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int avi_HeaderAdd_strf( bo_t *p_bo, avi_stream_t *p_stream )
{
    AVI_BOX_ENTER( "strf" );

    switch( p_stream->i_cat )
    {
        case AUDIO_ES:
            bo_add_16le( p_bo, p_stream->p_wf->wFormatTag );
            bo_add_16le( p_bo, p_stream->p_wf->nChannels );
            bo_add_32le( p_bo, p_stream->p_wf->nSamplesPerSec );
            bo_add_32le( p_bo, p_stream->p_wf->nAvgBytesPerSec );
            bo_add_16le( p_bo, p_stream->p_wf->nBlockAlign );
            bo_add_16le( p_bo, p_stream->p_wf->wBitsPerSample );
            bo_add_16le( p_bo, p_stream->p_wf->cbSize );
            bo_add_mem( p_bo, p_stream->p_wf->cbSize, (uint8_t*)&p_stream->p_wf[1] );
            break;
        case VIDEO_ES:
            bo_add_32le( p_bo, p_stream->p_bih->biSize );
            bo_add_32le( p_bo, p_stream->p_bih->biWidth );
            bo_add_32le( p_bo, p_stream->p_bih->biHeight );
            bo_add_16le( p_bo, p_stream->p_bih->biPlanes );
            bo_add_16le( p_bo, p_stream->p_bih->biBitCount );
#ifdef WORDS_BIGENDIAN
                bo_add_32be( p_bo, p_stream->p_bih->biCompression );
#else
                bo_add_32le( p_bo, p_stream->p_bih->biCompression );
#endif
            bo_add_32le( p_bo, p_stream->p_bih->biSizeImage );
            bo_add_32le( p_bo, p_stream->p_bih->biXPelsPerMeter );
            bo_add_32le( p_bo, p_stream->p_bih->biYPelsPerMeter );
            bo_add_32le( p_bo, p_stream->p_bih->biClrUsed );
            bo_add_32le( p_bo, p_stream->p_bih->biClrImportant );
            bo_add_mem( p_bo,
                        p_stream->i_bih - sizeof( VLC_BITMAPINFOHEADER ),
                        (uint8_t*)&p_stream->p_bih[1] );
            break;
    }

    AVI_BOX_EXIT( 0 );
}