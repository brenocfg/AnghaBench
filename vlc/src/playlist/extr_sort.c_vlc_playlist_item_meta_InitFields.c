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
struct vlc_playlist_sort_criterion {int /*<<< orphan*/  key; } ;
struct vlc_playlist_item_meta {int dummy; } ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_playlist_item_meta_DestroyFields (struct vlc_playlist_item_meta*) ; 
 int vlc_playlist_item_meta_InitField (struct vlc_playlist_item_meta*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vlc_playlist_item_meta_InitFields(struct vlc_playlist_item_meta *meta,
        const struct vlc_playlist_sort_criterion criteria[], size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        const struct vlc_playlist_sort_criterion *criterion = &criteria[i];
        int ret = vlc_playlist_item_meta_InitField(meta, criterion->key);
        if (unlikely(ret != VLC_SUCCESS))
        {
            vlc_playlist_item_meta_DestroyFields(meta);
            return ret;
        }
    }
    return VLC_SUCCESS;
}