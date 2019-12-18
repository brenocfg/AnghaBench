#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  p_fonts; } ;
typedef  TYPE_1__ vlc_family_t ;
struct TYPE_14__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_15__ {int /*<<< orphan*/  fallback_map; TYPE_1__* (* pf_get_family ) (TYPE_2__*,char const* const) ;} ;
typedef  TYPE_3__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  FB_LIST_DEFAULT ; 
 int /*<<< orphan*/  FreeFamilies (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* NewFamily (TYPE_2__*,char const* const,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* stub1 (TYPE_2__*,char const* const) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

vlc_family_t *InitDefaultList( filter_t *p_filter, const char *const *ppsz_default,
                               int i_size )
{

    vlc_family_t  *p_default  = NULL;
    filter_sys_t  *p_sys = p_filter->p_sys;

    for( int i = 0; i < i_size; ++i )
    {
        const vlc_family_t *p_family =
                p_sys->pf_get_family( p_filter, ppsz_default[ i ] );

        if( p_family )
        {
            vlc_family_t *p_temp =
                NewFamily( p_filter, ppsz_default[ i ], &p_default, NULL, NULL );

            if( unlikely( !p_temp ) )
                goto error;

            p_temp->p_fonts = p_family->p_fonts;
        }
    }

    if( p_default )
        vlc_dictionary_insert( &p_sys->fallback_map, FB_LIST_DEFAULT, p_default );

    return p_default;

error:
    if( p_default ) FreeFamilies( p_default, NULL );
    return NULL;
}