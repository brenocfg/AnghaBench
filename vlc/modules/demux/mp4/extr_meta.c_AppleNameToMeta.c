#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_meta_type_t ;
struct TYPE_4__ {char* psz_metadata; int /*<<< orphan*/  psz_naming; int /*<<< orphan*/  meta_type; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* com_apple_quicktime_toextrameta ; 
 TYPE_1__* com_apple_quicktime_tometa ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool AppleNameToMeta( char const* name,
    vlc_meta_type_t const** meta_type, char const** meta_key )
{
    *meta_type = NULL;
    *meta_key = NULL;

    for( size_t i = 0; *meta_type == NULL &&
                       i < ARRAY_SIZE( com_apple_quicktime_tometa ); ++i )
    {
        if( !strcmp( name, com_apple_quicktime_tometa[i].psz_naming ) )
            *meta_type = &com_apple_quicktime_tometa[i].meta_type;
    }

    for( size_t i = 0; *meta_key == NULL &&
                       i < ARRAY_SIZE( com_apple_quicktime_toextrameta ); ++i )
    {
        if( !strcmp( name, com_apple_quicktime_toextrameta[i].psz_naming ) )
            *meta_key = com_apple_quicktime_toextrameta[i].psz_metadata;
    }

    return *meta_type || *meta_key;
}