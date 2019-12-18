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
typedef  int /*<<< orphan*/  libvlc_event_t ;

/* Variables and functions */

__attribute__((used)) static void
mlist_item_deleted(const libvlc_event_t * p_event, void * p_user_data)
{
    // Nothing to do. For now.
    (void)p_event; (void)p_user_data;
}