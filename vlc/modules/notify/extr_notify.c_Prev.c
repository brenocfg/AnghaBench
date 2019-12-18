#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_4__ {int /*<<< orphan*/  playlist; } ;
typedef  TYPE_2__ intf_sys_t ;
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  NotifyNotification ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_notification_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_Prev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Prev( NotifyNotification *notification, gchar *psz, gpointer p )
{
    intf_thread_t *p_intf = (intf_thread_t *)p;
    intf_sys_t *p_sys = p_intf->p_sys;

    VLC_UNUSED(psz);
    notify_notification_close( notification, NULL );
    vlc_playlist_Lock(  p_sys->playlist );
    vlc_playlist_Prev( p_sys->playlist );
    vlc_playlist_Unlock(  p_sys->playlist );
}