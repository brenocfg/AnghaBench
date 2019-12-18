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
typedef  int /*<<< orphan*/  vlc_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  vlc_player_osd_Message (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

void
vlc_player_osd_Program(vlc_player_t *player, const char *name)
{
    vlc_player_osd_Message(player, _("Program Service ID: %s"), name);
}