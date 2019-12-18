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
struct secrets_watch_data {int b_running; int /*<<< orphan*/  sem; } ;
typedef  struct secrets_watch_data* gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GDBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbus_appeared_cb(GDBusConnection *connection, const gchar *name,
                const gchar *name_owner, gpointer user_data)
{
    (void) connection; (void) name; (void)name_owner;
    struct secrets_watch_data *p_watch_data = user_data;
    p_watch_data->b_running = true;
    vlc_sem_post(&p_watch_data->sem);
}