#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  media; int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ vlc_playlist_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 

void
vlc_playlist_item_Release(vlc_playlist_item_t *item)
{
    if (vlc_atomic_rc_dec(&item->rc))
    {
        input_item_Release(item->media);
        free(item);
    }
}