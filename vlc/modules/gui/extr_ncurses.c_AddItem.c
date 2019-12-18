#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/ * playlist; } ;
typedef  TYPE_2__ intf_sys_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input_item_New (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char* vlc_path2uri (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_AppendOne (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AddItem(intf_thread_t *intf, const char *path)
{
    char *uri = vlc_path2uri(path, NULL);
    if (uri == NULL)
        return;

    input_item_t *item = input_item_New(uri, NULL);
    free(uri);
    if (unlikely(item == NULL))
        return;

    intf_sys_t *sys = intf->p_sys;
    vlc_playlist_t *playlist = sys->playlist;
    vlc_playlist_Lock(playlist);
    vlc_playlist_AppendOne(playlist, item);
    vlc_playlist_Unlock(playlist);

    input_item_Release(item);
}