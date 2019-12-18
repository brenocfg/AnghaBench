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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
struct vlc_playlist_export {int /*<<< orphan*/  file; int /*<<< orphan*/  playlist_view; } ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int SEC_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetArtist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_GetDuration (int /*<<< orphan*/ *) ; 
 char* input_item_GetName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_item_GetMedia (int /*<<< orphan*/ *) ; 
 size_t vlc_playlist_view_Count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_playlist_view_Get (int /*<<< orphan*/ ,size_t) ; 
 char* vlc_xml_encode (char*) ; 

__attribute__((used)) static void DoExport( struct vlc_playlist_export *p_export )
{
    /* Go through the playlist and add items */
    size_t count = vlc_playlist_view_Count(p_export->playlist_view);
    for( size_t i = 0; i < count; ++i )
    {
        vlc_playlist_item_t *item =
            vlc_playlist_view_Get(p_export->playlist_view, i);

        input_item_t *media = vlc_playlist_item_GetMedia(item);

        char* psz_name = NULL;
        char *psz_tmp = input_item_GetName(media);
        if( psz_tmp )
            psz_name = vlc_xml_encode( psz_tmp );
        free( psz_tmp );

        if( psz_name )
        {
            char* psz_artist = NULL;
            psz_tmp = input_item_GetArtist(media);
            if( psz_tmp )
                psz_artist = vlc_xml_encode( psz_tmp );
            free( psz_tmp );

            vlc_tick_t i_duration = input_item_GetDuration(media);
            int min = SEC_FROM_VLC_TICK( i_duration ) / 60;
            int sec = SEC_FROM_VLC_TICK( i_duration ) - min * 60;

            // Print the artist if we have one
            if( psz_artist && *psz_artist )
                fprintf( p_export->file, "    <li>%s - %s (%02d:%02d)</li>\n", psz_artist, psz_name, min, sec );
            else
                fprintf( p_export->file, "    <li>%s (%2d:%2d)</li>\n", psz_name, min, sec);

            free( psz_artist );
        }
        free( psz_name );
    }
}