#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_dictionary_t ;
struct TYPE_10__ {scalar_t__ unit; double i_value; } ;
struct TYPE_9__ {TYPE_2__ font_size; TYPE_4__* font_style; } ;
typedef  TYPE_1__ ttml_style_t ;
typedef  TYPE_2__ ttml_length_t ;
struct TYPE_11__ {int /*<<< orphan*/  root_extent_v; int /*<<< orphan*/  i_cell_resolution_v; } ;
typedef  TYPE_3__ ttml_context_t ;
struct TYPE_12__ {int f_font_relsize; int i_font_size; } ;
typedef  TYPE_4__ text_style_t ;

/* Variables and functions */
 int TTML_LINE_TO_HEIGHT_RATIO ; 
 scalar_t__ TTML_UNIT_CELL ; 
 scalar_t__ TTML_UNIT_PERCENT ; 
 scalar_t__ TTML_UNIT_PIXELS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/  const*) ; 
 TYPE_2__ ttml_rebase_length (int /*<<< orphan*/ ,TYPE_2__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ComputeTTMLStyles( ttml_context_t *p_ctx, const vlc_dictionary_t *p_dict,
                               ttml_style_t *p_ttml_style )
{
    VLC_UNUSED(p_dict);
    /* Values depending on multiple others are converted last
     * Default value conversion must also not depend on attribute presence */
    text_style_t *p_text_style = p_ttml_style->font_style;
    ttml_length_t len = p_ttml_style->font_size;

    /* font size is pixels, cells or, % of cell */
    if( len.unit == TTML_UNIT_PERCENT )
    {
        len.i_value /= 100.0;
        len.unit = TTML_UNIT_CELL;
    }

    /* font size is now pixels or cells */
    /* if cell (and indirectly cell %), rebase as line height depending on resolution */
    if( len.unit == TTML_UNIT_CELL )
        len = ttml_rebase_length( p_ctx->i_cell_resolution_v, len, p_ctx->root_extent_v );

    /* font size is root_extent height % or pixels */
    if( len.unit == TTML_UNIT_PERCENT )
        p_text_style->f_font_relsize = len.i_value / TTML_LINE_TO_HEIGHT_RATIO;
    else
    if( len.unit == TTML_UNIT_PIXELS )
        p_text_style->i_font_size = len.i_value;
}