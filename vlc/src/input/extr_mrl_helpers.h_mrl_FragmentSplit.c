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
typedef  int /*<<< orphan*/  vlc_array_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int strcspn (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strndup (char const*,int) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_array_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_array_clear (int /*<<< orphan*/ *) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_array_init (int /*<<< orphan*/ *) ; 
 char* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_uri_decode (char*) ; 

__attribute__((used)) static inline int
mrl_FragmentSplit( vlc_array_t* out_items,
                   char const** out_extra,
                   char const* payload )
{
    char const* extra = NULL;

    vlc_array_init( out_items );

    while( strncmp( payload, "!/", 2 ) == 0 )
    {
        payload += 2;

        int len = strcspn( payload, "!?" );
        char* decoded = strndup( payload, len );

        if( unlikely( !decoded ) || !vlc_uri_decode( decoded ) )
            goto error;

        if( vlc_array_append( out_items, decoded ) )
        {
            free( decoded );
            goto error;
        }
        payload += len;
    }

    if( *payload )
    {
        if( *payload == '!' )
            goto error;

        if( *payload == '?' && vlc_array_count( out_items ) )
            ++payload;

        extra = payload;
    }

    *out_extra = extra;
    return VLC_SUCCESS;

error:
    for( size_t i = 0; i < vlc_array_count( out_items ); ++i )
        free( vlc_array_item_at_index( out_items, i ) );
    vlc_array_clear( out_items );
    return VLC_EGENERIC;;
}