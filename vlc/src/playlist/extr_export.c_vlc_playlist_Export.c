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
struct vlc_playlist_view {struct vlc_playlist* playlist; } ;
struct vlc_playlist_export {int /*<<< orphan*/  base_url; int /*<<< orphan*/  file; struct vlc_playlist_view* playlist_view; } ;
struct vlc_playlist {int /*<<< orphan*/  player; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * module_need (struct vlc_playlist_export*,char*,char const*,int) ; 
 int /*<<< orphan*/  module_unneed (struct vlc_playlist_export*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Err (struct vlc_playlist_export*,char*,...) ; 
 struct vlc_playlist_export* vlc_custom_create (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  vlc_fopen (char const*,char*) ; 
 int /*<<< orphan*/  vlc_object_delete (struct vlc_playlist_export*) ; 
 int /*<<< orphan*/  vlc_path2uri (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_GetObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (struct vlc_playlist*) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

int
vlc_playlist_Export(struct vlc_playlist *playlist, const char *filename,
                    const char *type)
{
    vlc_playlist_AssertLocked(playlist);

    struct vlc_playlist_export *export =
        vlc_custom_create(vlc_player_GetObject(playlist->player),
                          sizeof(*export), "playlist export");

    if (!export)
        return VLC_ENOMEM;

    int ret = VLC_EGENERIC;

    struct vlc_playlist_view playlist_view = { .playlist = playlist };

    export->playlist_view = &playlist_view;
    export->base_url = vlc_path2uri(filename, NULL);
    export->file = vlc_fopen(filename, "wt");
    if (!export->file)
    {
        msg_Err(export, "Could not create playlist file %s, %s",
                filename, vlc_strerror_c(errno));
        goto close_file;
    }

    // this will actually export
    module_t *module = module_need(export, "playlist export", type, true);

    if (!module)
    {
        msg_Err(export, "Could not export playlist");
        goto out;
    }

    module_unneed(export, module);

    if (!ferror(export->file))
        ret = VLC_SUCCESS;
    else
        msg_Err(export, "Could not write playlist file: %s",
                vlc_strerror_c(errno));

close_file:
    fclose(export->file);
out:
   free(export->base_url);
   vlc_object_delete(export);
   return ret;
}