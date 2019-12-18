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
struct TYPE_4__ {int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ vlc_renderer_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_free (TYPE_1__*) ; 
 scalar_t__ vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 

void
vlc_renderer_item_release(vlc_renderer_item_t *p_item)
{
    assert(p_item != NULL);

    if (vlc_atomic_rc_dec(&p_item->rc))
        item_free(p_item);
}