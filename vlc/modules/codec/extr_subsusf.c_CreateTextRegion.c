#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ i_y_offset; scalar_t__ i_x_offset; scalar_t__ i_height; scalar_t__ i_width; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_17__ {int i_x; int i_y; int i_align; int /*<<< orphan*/ * p_next; int /*<<< orphan*/  p_text; } ;
typedef  TYPE_2__ subpicture_region_t ;
struct TYPE_18__ {int i_align; int i_margin_h; int i_margin_v; int /*<<< orphan*/  p_style; int /*<<< orphan*/  psz_stylename; } ;
typedef  TYPE_3__ ssa_style_t ;
struct TYPE_19__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_20__ {int i_ssa_styles; TYPE_3__** pp_ssa_styles; } ;
typedef  TYPE_5__ decoder_sys_t ;

/* Variables and functions */
 TYPE_3__* ParseStyle (TYPE_5__*,char*) ; 
 int SUBPICTURE_ALIGN_BOTTOM ; 
 int /*<<< orphan*/  SetupPositions (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  VLC_CODEC_TEXT ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* subpicture_region_New (TYPE_1__*) ; 
 int /*<<< orphan*/  text_segment_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_segment_NewInheritStyle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_Clean (TYPE_1__*) ; 
 int /*<<< orphan*/  video_format_Init (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static subpicture_region_t *CreateTextRegion( decoder_t *p_dec,
                                              char *psz_subtitle,
                                              int i_sys_align )
{
    decoder_sys_t        *p_sys = p_dec->p_sys;
    subpicture_region_t  *p_text_region;
    video_format_t        fmt;

    /* Create a new subpicture region */
    video_format_Init( &fmt, VLC_CODEC_TEXT );
    fmt.i_width = fmt.i_height = 0;
    fmt.i_x_offset = fmt.i_y_offset = 0;
    p_text_region = subpicture_region_New( &fmt );
    video_format_Clean( &fmt );

    if( p_text_region != NULL )
    {
        ssa_style_t  *p_ssa_style = NULL;

        p_ssa_style = ParseStyle( p_sys, psz_subtitle );
        if( !p_ssa_style )
        {
            for( int i = 0; i < p_sys->i_ssa_styles; i++ )
            {
                if( !strcasecmp( p_sys->pp_ssa_styles[i]->psz_stylename, "Default" ) )
                    p_ssa_style = p_sys->pp_ssa_styles[i];
            }
        }

        /* Set default or user align/magin.
         * Style overriden if no user value. */
        p_text_region->i_x = i_sys_align > 0 ? 20 : 0;
        p_text_region->i_y = 10;
        p_text_region->i_align = SUBPICTURE_ALIGN_BOTTOM |
                                 ((i_sys_align > 0) ? i_sys_align : 0);

        if( p_ssa_style )
        {
            msg_Dbg( p_dec, "style is: %s", p_ssa_style->psz_stylename );

            /* TODO: Setup % based offsets properly, without adversely affecting
             *       everything else in vlc. Will address with separate patch,
             *       to prevent this one being any more complicated.

                     * p_ssa_style->i_margin_percent_h;
                     * p_ssa_style->i_margin_percent_v;
             */
            if( i_sys_align == -1 )
            {
                p_text_region->i_align     = p_ssa_style->i_align;
                p_text_region->i_x         = p_ssa_style->i_margin_h;
                p_text_region->i_y         = p_ssa_style->i_margin_v;
            }
            p_text_region->p_text = text_segment_NewInheritStyle( p_ssa_style->p_style );
        }
        else
        {
            p_text_region->p_text = text_segment_New( NULL );
        }
        /* Look for position arguments which may override the style-based
         * defaults.
         */
        SetupPositions( p_text_region, psz_subtitle );

        p_text_region->p_next = NULL;
    }
    return p_text_region;
}