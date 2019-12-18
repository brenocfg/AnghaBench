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
struct vlc_playlist_item_meta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_playlist_item_meta**) ; 
 int /*<<< orphan*/  vlc_playlist_item_meta_Delete (struct vlc_playlist_item_meta*) ; 

__attribute__((used)) static void
vlc_playlist_DeleteMetaArray(struct vlc_playlist_item_meta *array[],
                             size_t count)
{
    for (size_t i = 0; i < count; ++i)
        vlc_playlist_item_meta_Delete(array[i]);
    free(array);
}