#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  listeners; } ;
typedef  TYPE_1__ vlc_player_t ;
struct TYPE_8__ {int /*<<< orphan*/  node; void* cbs_data; struct vlc_player_cbs const* cbs; } ;
typedef  TYPE_2__ vlc_player_listener_id ;
struct vlc_player_cbs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct vlc_player_cbs const*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_assert_locked (TYPE_1__*) ; 

vlc_player_listener_id *
vlc_player_AddListener(vlc_player_t *player,
                       const struct vlc_player_cbs *cbs, void *cbs_data)
{
    assert(cbs);
    vlc_player_assert_locked(player);

    vlc_player_listener_id *listener = malloc(sizeof(*listener));
    if (!listener)
        return NULL;

    listener->cbs = cbs;
    listener->cbs_data = cbs_data;

    vlc_list_append(&listener->node, &player->listeners);

    return listener;
}