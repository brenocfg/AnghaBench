#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ vlc_player_listener_id ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_assert_locked (int /*<<< orphan*/ *) ; 

void
vlc_player_RemoveListener(vlc_player_t *player,
                          vlc_player_listener_id *id)
{
    assert(id);
    vlc_player_assert_locked(player);

    vlc_list_remove(&id->node);
    free(id);
}