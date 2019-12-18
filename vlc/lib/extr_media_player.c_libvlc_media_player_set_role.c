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
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/ * roles ; 
 scalar_t__ var_SetString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int libvlc_media_player_set_role(libvlc_media_player_t *mp, unsigned role)
{
    if (role >= ARRAY_SIZE(roles)
     || var_SetString(mp, "role", roles[role]) != VLC_SUCCESS)
        return -1;
    return 0;
}