#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  unsigned int uint32_t ;
struct TYPE_11__ {int i_bmask; int i_rmask; int i_gmask; } ;
struct TYPE_12__ {TYPE_1__ video; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_13__ {int i_buffer; int* p_buffer; } ;
typedef  TYPE_3__ block_t ;
struct TYPE_14__ {scalar_t__ i_frames; scalar_t__ i_cat; TYPE_5__* p_bih; } ;
typedef  TYPE_4__ avi_stream_t ;
typedef  int /*<<< orphan*/  VLC_BITMAPINFOHEADER ;
struct TYPE_15__ {scalar_t__ biCompression; int biSize; int biBitCount; } ;

/* Variables and functions */
 scalar_t__ BI_RGB ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_ENOMEM ; 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 
 int VLC_SUCCESS ; 
 TYPE_3__* block_Realloc (TYPE_3__*,size_t,int) ; 
 unsigned int ctz (int) ; 
 int /*<<< orphan*/  memcpy (int*,TYPE_5__*,size_t) ; 

__attribute__((used)) static int PrepareSamples( const avi_stream_t *p_stream,
                           const es_format_t *p_fmt,
                           block_t **pp_block )
{
    if( p_stream->i_frames == 0 && p_stream->i_cat == VIDEO_ES )
    {
       /* Add header present at the end of BITMAP info header
          to first frame in case of XVID */
       if( p_stream->p_bih->biCompression == VLC_FOURCC( 'X', 'V', 'I', 'D' ) )
       {
           size_t i_header_length =
               p_stream->p_bih->biSize - sizeof(VLC_BITMAPINFOHEADER);
           *pp_block = block_Realloc( *pp_block, i_header_length,
                                      (*pp_block)->i_buffer );
           if( !*pp_block )
               return VLC_ENOMEM;
           memcpy((*pp_block)->p_buffer,&p_stream->p_bih[1], i_header_length);
       }
    }

    /* RV24 is only BGR in AVI, and we can't use BI_BITFIELD */
    if( p_stream->i_cat == VIDEO_ES &&
        p_stream->p_bih->biCompression == BI_RGB &&
        p_stream->p_bih->biBitCount == 24 &&
        (p_fmt->video.i_bmask != 0xFF0000 ||
         p_fmt->video.i_rmask != 0x0000FF) )
    {
        unsigned rshift = ctz(p_fmt->video.i_rmask);
        unsigned gshift = ctz(p_fmt->video.i_gmask);
        unsigned bshift = ctz(p_fmt->video.i_bmask);

        uint8_t *p_data = (*pp_block)->p_buffer;
        for( size_t i=0; i<(*pp_block)->i_buffer / 3; i++ )
        {
            uint8_t *p = &p_data[i*3];
            /* reorder as BGR using shift value (done by FixRGB) */
            uint32_t v = (p[0] << 16) | (p[1] << 8) | p[2];
            p[0] = (v & p_fmt->video.i_bmask) >> bshift;
            p[1] = (v & p_fmt->video.i_gmask) >> gshift;
            p[2] = (v & p_fmt->video.i_rmask) >> rshift;
        }
    }

    return VLC_SUCCESS;
}