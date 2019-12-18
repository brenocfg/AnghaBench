#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text_style_t ;
struct TYPE_5__ {scalar_t__ i_size; scalar_t__* p_scripts; scalar_t__* p_levels; int /*<<< orphan*/ ** pp_styles; } ;
typedef  TYPE_1__ paragraph_t ;
typedef  scalar_t__ hb_script_t ;
typedef  int /*<<< orphan*/  filter_t ;
typedef  scalar_t__ FriBidiLevel ;

/* Variables and functions */
 int AddRun (int /*<<< orphan*/ *,TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int AddRunWithFallback (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  FaceStyleEquals (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static int ItemizeParagraph( filter_t *p_filter, paragraph_t *p_paragraph )
{
    if( p_paragraph->i_size <= 0 )
    {
        msg_Err( p_filter,
                 "ItemizeParagraph() invalid parameters. Paragraph size: %d",
                 p_paragraph->i_size );
        return VLC_EGENERIC;
    }

    int i_last_run_start = 0;
    const text_style_t *p_last_style = p_paragraph->pp_styles[ 0 ];

#ifdef HAVE_HARFBUZZ
    hb_script_t last_script = p_paragraph->p_scripts[ 0 ];
    FriBidiLevel last_level = p_paragraph->p_levels[ 0 ];
#endif

    for( int i = 0; i <= p_paragraph->i_size; ++i )
    {
        if( i == p_paragraph->i_size
#ifdef HAVE_HARFBUZZ
            || last_script != p_paragraph->p_scripts[ i ]
            || last_level != p_paragraph->p_levels[ i ]
#endif
            || !FaceStyleEquals( p_filter, p_last_style, p_paragraph->pp_styles[ i ] ) )
        {
            int i_ret;
#ifdef HAVE_FONT_FALLBACK
            i_ret = AddRunWithFallback( p_filter, p_paragraph, i_last_run_start, i );
#else
            i_ret = AddRun( p_filter, p_paragraph, i_last_run_start, i, NULL, NULL );
#endif
            if( i_ret )
                return i_ret;

            if( i < p_paragraph->i_size )
            {
                i_last_run_start = i;
                p_last_style = p_paragraph->pp_styles[ i ];
#ifdef HAVE_HARFBUZZ
                last_script = p_paragraph->p_scripts[ i ];
                last_level = p_paragraph->p_levels[ i ];
#endif
            }
        }
    }
    return VLC_SUCCESS;
}