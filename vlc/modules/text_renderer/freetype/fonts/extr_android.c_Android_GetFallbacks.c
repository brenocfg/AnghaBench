#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_family_t ;
typedef  int /*<<< orphan*/  uni_char_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_5__ {int /*<<< orphan*/  fallback_map; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 char* ToLower (char const*) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * kVLCDictionaryNotFound ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 

vlc_family_t *Android_GetFallbacks( filter_t *p_filter, const char *psz_family,
                                    uni_char_t codepoint )
{
    VLC_UNUSED( codepoint );

    vlc_family_t *p_fallbacks = NULL;
    filter_sys_t *p_sys = p_filter->p_sys;
    char *psz_lc = ToLower( psz_family );
    if( unlikely( !psz_lc ) )
        return NULL;

    p_fallbacks = vlc_dictionary_value_for_key( &p_sys->fallback_map, psz_lc );

    free( psz_lc );

    if( p_fallbacks == kVLCDictionaryNotFound )
        return NULL;

    return p_fallbacks;
}