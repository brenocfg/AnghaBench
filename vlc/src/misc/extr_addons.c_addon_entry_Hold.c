#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  addon_entry_t ;
struct TYPE_2__ {int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ addon_entry_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_atomic_rc_inc (int /*<<< orphan*/ *) ; 

addon_entry_t * addon_entry_Hold( addon_entry_t * p_entry )
{
    addon_entry_owner_t *owner = (addon_entry_owner_t *) p_entry;

    vlc_atomic_rc_inc( &owner->rc );
    return p_entry;
}