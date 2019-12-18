#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  intf_thread_t ;
struct TYPE_3__ {char* psz_name; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 char* GetDiscDevice (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  intf_Eject (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* vlc_player_GetCurrentMedia (int /*<<< orphan*/ *) ; 
 int vlc_player_IsStarted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Eject(intf_thread_t *intf, vlc_player_t *player)
{
    char *device, *name;

    /* If there's a stream playing, we aren't allowed to eject ! */
    vlc_player_Lock(player);
    bool started = vlc_player_IsStarted(player);
    vlc_player_Unlock(player);
    if (started)
        return;

    vlc_player_Lock(player);
    input_item_t *current = vlc_player_GetCurrentMedia(player);
    vlc_player_Unlock(player);
    if (!current)
        return;
    name = current->psz_name;
    device = name ? GetDiscDevice(name) : NULL;

    if (device) {
        intf_Eject(intf, device);
        free(device);
    }
}