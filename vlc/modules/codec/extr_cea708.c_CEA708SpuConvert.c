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
struct TYPE_13__ {struct TYPE_13__* p_next; } ;
typedef  TYPE_3__ text_segment_t ;
struct TYPE_12__ {double x; double y; } ;
struct TYPE_14__ {int flags; int align; int inner_align; TYPE_2__ origin; TYPE_3__* p_segments; } ;
typedef  TYPE_4__ substext_updater_region_t ;
struct TYPE_11__ {scalar_t__ scroll_direction; } ;
struct TYPE_15__ {int i_lastrow; int i_row_count; int i_firstrow; double i_anchor_offset_h; int anchor_point; double i_anchor_offset_v; scalar_t__ b_relative; int /*<<< orphan*/ * rows; TYPE_1__ style; int /*<<< orphan*/  b_visible; } ;
typedef  TYPE_5__ cea708_window_t ;

/* Variables and functions */
 TYPE_3__* CEA708RowToSegments (int /*<<< orphan*/ ,int) ; 
#define  CEA708_ANCHOR_BOTTOM_CENTER 140 
#define  CEA708_ANCHOR_BOTTOM_LEFT 139 
#define  CEA708_ANCHOR_BOTTOM_RIGHT 138 
#define  CEA708_ANCHOR_CENTER_CENTER 137 
#define  CEA708_ANCHOR_CENTER_LEFT 136 
#define  CEA708_ANCHOR_CENTER_RIGHT 135 
#define  CEA708_ANCHOR_TOP_CENTER 134 
#define  CEA708_ANCHOR_TOP_LEFT 133 
#define  CEA708_ANCHOR_TOP_RIGHT 132 
 float CEA708_FONT_TO_LINE_HEIGHT_RATIO ; 
 int CEA708_ROW_HEIGHT_STANDARD ; 
 float CEA708_SCREEN_COLS_169 ; 
 float CEA708_SCREEN_ROWS ; 
 scalar_t__ CEA708_WA_DIRECTION_BT ; 
 scalar_t__ CEA708_Window_RowCount (TYPE_5__ const*) ; 
#define  SUBPICTURE_ALIGN_BOTTOM 131 
#define  SUBPICTURE_ALIGN_LEFT 130 
#define  SUBPICTURE_ALIGN_RIGHT 129 
#define  SUBPICTURE_ALIGN_TOP 128 
 TYPE_4__* SubpictureUpdaterSysRegionNew () ; 
 int UPDT_REGION_ORIGIN_X_IS_RATIO ; 
 int UPDT_REGION_ORIGIN_Y_IS_RATIO ; 

__attribute__((used)) static void CEA708SpuConvert( const cea708_window_t *p_w,
                              substext_updater_region_t *p_region )
{
    if( !p_w->b_visible || CEA708_Window_RowCount( p_w ) == 0 )
        return;

    if( p_region == NULL && !(p_region = SubpictureUpdaterSysRegionNew()) )
        return;

    int first, last;

    if (p_w->style.scroll_direction == CEA708_WA_DIRECTION_BT) {
        /* BT is a bit of a special case since we need to grab the last N
           rows between first and last, rather than the first... */
        last = p_w->i_lastrow;
        if (p_w->i_lastrow - p_w->i_row_count < p_w->i_firstrow)
            first = p_w->i_firstrow;
        else
            first = p_w->i_lastrow - p_w->i_row_count + 1;

    } else {
        first = p_w->i_firstrow;
        if (p_w->i_firstrow + p_w->i_row_count > p_w->i_lastrow)
            last = p_w->i_lastrow;
        else
            last = p_w->i_firstrow + p_w->i_row_count - 1;
    }

    text_segment_t **pp_last = &p_region->p_segments;
    for( uint8_t i=first; i<=last; i++ )
    {
        if( !p_w->rows[i] )
            continue;

        *pp_last = CEA708RowToSegments( p_w->rows[i], i < p_w->i_lastrow );
        if( *pp_last )
            pp_last  = &((*pp_last)->p_next);
    }

    if( p_w->b_relative )
    {
        /* FIXME: take into account left/right anchors */
        p_region->origin.x = p_w->i_anchor_offset_h / 100.0;

        switch (p_w->anchor_point) {
        case CEA708_ANCHOR_TOP_LEFT:
        case CEA708_ANCHOR_TOP_CENTER:
        case CEA708_ANCHOR_TOP_RIGHT:
            p_region->origin.y = p_w->i_anchor_offset_v / 100.0;
            break;
        case CEA708_ANCHOR_BOTTOM_LEFT:
        case CEA708_ANCHOR_BOTTOM_CENTER:
        case CEA708_ANCHOR_BOTTOM_RIGHT:
            p_region->origin.y = 1.0 - (p_w->i_anchor_offset_v / 100.0);
            break;
        default:
            /* FIXME: for CENTER vertical justified, just position as top */
            p_region->origin.y = p_w->i_anchor_offset_v / 100.0;
            break;
        }
    }
    else
    {
        p_region->origin.x = (float)p_w->i_anchor_offset_h / CEA708_SCREEN_COLS_169;
        p_region->origin.y = (float)p_w->i_anchor_offset_v /
                             (CEA708_SCREEN_ROWS * CEA708_FONT_TO_LINE_HEIGHT_RATIO);
    }
    p_region->flags |= UPDT_REGION_ORIGIN_X_IS_RATIO|UPDT_REGION_ORIGIN_Y_IS_RATIO;

    if( p_w->i_firstrow <= p_w->i_lastrow )
    {
        p_region->origin.y += p_w->i_firstrow * CEA708_ROW_HEIGHT_STANDARD;
        /*const uint8_t i_min = CEA708_Window_MinCol( p_w );
        if( i_min < CEA708_WINDOW_MAX_COLS )
            p_region->origin.x += (float) i_min / CEA708_WINDOW_MAX_COLS;*/
    }

    if( p_w->anchor_point <= CEA708_ANCHOR_BOTTOM_RIGHT )
    {
        static const int vlc_subpicture_aligns[] =
        {
            [CEA708_ANCHOR_TOP_LEFT]        = SUBPICTURE_ALIGN_TOP|SUBPICTURE_ALIGN_LEFT,
            [CEA708_ANCHOR_TOP_CENTER]      = SUBPICTURE_ALIGN_TOP,
            [CEA708_ANCHOR_TOP_RIGHT]       = SUBPICTURE_ALIGN_TOP|SUBPICTURE_ALIGN_RIGHT,
            [CEA708_ANCHOR_CENTER_LEFT]     = SUBPICTURE_ALIGN_LEFT,
            [CEA708_ANCHOR_CENTER_CENTER]   = 0,
            [CEA708_ANCHOR_CENTER_RIGHT]    = SUBPICTURE_ALIGN_RIGHT,
            [CEA708_ANCHOR_BOTTOM_LEFT]     = SUBPICTURE_ALIGN_BOTTOM|SUBPICTURE_ALIGN_LEFT,
            [CEA708_ANCHOR_BOTTOM_CENTER]   = SUBPICTURE_ALIGN_BOTTOM,
            [CEA708_ANCHOR_BOTTOM_RIGHT]    = SUBPICTURE_ALIGN_BOTTOM|SUBPICTURE_ALIGN_RIGHT,
        };
        p_region->align = vlc_subpicture_aligns[p_w->anchor_point];
    }
    p_region->inner_align = SUBPICTURE_ALIGN_BOTTOM|SUBPICTURE_ALIGN_LEFT;
}