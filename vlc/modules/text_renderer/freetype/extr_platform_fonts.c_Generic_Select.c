#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int i_index; int /*<<< orphan*/  psz_fontfile; } ;
typedef  TYPE_1__ vlc_font_t ;
struct TYPE_23__ {scalar_t__ p_fonts; } ;
typedef  TYPE_2__ vlc_family_t ;
typedef  int /*<<< orphan*/  uni_char_t ;
struct TYPE_24__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_25__ {TYPE_2__* (* pf_get_family ) (TYPE_3__*,char const*) ;int /*<<< orphan*/  fallback_map; TYPE_2__* (* pf_get_fallbacks ) (TYPE_3__*,char const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ filter_sys_t ;
typedef  scalar_t__ FT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FB_LIST_ATTACHMENTS ; 
 int /*<<< orphan*/  FB_LIST_DEFAULT ; 
 scalar_t__ FT_Get_Char_Index (scalar_t__,int /*<<< orphan*/ ) ; 
 char* File_Select (int /*<<< orphan*/ ) ; 
 TYPE_1__* GetBestFont (TYPE_3__*,TYPE_2__ const*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ GetFace (TYPE_3__*,scalar_t__) ; 
 char const* SYSTEM_DEFAULT_FAMILY ; 
 int /*<<< orphan*/  SYSTEM_DEFAULT_FONT_FILE ; 
 TYPE_2__* SearchFallbacks (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 TYPE_2__* stub1 (TYPE_3__*,char const*) ; 
 TYPE_2__* stub2 (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* stub3 (TYPE_3__*,char const*) ; 
 TYPE_2__* stub4 (TYPE_3__*,char const*) ; 
 TYPE_2__* vlc_dictionary_value_for_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char* Generic_Select( filter_t *p_filter, const char* psz_family,
                      bool b_bold, bool b_italic,
                      int *i_idx, uni_char_t codepoint )
{

    filter_sys_t *p_sys = p_filter->p_sys;
    const vlc_family_t *p_family = NULL;
    vlc_family_t *p_fallbacks = NULL;

    if( codepoint )
    {
        /*
         * Try regular face of the same family first.
         * It usually has the best coverage.
         */
        const vlc_family_t *p_temp = p_sys->pf_get_family( p_filter, psz_family );
        if( p_temp && p_temp->p_fonts )
        {
            FT_Face p_face = GetFace( p_filter, p_temp->p_fonts );
            if( p_face && FT_Get_Char_Index( p_face, codepoint ) )
                p_family = p_temp;
        }

        /* Try font attachments */
        if( !p_family )
        {
            p_fallbacks = vlc_dictionary_value_for_key( &p_sys->fallback_map,
                                                        FB_LIST_ATTACHMENTS );
            if( p_fallbacks )
                p_family = SearchFallbacks( p_filter, p_fallbacks, codepoint );
        }

        /* Try system fallbacks */
        if( !p_family )
        {
            p_fallbacks = p_sys->pf_get_fallbacks( p_filter, psz_family, codepoint );
            if( p_fallbacks )
                p_family = SearchFallbacks( p_filter, p_fallbacks, codepoint );
        }

        /* Try the default fallback list, if any */
        if( !p_family )
        {
            p_fallbacks = vlc_dictionary_value_for_key( &p_sys->fallback_map,
                                                        FB_LIST_DEFAULT );
            if( p_fallbacks )
                p_family = SearchFallbacks( p_filter, p_fallbacks, codepoint );
        }

        if( !p_family )
            return NULL;
    }

    if( !p_family )
        p_family = p_sys->pf_get_family( p_filter, psz_family );

    if( !p_family || !p_family->p_fonts )
        p_family = p_sys->pf_get_family( p_filter, SYSTEM_DEFAULT_FAMILY );

    vlc_font_t *p_font;
    if( p_family && ( p_font = GetBestFont( p_filter, p_family, b_bold,
                                            b_italic, codepoint ) ) )
    {
        *i_idx = p_font->i_index;
        return strdup( p_font->psz_fontfile );
    }

    return File_Select( SYSTEM_DEFAULT_FONT_FILE );
}