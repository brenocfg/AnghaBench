#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_3__ {TYPE_2__* p_md; } ;
typedef  TYPE_1__ libvlc_media_player_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;
struct TYPE_4__ {int /*<<< orphan*/ * p_input_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_add_subtree (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
on_media_subitems_changed(vlc_player_t *player, input_item_t *media,
                          input_item_node_t *new_subitems, void *data)
{
    (void) player;

    libvlc_media_player_t *mp = data;

    input_item_t *current = mp->p_md ? mp->p_md->p_input_item : NULL;
    if (media == current)
        libvlc_media_add_subtree(mp->p_md, new_subitems);
}