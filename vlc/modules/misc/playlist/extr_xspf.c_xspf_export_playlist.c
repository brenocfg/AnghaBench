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
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_playlist_export {int /*<<< orphan*/  file; int /*<<< orphan*/  playlist_view; } ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * vlc_playlist_item_GetMedia (int /*<<< orphan*/ *) ; 
 size_t vlc_playlist_view_Count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_playlist_view_Get (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  xspf_export_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

int xspf_export_playlist( vlc_object_t *p_this )
{
    struct vlc_playlist_export *p_export = (struct vlc_playlist_export *) p_this;

    /* write XSPF XML header */
    fprintf( p_export->file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" );
    fprintf( p_export->file,
             "<playlist xmlns=\"http://xspf.org/ns/0/\" " \
              "xmlns:vlc=\"http://www.videolan.org/vlc/playlist/ns/0/\" " \
              "version=\"1\">\n" );

    fprintf( p_export->file, "\t<trackList>\n" );
    size_t count = vlc_playlist_view_Count(p_export->playlist_view);
    for( size_t i = 0; i < count; ++i )
    {
        vlc_playlist_item_t *item =
            vlc_playlist_view_Get(p_export->playlist_view, i);
        input_item_t *media = vlc_playlist_item_GetMedia(item);

        xspf_export_item(media, p_export->file, i);
    }

    fprintf( p_export->file, "\t</trackList>\n" );

    /* close the header elements */
    fprintf( p_export->file, "</playlist>\n" );

    return VLC_SUCCESS;
}