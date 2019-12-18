#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
struct TYPE_21__ {int i_sar_num; int i_sar_den; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_width; scalar_t__ i_chroma; } ;
typedef  TYPE_4__ video_format_t ;
struct TYPE_20__ {scalar_t__ i_chroma; unsigned int i_height; unsigned int i_width; } ;
struct TYPE_22__ {TYPE_11__* p_picture; TYPE_3__ fmt; } ;
typedef  TYPE_5__ subpicture_region_t ;
struct TYPE_19__ {scalar_t__ i_chroma; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; } ;
struct TYPE_23__ {TYPE_2__ format; } ;
typedef  TYPE_6__ picture_t ;
typedef  int i_transparent_color ;
struct TYPE_24__ {TYPE_8__* p_sys; } ;
typedef  TYPE_7__ decoder_t ;
struct TYPE_25__ {int i_images; TYPE_1__** pp_images; } ;
typedef  TYPE_8__ decoder_sys_t ;
struct TYPE_18__ {TYPE_6__* p_pic; int /*<<< orphan*/  psz_filename; } ;
struct TYPE_17__ {int* Y_PIXELS; unsigned int Y_PITCH; int* U_PIXELS; unsigned int U_PITCH; int* V_PIXELS; unsigned int V_PITCH; unsigned int A_PITCH; scalar_t__* A_PIXELS; } ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_YUVA ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  picture_CopyPixels (TYPE_11__*,TYPE_6__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_5__* subpicture_region_New (TYPE_4__*) ; 

__attribute__((used)) static subpicture_region_t *LoadEmbeddedImage( decoder_t *p_dec,
                                               const char *psz_filename,
                                               int i_transparent_color )
{
    decoder_sys_t         *p_sys = p_dec->p_sys;
    subpicture_region_t   *p_region;
    video_format_t         fmt_out;
    picture_t             *p_pic = NULL;

    for( int k = 0; k < p_sys->i_images; k++ )
    {
        if( p_sys->pp_images &&
            !strcmp( p_sys->pp_images[k]->psz_filename, psz_filename ) )
        {
            p_pic = p_sys->pp_images[k]->p_pic;
            break;
        }
    }

    if( !p_pic )
    {
        msg_Err( p_dec, "Unable to read image %s", psz_filename );
        return NULL;
    }

    /* Display the feed's image */
    memset( &fmt_out, 0, sizeof( video_format_t));

    fmt_out.i_chroma = VLC_CODEC_YUVA;
    fmt_out.i_sar_num = fmt_out.i_sar_den = 1;
    fmt_out.i_width =
        fmt_out.i_visible_width = p_pic->format.i_visible_width;
    fmt_out.i_height =
        fmt_out.i_visible_height = p_pic->format.i_visible_height;

    p_region = subpicture_region_New( &fmt_out );
    if( !p_region )
    {
        msg_Err( p_dec, "cannot allocate SPU region" );
        return NULL;
    }
    assert( p_pic->format.i_chroma == VLC_CODEC_YUVA );
    /* FIXME the copy is probably not needed anymore */
    picture_CopyPixels( p_region->p_picture, p_pic );

    /* This isn't the best way to do this - if you really want transparency, then
     * you're much better off using an image type that supports it like PNG. The
     * spec requires this support though.
     */
    if( i_transparent_color > 0 )
    {
        int i_r = ( i_transparent_color >> 16 ) & 0xff;
        int i_g = ( i_transparent_color >>  8 ) & 0xff;
        int i_b = ( i_transparent_color       ) & 0xff;

        /* FIXME it cannot work as the yuv conversion code will probably NOT match
         * this one  */
        int i_y = ( ( (  66 * i_r + 129 * i_g +  25 * i_b + 128 ) >> 8 ) + 16 );
        int i_u =   ( ( -38 * i_r -  74 * i_g + 112 * i_b + 128 ) >> 8 ) + 128 ;
        int i_v =   ( ( 112 * i_r -  94 * i_g -  18 * i_b + 128 ) >> 8 ) + 128 ;

        assert( p_region->fmt.i_chroma == VLC_CODEC_YUVA );
        for( unsigned int y = 0; y < p_region->fmt.i_height; y++ )
        {
            for( unsigned int x = 0; x < p_region->fmt.i_width; x++ )
            {
                if( p_region->p_picture->Y_PIXELS[y*p_region->p_picture->Y_PITCH + x] != i_y ||
                    p_region->p_picture->U_PIXELS[y*p_region->p_picture->U_PITCH + x] != i_u ||
                    p_region->p_picture->V_PIXELS[y*p_region->p_picture->V_PITCH + x] != i_v )
                    continue;
                p_region->p_picture->A_PIXELS[y*p_region->p_picture->A_PITCH + x] = 0;

            }
        }
    }
    return p_region;
}