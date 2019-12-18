#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  b_italic; int /*<<< orphan*/  b_bold; struct TYPE_6__* p_next; } ;
typedef  TYPE_1__ vlc_font_t ;
struct TYPE_7__ {TYPE_1__* p_fonts; } ;
typedef  TYPE_2__ vlc_family_t ;
typedef  scalar_t__ uni_char_t ;
typedef  int /*<<< orphan*/  filter_t ;
typedef  scalar_t__ FT_Face ;

/* Variables and functions */
 scalar_t__ FT_Get_Char_Index (scalar_t__,scalar_t__) ; 
 scalar_t__ GetFace (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static vlc_font_t *GetBestFont( filter_t *p_filter, const vlc_family_t *p_family,
                                bool b_bold, bool b_italic, uni_char_t codepoint )
{
    int i_best_score = 0;
    vlc_font_t *p_best_font = p_family->p_fonts;

    for( vlc_font_t *p_font = p_family->p_fonts; p_font; p_font = p_font->p_next )
    {
        int i_score = 0;

        if( codepoint )
        {
            FT_Face p_face = GetFace( p_filter, p_font );
            if( p_face && FT_Get_Char_Index( p_face, codepoint ) )
                i_score += 1000;
        }

        if( !!p_font->b_bold == !!b_bold )
            i_score += 100;
        if( !!p_font->b_italic == !!b_italic )
            i_score += 10;

        if( i_score > i_best_score )
        {
            p_best_font = p_font;
            i_best_score = i_score;
        }
    }

    return p_best_font;
}