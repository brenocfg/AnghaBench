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
typedef  scalar_t__ vlc_action_id_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ ACTIONID_COMBO_VOL_FOV_DOWN ; 
 scalar_t__ ACTIONID_COMBO_VOL_FOV_UP ; 
 scalar_t__ ACTIONID_JUMP_BACKWARD_EXTRASHORT ; 
 scalar_t__ ACTIONID_JUMP_FORWARD_EXTRASHORT ; 
 scalar_t__ ACTIONID_NONE ; 
 int /*<<< orphan*/  add_mapping (void**,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void add_wheel_mapping (void **map, uint32_t kmore, uint32_t kless,
                                 int mode)
{
    vlc_action_id_t amore = ACTIONID_NONE, aless = ACTIONID_NONE;

    switch (mode)
    {
        case 0: /* volume up/down */
            amore = ACTIONID_COMBO_VOL_FOV_UP;
            aless = ACTIONID_COMBO_VOL_FOV_DOWN;
            break;
        case 2: /* position latter/earlier */
            amore = ACTIONID_JUMP_FORWARD_EXTRASHORT;
            aless = ACTIONID_JUMP_BACKWARD_EXTRASHORT;
            break;
        case 3: /* position earlier/latter */
            amore = ACTIONID_JUMP_BACKWARD_EXTRASHORT;
            aless = ACTIONID_JUMP_FORWARD_EXTRASHORT;
            break;
    }

    if (amore != ACTIONID_NONE)
        add_mapping (map, kmore, amore);
    if (aless != ACTIONID_NONE)
        add_mapping (map, kless, aless);
}