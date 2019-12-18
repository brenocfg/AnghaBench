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
struct vlc_playlist_sort_criterion {scalar_t__ order; int /*<<< orphan*/  key; } ;
struct vlc_playlist_item_meta {int dummy; } ;
struct sort_request {size_t count; struct vlc_playlist_sort_criterion* criteria; } ;

/* Variables and functions */
 int CompareMetaByKey (struct vlc_playlist_item_meta const*,struct vlc_playlist_item_meta const*,int /*<<< orphan*/ ) ; 
 scalar_t__ VLC_PLAYLIST_SORT_ORDER_DESCENDING ; 

__attribute__((used)) static int
compare_meta(const void *lhs, const void *rhs, void *userdata)
{
    struct sort_request *req = userdata;
    const struct vlc_playlist_item_meta *a =
            *(const struct vlc_playlist_item_meta **) lhs;
    const struct vlc_playlist_item_meta *b =
            *(const struct vlc_playlist_item_meta **) rhs;

    for (size_t i = 0; i < req->count; ++i)
    {
        const struct vlc_playlist_sort_criterion *criterion = &req->criteria[i];
        int ret = CompareMetaByKey(a, b, criterion->key);
        if (ret)
        {
            if (criterion->order == VLC_PLAYLIST_SORT_ORDER_DESCENDING)
                /* do not return -ret, it's undefined if ret == INT_MIN */
                return ret > 0 ? -1 : 1;
            return ret;
        }
    }
    return 0;
}