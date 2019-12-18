#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uni_char_t ;
typedef  int /*<<< orphan*/  text_style_t ;
typedef  int /*<<< orphan*/  paragraph_t ;
typedef  int /*<<< orphan*/  line_desc_t ;
typedef  int /*<<< orphan*/  filter_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BuildParagraph (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,unsigned int*) ; 
 int /*<<< orphan*/  FreeParagraph (int /*<<< orphan*/ *) ; 
 scalar_t__ LayoutLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** malloc (int) ; 

__attribute__((used)) static int LayoutRubyText( filter_t *p_filter,
                           const uni_char_t *p_uchars,
                           int i_uchars,
                           text_style_t *p_style,
                           line_desc_t **pp_line )
{
    unsigned int i_max_advance_x;

    text_style_t **pp_styles = malloc(sizeof(*pp_styles) * i_uchars);
    for(int i=0;i<i_uchars;i++)
        pp_styles[i] = p_style;

    paragraph_t *p_paragraph = BuildParagraph( p_filter, i_uchars,
                                               p_uchars, pp_styles,
                                               NULL, 1,
                                               &i_max_advance_x );
    if( !p_paragraph )
    {
        free( pp_styles );
        return VLC_EGENERIC;
    }

    if( LayoutLine( p_filter, p_paragraph,
                    0, i_uchars - 1,
                    false, pp_line ) )
    {
        free( pp_styles );
        FreeParagraph( p_paragraph );
        return VLC_EGENERIC;
    }

    FreeParagraph( p_paragraph );
    free( pp_styles );

    return VLC_SUCCESS;
}