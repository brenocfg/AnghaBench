#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ unit; } ;
struct TYPE_21__ {int b_preserve_space; scalar_t__ display; int i_text_align; int /*<<< orphan*/  origin_v; TYPE_12__ origin_h; int /*<<< orphan*/  extent_v; TYPE_12__ extent_h; scalar_t__ b_text_align_set; int /*<<< orphan*/  i_direction; scalar_t__ b_direction_set; TYPE_1__* font_style; } ;
typedef  TYPE_2__ ttml_style_t ;
struct TYPE_19__ {int inner_align; } ;
struct TYPE_22__ {TYPE_5__** pp_last_segment; TYPE_13__ updt; } ;
typedef  TYPE_3__ ttml_region_t ;
typedef  int /*<<< orphan*/  ttml_context_t ;
struct TYPE_23__ {int /*<<< orphan*/  p_parent; int /*<<< orphan*/  psz_text; } ;
typedef  TYPE_4__ tt_textnode_t ;
struct TYPE_24__ {struct TYPE_24__* p_next; TYPE_1__* style; } ;
typedef  TYPE_5__ text_segment_t ;
struct TYPE_20__ {int i_features; int /*<<< orphan*/  i_font_alpha; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIDIConvert (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillUpdaterCoords (int /*<<< orphan*/ *,TYPE_12__,int /*<<< orphan*/ ,int,TYPE_13__*) ; 
 TYPE_2__* InheritTTMLStyles (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STYLE_ALPHA_TRANSPARENT ; 
 int STYLE_BACKGROUND ; 
 int STYLE_HAS_FONT_ALPHA ; 
 int STYLE_OUTLINE ; 
 int STYLE_SHADOW ; 
 int STYLE_STRIKEOUT ; 
 int SUBPICTURE_ALIGN_LEFT ; 
 int SUBPICTURE_ALIGN_RIGHT ; 
 int /*<<< orphan*/  StripSpacing (TYPE_5__*) ; 
 scalar_t__ TTML_DISPLAY_NONE ; 
 scalar_t__ TTML_UNIT_UNKNOWN ; 
 TYPE_5__* text_segment_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttml_style_Delete (TYPE_2__*) ; 
 int /*<<< orphan*/  ttml_style_Merge (TYPE_2__ const*,TYPE_2__*) ; 

__attribute__((used)) static void AppendTextToRegion( ttml_context_t *p_ctx, const tt_textnode_t *p_ttnode,
                                const ttml_style_t *p_set_styles, ttml_region_t *p_region )
{
    text_segment_t *p_segment;

    if( p_region == NULL )
        return;

    p_segment = text_segment_New( p_ttnode->psz_text );
    if( p_segment )
    {
        bool b_preserve_space = false;
        ttml_style_t *s = InheritTTMLStyles( p_ctx, p_ttnode->p_parent );
        if( s )
        {
            if( p_set_styles )
                ttml_style_Merge( p_set_styles, s );

            p_segment->style = s->font_style;
            s->font_style = NULL;

            b_preserve_space = s->b_preserve_space;
            if( s->b_direction_set )
                BIDIConvert( p_segment, s->i_direction );

            if( s->display == TTML_DISPLAY_NONE )
            {
                /* Must not display, but still occupies space */
                p_segment->style->i_features &= ~(STYLE_BACKGROUND|STYLE_OUTLINE|STYLE_STRIKEOUT|STYLE_SHADOW);
                p_segment->style->i_font_alpha = STYLE_ALPHA_TRANSPARENT;
                p_segment->style->i_features |= STYLE_HAS_FONT_ALPHA;
            }

            /* we don't have paragraph, so no per text line alignment.
             * Text style brings horizontal textAlign to region.
             * Region itself is styled with vertical displayAlign */
            if( s->b_text_align_set )
            {
                p_region->updt.inner_align &= ~(SUBPICTURE_ALIGN_LEFT|SUBPICTURE_ALIGN_RIGHT);
                p_region->updt.inner_align |= s->i_text_align;
            }

            if( s->extent_h.unit != TTML_UNIT_UNKNOWN )
                FillUpdaterCoords( p_ctx, s->extent_h, s->extent_v, false, &p_region->updt );

            if( s->origin_h.unit != TTML_UNIT_UNKNOWN )
                FillUpdaterCoords( p_ctx, s->origin_h, s->origin_v, true, &p_region->updt );

            ttml_style_Delete( s );
        }

        if( !b_preserve_space )
            StripSpacing( p_segment );
    }

    *p_region->pp_last_segment = p_segment;
    p_region->pp_last_segment = &p_segment->p_next;
}