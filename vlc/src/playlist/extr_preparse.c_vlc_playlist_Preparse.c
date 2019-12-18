#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  libvlc; } ;
typedef  TYPE_1__ vlc_playlist_t ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 int META_REQUEST_OPTION_FETCH_LOCAL ; 
 int META_REQUEST_OPTION_SCOPE_LOCAL ; 
 int /*<<< orphan*/  VLC_UNUSED (TYPE_1__*) ; 
 TYPE_1__* input_preparser_callbacks ; 
 int /*<<< orphan*/  vlc_MetadataRequest (int /*<<< orphan*/ ,TYPE_1__*,int,TYPE_1__**,TYPE_1__*,int,int /*<<< orphan*/ *) ; 

void
vlc_playlist_Preparse(vlc_playlist_t *playlist, input_item_t *input)
{
#ifdef TEST_PLAYLIST
    VLC_UNUSED(playlist);
    VLC_UNUSED(input);
    VLC_UNUSED(input_preparser_callbacks);
#else
    /* vlc_MetadataRequest is not exported */
    vlc_MetadataRequest(playlist->libvlc, input,
                        META_REQUEST_OPTION_SCOPE_LOCAL |
                        META_REQUEST_OPTION_FETCH_LOCAL,
                        &input_preparser_callbacks, playlist, -1, NULL);
#endif
}