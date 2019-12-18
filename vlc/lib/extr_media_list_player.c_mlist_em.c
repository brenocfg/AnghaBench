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
struct TYPE_4__ {int /*<<< orphan*/  p_mlist; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;
typedef  int /*<<< orphan*/  libvlc_event_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/ * libvlc_media_list_event_manager (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline libvlc_event_manager_t * mlist_em(libvlc_media_list_player_t * p_mlp)
{
    assert_locked(p_mlp);
    return libvlc_media_list_event_manager(p_mlp->p_mlist);
}