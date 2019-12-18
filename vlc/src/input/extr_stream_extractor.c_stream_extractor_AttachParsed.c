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
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ mrl_FragmentSplit (int /*<<< orphan*/ *,char const**,char const*) ; 
 int /*<<< orphan*/  vlc_array_clear (int /*<<< orphan*/ *) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 char* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ vlc_stream_extractor_Attach (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *) ; 

int
stream_extractor_AttachParsed( stream_t** source, char const* data,
                               char const** out_extra )
{
    vlc_array_t identifiers;

    if( mrl_FragmentSplit( &identifiers, out_extra, data ) )
        return VLC_EGENERIC;

    size_t count = vlc_array_count( &identifiers );
    size_t idx = 0;

    while( idx < count )
    {
        char* id = vlc_array_item_at_index( &identifiers, idx );

        if( vlc_stream_extractor_Attach( source, id, NULL ) )
            break;

        ++idx;
    }

    for( size_t i = 0; i < count; ++i )
        free( vlc_array_item_at_index( &identifiers, i ) );
    vlc_array_clear( &identifiers );

    return idx == count ? VLC_SUCCESS : VLC_EGENERIC;
}