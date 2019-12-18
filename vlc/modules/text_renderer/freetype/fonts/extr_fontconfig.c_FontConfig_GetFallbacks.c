#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {char* psz_name; } ;
typedef  TYPE_2__ vlc_family_t ;
typedef  int /*<<< orphan*/  uni_char_t ;
struct TYPE_21__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_22__ {int /*<<< orphan*/  fallback_map; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_24__ {int nfont; int /*<<< orphan*/ * fonts; } ;
struct TYPE_19__ {int /*<<< orphan*/  const* s; } ;
struct TYPE_23__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ FcValue ;
typedef  int /*<<< orphan*/  FcResult ;
typedef  int /*<<< orphan*/  FcPattern ;
typedef  TYPE_6__ FcFontSet ;
typedef  int /*<<< orphan*/  FcChar8 ;

/* Variables and functions */
 int /*<<< orphan*/  FC_FAMILY ; 
 scalar_t__ FcConfigSubstitute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FcDefaultSubstitute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FcFalse ; 
 int /*<<< orphan*/  FcFontSetDestroy (TYPE_6__*) ; 
 TYPE_6__* FcFontSort (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FcMatchPattern ; 
 int /*<<< orphan*/  FcPatternAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * FcPatternCreate () ; 
 int /*<<< orphan*/  FcPatternDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FcPatternGetString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FcTrue ; 
 int /*<<< orphan*/  FcTypeString ; 
 int /*<<< orphan*/  FreeFamilies (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* NewFamily (TYPE_3__*,char*,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* ToLower (char const*) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* kVLCDictionaryNotFound ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 TYPE_2__* vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 

vlc_family_t *FontConfig_GetFallbacks( filter_t *p_filter, const char *psz_family,
                                       uni_char_t codepoint )
{

    VLC_UNUSED( codepoint );

    vlc_family_t *p_family = NULL;
    filter_sys_t *p_sys    = p_filter->p_sys;

    char *psz_lc = ToLower( psz_family );

    if( unlikely( !psz_lc ) )
        return NULL;

    p_family = vlc_dictionary_value_for_key( &p_sys->fallback_map, psz_lc );

    if( p_family != kVLCDictionaryNotFound )
    {
        free( psz_lc );
        return p_family;
    }
    else
        p_family = NULL;

    const char *psz_last_name = "";
    FcPattern  *p_pattern = FcPatternCreate();
    FcValue     family;
    family.type = FcTypeString;
    family.u.s = ( const FcChar8* ) psz_family;
    FcPatternAdd( p_pattern, FC_FAMILY, family, FcFalse );
    if( FcConfigSubstitute( config, p_pattern, FcMatchPattern ) == FcTrue )
    {
        FcDefaultSubstitute( p_pattern );
        FcResult result;
        FcFontSet* p_font_set = FcFontSort( config, p_pattern, FcTrue, NULL, &result );
        if( p_font_set )
        {
            for( int i = 0; i < p_font_set->nfont; ++i )
            {
                char* psz_name = NULL;
                FcPatternGetString( p_font_set->fonts[i],
                                    FC_FAMILY, 0, ( FcChar8** )( &psz_name ) );

                /* Avoid duplicate family names */
                if( strcasecmp( psz_last_name, psz_name ) )
                {
                    vlc_family_t *p_temp = NewFamily( p_filter, psz_name,
                                                      &p_family, NULL, NULL );

                    if( unlikely( !p_temp ) )
                    {
                        FcFontSetDestroy( p_font_set );
                        FcPatternDestroy( p_pattern );
                        if( p_family )
                            FreeFamilies( p_family, NULL );
                        free( psz_lc );
                        return NULL;
                    }

                    psz_last_name = p_temp->psz_name;
                }
            }
            FcFontSetDestroy( p_font_set );
        }
    }
    FcPatternDestroy( p_pattern );

    if( p_family )
        vlc_dictionary_insert( &p_sys->fallback_map, psz_lc, p_family );

    free( psz_lc );
    return p_family;
}