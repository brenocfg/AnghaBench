#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const vlc_family_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_6__ {int /*<<< orphan*/  family_map; int /*<<< orphan*/  p_families; } ;
typedef  TYPE_2__ filter_sys_t ;
typedef  scalar_t__ FcResult ;
typedef  int /*<<< orphan*/  FcPattern ;
typedef  int /*<<< orphan*/  FcChar8 ;
typedef  scalar_t__ FcBool ;

/* Variables and functions */
 int /*<<< orphan*/  FC_FAMILY ; 
 int /*<<< orphan*/  FC_FILE ; 
 int /*<<< orphan*/  FC_INDEX ; 
 int /*<<< orphan*/  FC_OUTLINE ; 
 int /*<<< orphan*/  FC_SLANT ; 
 int /*<<< orphan*/  FC_SLANT_ITALIC ; 
 int /*<<< orphan*/  FC_SLANT_ROMAN ; 
 int /*<<< orphan*/  FC_WEIGHT ; 
 int /*<<< orphan*/  FC_WEIGHT_EXTRABOLD ; 
 int /*<<< orphan*/  FC_WEIGHT_NORMAL ; 
 int /*<<< orphan*/  FcConfigSubstitute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FcDefaultSubstitute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FcFontMatch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  FcMatchPattern ; 
 int /*<<< orphan*/  FcPatternAddBool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FcPatternAddInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FcPatternAddString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * FcPatternCreate () ; 
 int /*<<< orphan*/  FcPatternDestroy (int /*<<< orphan*/ *) ; 
 scalar_t__ FcPatternGetBool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ FcPatternGetInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ FcPatternGetString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FcResultMatch ; 
 scalar_t__ FcResultNoMatch ; 
 scalar_t__ FcTrue ; 
 int /*<<< orphan*/  const* NewFamily (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  NewFont (char*,int,int const,int const,int /*<<< orphan*/  const*) ; 
 char* ToLower (char const*) ; 
 int /*<<< orphan*/  config ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  const* kVLCDictionaryNotFound ; 
 char* strdup (char const*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  const* vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 

const vlc_family_t *FontConfig_GetFamily( filter_t *p_filter, const char *psz_family )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    char *psz_lc = ToLower( psz_family );

    if( unlikely( !psz_lc ) )
        return NULL;

    vlc_family_t *p_family =
            vlc_dictionary_value_for_key( &p_sys->family_map, psz_lc );

    if( p_family != kVLCDictionaryNotFound )
    {
        free( psz_lc );
        return p_family;
    }

    p_family = NewFamily( p_filter, psz_lc, &p_sys->p_families,
                          &p_sys->family_map, psz_lc );

    free( psz_lc );
    if( !p_family )
        return NULL;

    for( int i = 0; i < 4; ++i ) /* Iterate through FC_{SLANT,WEIGHT} combos */
    {
        bool const b_bold = i & 1;
        bool const b_italic = i & 2;

        int i_index = 0;
        FcResult result = FcResultMatch;
        FcPattern *pat, *p_pat;
        FcChar8* val_s;
        FcBool val_b;
        char *psz_fontfile = NULL;

        /* Create a pattern and fill it */
        pat = FcPatternCreate();
        if (!pat) continue;

        /* */
        FcPatternAddString( pat, FC_FAMILY, (const FcChar8*) psz_family );
        FcPatternAddBool( pat, FC_OUTLINE, FcTrue );
        FcPatternAddInteger( pat, FC_SLANT, b_italic ? FC_SLANT_ITALIC : FC_SLANT_ROMAN );
        FcPatternAddInteger( pat, FC_WEIGHT, b_bold ? FC_WEIGHT_EXTRABOLD : FC_WEIGHT_NORMAL );

        /* */
        FcDefaultSubstitute( pat );
        if( !FcConfigSubstitute( config, pat, FcMatchPattern ) )
        {
            FcPatternDestroy( pat );
            continue;
        }

        /* Find the best font for the pattern, destroy the pattern */
        p_pat = FcFontMatch( config, pat, &result );
        FcPatternDestroy( pat );
        if( !p_pat || result == FcResultNoMatch ) continue;

        /* Check the new pattern */
        if( ( FcResultMatch != FcPatternGetBool( p_pat, FC_OUTLINE, 0, &val_b ) )
            || ( val_b != FcTrue ) )
        {
            FcPatternDestroy( p_pat );
            continue;
        }
        if( FcResultMatch != FcPatternGetInteger( p_pat, FC_INDEX, 0, &i_index ) )
        {
            i_index = 0;
        }

        if( FcResultMatch != FcPatternGetString( p_pat, FC_FAMILY, 0, &val_s ) )
        {
            FcPatternDestroy( p_pat );
            continue;
        }

        if( FcResultMatch == FcPatternGetString( p_pat, FC_FILE, 0, &val_s ) )
            psz_fontfile = strdup( (const char*)val_s );

        FcPatternDestroy( p_pat );

        if( !psz_fontfile )
            continue;

        NewFont( psz_fontfile, i_index, b_bold, b_italic, p_family );
    }

    return p_family;
}