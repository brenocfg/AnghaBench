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
struct TYPE_4__ {int /*<<< orphan*/ * media; int /*<<< orphan*/  id; int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ vlc_playlist_item_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_item_Hold (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_atomic_rc_init (int /*<<< orphan*/ *) ; 

vlc_playlist_item_t *
vlc_playlist_item_New(input_item_t *media, uint64_t id)
{
    vlc_playlist_item_t *item = malloc(sizeof(*item));
    if (unlikely(!item))
        return NULL;

    vlc_atomic_rc_init(&item->rc);
    item->id = id;
    item->media = media;
    input_item_Hold(media);
    return item;
}