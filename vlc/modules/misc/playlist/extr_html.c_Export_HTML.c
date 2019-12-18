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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_playlist_export {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  DoExport (struct vlc_playlist_export*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_Dbg (struct vlc_playlist_export*,char*) ; 

int Export_HTML( vlc_object_t *p_this )
{
    struct vlc_playlist_export *p_export = (struct vlc_playlist_export *) p_this;

    msg_Dbg( p_export, "saving using HTML format" );

    /* Write header */
    fprintf( p_export->file, "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n"
"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
"<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\">\n"
"<head>\n"
"  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
"  <meta name=\"Generator\" content=\"VLC media player\" />\n"
"  <meta name=\"Author\" content=\"VLC, http://www.videolan.org/vlc/\" />\n"
"  <title>VLC generated playlist</title>\n"
"  <style type=\"text/css\">\n"
"    body {\n"
"      background-color: #E4F3FF;\n"
"      font-family: sans-serif, Helvetica, Arial;\n"
"      font-size: 13px;\n"
"    }\n"
"    h1 {\n"
"      color: #2D58AE;\n"
"      font-size: 25px;\n"
"    }\n"
"    hr {\n"
"      color: #555555;\n"
"    }\n"
"  </style>\n"
"</head>\n\n"
"<body>\n"
"  <h1>Playlist</h1>\n"
"  <hr />\n"
"  <ol>\n" );

    // Call the playlist constructor
    DoExport(p_export);

    // Print the footer
    fprintf( p_export->file, "  </ol>\n"
"  <hr />\n"
"</body>\n"
"</html>" );
    return VLC_SUCCESS;
}