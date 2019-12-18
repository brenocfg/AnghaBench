#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ p_fonts; int /*<<< orphan*/  psz_name; struct TYPE_10__* p_next; } ;
typedef  TYPE_1__ vlc_family_t ;
typedef  int /*<<< orphan*/  uni_char_t ;
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_12__ {TYPE_1__* (* pf_get_family ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ filter_sys_t ;
typedef  int /*<<< orphan*/  FT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Get_Char_Index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFace (TYPE_2__*,scalar_t__) ; 
 TYPE_1__* stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

vlc_family_t *SearchFallbacks( filter_t *p_filter, vlc_family_t *p_fallbacks,
                                      uni_char_t codepoint )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    vlc_family_t *p_family = NULL;

    for( vlc_family_t *p_fallback = p_fallbacks; p_fallback;
         p_fallback = p_fallback->p_next )
    {
        if( !p_fallback->p_fonts )
        {
            const vlc_family_t *p_temp =
                    p_sys->pf_get_family( p_filter, p_fallback->psz_name );
            if( !p_temp || !p_temp->p_fonts )
                continue;
            p_fallback->p_fonts = p_temp->p_fonts;
        }

        FT_Face p_face = GetFace( p_filter, p_fallback->p_fonts );
        if( !p_face || !FT_Get_Char_Index( p_face, codepoint ) )
            continue;
        p_family = p_fallback;
        break;
    }

    return p_family;
}