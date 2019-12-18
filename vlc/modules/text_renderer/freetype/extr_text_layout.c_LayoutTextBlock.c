#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  p_laid; int /*<<< orphan*/  p_style; int /*<<< orphan*/  i_count; int /*<<< orphan*/  p_uchars; } ;
typedef  TYPE_1__ ruby_block_t ;
typedef  int /*<<< orphan*/  paragraph_t ;
struct TYPE_11__ {int yMin; int yMax; } ;
struct TYPE_13__ {int i_height; int i_base_line; TYPE_10__ bbox; struct TYPE_13__* p_next; } ;
typedef  TYPE_2__ line_desc_t ;
struct TYPE_14__ {size_t i_count; char* p_uchars; unsigned int i_max_height; int /*<<< orphan*/  b_balanced; int /*<<< orphan*/  b_grid; int /*<<< orphan*/  i_max_width; TYPE_1__** pp_ruby; int /*<<< orphan*/ * pp_styles; } ;
typedef  TYPE_3__ layout_text_block_t ;
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  FT_BBox ;

/* Variables and functions */
 int /*<<< orphan*/  BBoxEnlarge (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  BBoxInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BuildParagraph (int /*<<< orphan*/ *,size_t,char*,int /*<<< orphan*/ *,TYPE_1__**,int,unsigned int*) ; 
 int /*<<< orphan*/  FreeLine (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeLines (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeParagraph (int /*<<< orphan*/ *) ; 
 scalar_t__ LayoutParagraph (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  LayoutRubyText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 

int LayoutTextBlock( filter_t *p_filter,
                     const layout_text_block_t *p_textblock,
                     line_desc_t **pp_lines, FT_BBox *p_bbox,
                     int *pi_max_face_height )
{
    line_desc_t *p_first_line = 0;
    line_desc_t **pp_line = &p_first_line;
    size_t i_paragraph_start = 0;
    unsigned i_total_height = 0;
    unsigned i_max_advance_x = 0;
    int i_max_face_height = 0;

    /* Prepare ruby content */
    if( p_textblock->pp_ruby )
    {
        ruby_block_t *p_prev = NULL;
        for( size_t i=0; i<p_textblock->i_count; i++ )
        {
            if( p_textblock->pp_ruby[i] == p_prev )
                continue;
            p_prev = p_textblock->pp_ruby[i];
            if( p_prev )
                LayoutRubyText( p_filter, p_prev->p_uchars, p_prev->i_count,
                                p_prev->p_style, &p_prev->p_laid );
        }
    }
    /* !Prepare ruby content */

    for( size_t i = 0; i <= p_textblock->i_count; ++i )
    {
        if( i == p_textblock->i_count || p_textblock->p_uchars[ i ] == '\n' )
        {
            if( i_paragraph_start == i )
            {
                i_paragraph_start = i + 1;
                continue;
            }

            paragraph_t *p_paragraph =
                    BuildParagraph( p_filter,
                                    i - i_paragraph_start,
                                    &p_textblock->p_uchars[i_paragraph_start],
                                    &p_textblock->pp_styles[i_paragraph_start],
                                    p_textblock->pp_ruby ?
                                    &p_textblock->pp_ruby[i_paragraph_start] : NULL,
                                    20, &i_max_advance_x );
            if( !p_paragraph )
            {
                if( p_first_line ) FreeLines( p_first_line );
                return VLC_ENOMEM;
            }

            if( LayoutParagraph( p_filter, p_paragraph,
                                 p_textblock->i_max_width,
                                 i_max_advance_x,
                                 p_textblock->b_grid, p_textblock->b_balanced,
                                 pp_line ) )
            {
                FreeParagraph( p_paragraph );
                if( p_first_line ) FreeLines( p_first_line );
                return VLC_EGENERIC;
            }

            FreeParagraph( p_paragraph );

            for( ; *pp_line; pp_line = &(*pp_line)->p_next )
            {
                /* only cut at max i_max_height + 1 line due to
                 * approximate font sizing vs region size */
                if( p_textblock->i_max_height > 0 && i_total_height > p_textblock->i_max_height )
                {
                    i_total_height = p_textblock->i_max_height + 1;
                    line_desc_t *p_todelete = *pp_line;
                    while( p_todelete ) /* Drop extra lines */
                    {
                        line_desc_t *p_next = p_todelete->p_next;
                        FreeLine( p_todelete );
                        p_todelete = p_next;
                    }
                    *pp_line = NULL;
                    i = p_textblock->i_count + 1; /* force no more paragraphs */
                    break; /* ! no p_next ! */
                }
                else if( (*pp_line)->i_height > i_max_face_height )
                {
                    i_max_face_height = (*pp_line)->i_height;
                }
                i_total_height += (*pp_line)->i_height;
            }
            i_paragraph_start = i + 1;
        }
    }

    int i_base_line = 0;
    FT_BBox bbox;
    BBoxInit( &bbox );

    for( line_desc_t *p_line = p_first_line; p_line; p_line = p_line->p_next )
    {
        p_line->i_base_line = i_base_line;
        p_line->bbox.yMin -= i_base_line;
        p_line->bbox.yMax -= i_base_line;
        BBoxEnlarge( &bbox, &p_line->bbox );

        i_base_line += i_max_face_height;
    }

    *pi_max_face_height = i_max_face_height;
    *pp_lines = p_first_line;
    *p_bbox = bbox;
    return VLC_SUCCESS;
}