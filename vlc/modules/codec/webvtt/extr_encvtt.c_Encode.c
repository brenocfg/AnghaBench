#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int i_features; int i_style_flags; } ;
typedef  TYPE_2__ text_style_t ;
struct TYPE_22__ {int /*<<< orphan*/ * psz_text; TYPE_2__* style; TYPE_4__* p_ruby; struct TYPE_22__* p_next; } ;
typedef  TYPE_3__ text_segment_t ;
struct TYPE_23__ {int /*<<< orphan*/ * psz_rt; int /*<<< orphan*/ * psz_base; struct TYPE_23__* p_next; } ;
typedef  TYPE_4__ text_segment_ruby_t ;
struct TYPE_24__ {float i_original_picture_height; scalar_t__ i_start; scalar_t__ i_stop; TYPE_6__* p_region; } ;
typedef  TYPE_5__ subpicture_t ;
struct TYPE_20__ {scalar_t__ i_chroma; } ;
struct TYPE_25__ {int i_text_align; int i_align; float i_y; TYPE_3__* p_text; TYPE_1__ fmt; struct TYPE_25__* p_next; } ;
typedef  TYPE_6__ subpicture_region_t ;
typedef  int /*<<< orphan*/  encoder_t ;
struct TYPE_26__ {TYPE_8__* b; } ;
typedef  TYPE_7__ bo_t ;
struct TYPE_27__ {scalar_t__ i_pts; scalar_t__ i_dts; scalar_t__ i_length; } ;
typedef  TYPE_8__ block_t ;

/* Variables and functions */
 int STYLE_BOLD ; 
 int STYLE_HAS_FLAGS ; 
 int STYLE_ITALIC ; 
 int STYLE_UNDERLINE ; 
 int SUBPICTURE_ALIGN_LEFT ; 
 int SUBPICTURE_ALIGN_RIGHT ; 
 int SUBPICTURE_ALIGN_TOP ; 
 scalar_t__ VLC_CODEC_TEXT ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteText (int /*<<< orphan*/ *,TYPE_7__*,char*) ; 
 int /*<<< orphan*/  bo_add_32be (TYPE_7__*,int) ; 
 int /*<<< orphan*/  bo_add_8 (TYPE_7__*,char) ; 
 int /*<<< orphan*/  bo_add_fourcc (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  bo_add_mem (TYPE_7__*,int,char*) ; 
 int /*<<< orphan*/  bo_deinit (TYPE_7__*) ; 
 int /*<<< orphan*/  bo_init (TYPE_7__*,int) ; 
 int /*<<< orphan*/  bo_set_32be (TYPE_7__*,size_t,size_t) ; 
 size_t bo_size (TYPE_7__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int us_asprintf (char**,char*,float) ; 

__attribute__((used)) static block_t *Encode( encoder_t *p_enc, subpicture_t *p_spu )
{
    VLC_UNUSED( p_enc );

    if( p_spu == NULL )
        return NULL;

    bo_t box;
    if( !bo_init( &box, 8 ) )
        return NULL;

    for( subpicture_region_t *p_region = p_spu->p_region;
                              p_region; p_region = p_region->p_next )
    {
        if( p_region->fmt.i_chroma != VLC_CODEC_TEXT ||
            p_region->p_text == NULL ||
            p_region->p_text->psz_text == NULL )
            continue;

        size_t i_offset = bo_size( &box );

        bo_add_32be( &box, 0 );
        bo_add_fourcc( &box, "vttc" );

        /* Payload */

        bo_add_32be( &box, 0 );
        bo_add_fourcc( &box, "payl" );

        char prevchar = '\0';
        /* This should already be UTF-8 encoded, so not much effort... */
        for( const text_segment_t *p_segment = p_region->p_text;
             p_segment; p_segment = p_segment->p_next )
        {
            if( p_segment->psz_text == NULL )
                continue;

            if( p_segment->p_ruby )
            {
                bo_add_mem( &box, 6, "<ruby>" );
                for( const text_segment_ruby_t *p_ruby = p_segment->p_ruby;
                                                p_ruby; p_ruby = p_ruby->p_next )
                {
                    WriteText( p_ruby->psz_base, &box, &prevchar );
                    bo_add_mem( &box, 4, "<rt>" );
                    WriteText( p_ruby->psz_rt, &box, &prevchar );
                    bo_add_mem( &box, 5, "</rt>" );
                }
                bo_add_mem( &box, 7, "</ruby>" );
                continue;
            }

            const text_style_t *style = p_segment->style;
            if( style && style->i_features )
            {
                if( style->i_features & STYLE_HAS_FLAGS )
                {
                    if( style->i_style_flags & STYLE_BOLD )
                        bo_add_mem( &box, 3, "<b>" );
                    if( style->i_style_flags & STYLE_UNDERLINE )
                        bo_add_mem( &box, 3, "<u>" );
                    if( style->i_style_flags & STYLE_ITALIC )
                        bo_add_mem( &box, 3, "<i>" );
                }
            }

            WriteText( p_segment->psz_text, &box, &prevchar );

            if( style && style->i_features )
            {
                if( style->i_features & STYLE_HAS_FLAGS )
                {
                    if( style->i_style_flags & STYLE_BOLD )
                        bo_add_mem( &box, 4, "</b>" );
                    if( style->i_style_flags & STYLE_UNDERLINE )
                        bo_add_mem( &box, 4, "</u>" );
                    if( style->i_style_flags & STYLE_ITALIC )
                        bo_add_mem( &box, 4, "</i>" );
                }
            }
        }

        bo_set_32be( &box, i_offset + 8, bo_size( &box ) - i_offset - 8 );

        /* Settings */

        if( (p_region->i_text_align & (SUBPICTURE_ALIGN_LEFT|SUBPICTURE_ALIGN_RIGHT)) ||
                (p_region->i_align & SUBPICTURE_ALIGN_TOP) )
        {
            size_t i_start = bo_size( &box );

            bo_add_32be( &box, 0 );
            bo_add_fourcc( &box, "sttg" );

            if( p_region->i_text_align & SUBPICTURE_ALIGN_LEFT )
                bo_add_mem( &box, 10, "align:left" );
            else if( p_region->i_text_align & SUBPICTURE_ALIGN_RIGHT )
                bo_add_mem( &box, 11, "align:right" );

            if( p_region->i_align & SUBPICTURE_ALIGN_TOP )
            {
                float offset = 100.0;
                if( p_spu->i_original_picture_height > 0 )
                    offset = offset * p_region->i_y / p_spu->i_original_picture_height;
                if( bo_size( &box ) != i_start + 8 )
                    bo_add_8( &box, ' ' );
                char *psz;
                int i_printed = us_asprintf( &psz, "line:%2.2f%%", offset );
                if( i_printed >= 0 )
                {
                    if( i_printed > 0 )
                        bo_add_mem( &box, i_printed, psz );
                    free( psz );
                }
            }
            bo_set_32be( &box, i_start, bo_size( &box ) - i_start );
        }


        bo_set_32be( &box, i_offset, bo_size( &box ) - i_offset );
    }

    if( bo_size( &box ) == 0 ) /* No cue */
    {
        bo_add_32be( &box, 8 );
        bo_add_fourcc( &box, "vtte" );
    }

    block_t *p_block = box.b;
    box.b = NULL;
    bo_deinit( &box );

    if( p_block )
    {
        p_block->i_pts = p_block->i_dts = p_spu->i_start;
        if( p_spu->i_stop > p_spu->i_start )
            p_block->i_length = p_spu->i_stop - p_spu->i_start;
    }

    return p_block;
}