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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int /*<<< orphan*/  intf_thread_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetURI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* var_CreateGetString (int /*<<< orphan*/ *,char*) ; 
 size_t vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_Get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_PlayAt (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * vlc_playlist_item_GetMedia (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
playlist_bookmark_Play(intf_thread_t *intf,
                       vlc_playlist_t *playlist, char *name)
{
    char *bookmark_uri = var_CreateGetString(intf, name);
    size_t count = vlc_playlist_Count(playlist);
    size_t i;
    for (i = 0; i < count; ++i)
    {
        vlc_playlist_item_t *plitem = vlc_playlist_Get(playlist, i);
        input_item_t *item = vlc_playlist_item_GetMedia(plitem);
        char *item_uri = input_item_GetURI(item);
        if (!strcmp(bookmark_uri, item_uri))
            break;
        free(item_uri);
    }
    if (i != count)
        vlc_playlist_PlayAt(playlist, i);
    free(bookmark_uri);
}