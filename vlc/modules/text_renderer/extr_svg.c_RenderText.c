#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_15__ {int /*<<< orphan*/  fmt; TYPE_4__* p_picture; TYPE_9__* p_text; scalar_t__ i_y; scalar_t__ i_x; } ;
typedef  TYPE_3__ subpicture_region_t ;
struct TYPE_16__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_13__ {unsigned int i_visible_width; unsigned int i_visible_height; } ;
struct TYPE_14__ {TYPE_1__ video; } ;
struct TYPE_17__ {TYPE_2__ fmt_out; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_18__ {int /*<<< orphan*/  psz_text; } ;

/* Variables and functions */
 char* SegmentsToSVG (TYPE_9__*,unsigned int,int*) ; 
 scalar_t__ const VLC_CODEC_BGRA ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 char* svg_GetDocument (TYPE_5__*,unsigned int,int,char*) ; 
 TYPE_4__* svg_RenderPicture (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int RenderText( filter_t *p_filter, subpicture_region_t *p_region_out,
                       subpicture_region_t *p_region_in,
                       const vlc_fourcc_t *p_chroma_list )
{
    /* Sanity check */
    if( !p_region_in || !p_region_out || !p_region_in->p_text )
        return VLC_EGENERIC;

    for( size_t i=0; p_chroma_list[i]; i++ )
    {
        if( p_chroma_list[i] == VLC_CODEC_BGRA )
            break;
        if( p_chroma_list[i] == 0 )
            return VLC_EGENERIC;
    }

    p_region_out->i_x = p_region_in->i_x;
    p_region_out->i_y = p_region_in->i_y;

    unsigned i_width = p_filter->fmt_out.video.i_visible_width;
    if( (unsigned) p_region_out->i_x <= i_width )
        i_width -= p_region_out->i_x;

    unsigned i_height = p_filter->fmt_out.video.i_visible_height;
    if( (unsigned) p_region_out->i_y <= i_height )
        i_height -= p_region_out->i_y;

    if( i_height == 0 || i_width == 0 )
        return VLC_EGENERIC;

    char *psz_svg;
    /* Check if the data is SVG or pure text. In the latter case,
       convert the text to SVG. FIXME: find a better test */
    if( p_region_in->p_text && strstr( p_region_in->p_text->psz_text, "<svg" ) )
    {
        psz_svg = strdup( p_region_in->p_text->psz_text );
    }
    else
    {
        /* Data is text. Convert to SVG */
        int i_total;
        psz_svg = SegmentsToSVG( p_region_in->p_text, i_height, &i_total );
        if( psz_svg )
        {
            char *psz_doc = svg_GetDocument( p_filter, i_width, i_total, psz_svg );
            free( psz_svg );
            psz_svg = psz_doc;
        }
    }

    if( !psz_svg )
        return VLC_EGENERIC;

    picture_t *p_picture = svg_RenderPicture( p_filter, psz_svg );

    free( psz_svg );

    if (p_picture)
    {
        p_region_out->p_picture = p_picture;
        video_format_Clean( &p_region_out->fmt );
        video_format_Copy( &p_region_out->fmt, &p_picture->format );
        return VLC_SUCCESS;
    }
    return VLC_EGENERIC;
}