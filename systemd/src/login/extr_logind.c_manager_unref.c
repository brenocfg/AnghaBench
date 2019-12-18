#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  User ;
struct TYPE_6__ {int /*<<< orphan*/  action_job; int /*<<< orphan*/  wall_message; int /*<<< orphan*/  scheduled_shutdown_tty; int /*<<< orphan*/  scheduled_shutdown_type; int /*<<< orphan*/  kill_exclude_users; int /*<<< orphan*/  kill_only_users; int /*<<< orphan*/  reserve_vt_fd; int /*<<< orphan*/  event; int /*<<< orphan*/  bus; int /*<<< orphan*/  polkit_registry; scalar_t__ unlink_nologin; int /*<<< orphan*/  device_button_monitor; int /*<<< orphan*/  device_vcsa_monitor; int /*<<< orphan*/  device_monitor; int /*<<< orphan*/  device_seat_monitor; int /*<<< orphan*/  console_active_fd; int /*<<< orphan*/  utmp_event_source; int /*<<< orphan*/  lid_switch_ignore_event_source; int /*<<< orphan*/  console_active_event_source; int /*<<< orphan*/  wall_message_timeout_source; int /*<<< orphan*/  nologin_timeout_source; int /*<<< orphan*/  scheduled_shutdown_timeout_source; int /*<<< orphan*/  inhibit_timeout_source; int /*<<< orphan*/  idle_action_event_source; int /*<<< orphan*/  session_units; int /*<<< orphan*/  user_units; int /*<<< orphan*/  brightness_writers; int /*<<< orphan*/  buttons; int /*<<< orphan*/  inhibitors; int /*<<< orphan*/  users; int /*<<< orphan*/  sessions_by_leader; int /*<<< orphan*/  sessions; int /*<<< orphan*/  seats; int /*<<< orphan*/  devices; } ;
typedef  int /*<<< orphan*/  Session ;
typedef  int /*<<< orphan*/  Seat ;
typedef  TYPE_1__ Manager ;
typedef  int /*<<< orphan*/  Inhibitor ;
typedef  int /*<<< orphan*/  Device ;
typedef  int /*<<< orphan*/  Button ;

/* Variables and functions */
 int /*<<< orphan*/  bus_verify_polkit_async_registry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  button_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 void* hashmap_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inhibitor_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_flush_close_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_device_monitor_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seat_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_or_warn (char*) ; 
 int /*<<< orphan*/  user_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Manager* manager_unref(Manager *m) {
        Session *session;
        User *u;
        Device *d;
        Seat *s;
        Inhibitor *i;
        Button *b;

        if (!m)
                return NULL;

        while ((session = hashmap_first(m->sessions)))
                session_free(session);

        while ((u = hashmap_first(m->users)))
                user_free(u);

        while ((d = hashmap_first(m->devices)))
                device_free(d);

        while ((s = hashmap_first(m->seats)))
                seat_free(s);

        while ((i = hashmap_first(m->inhibitors)))
                inhibitor_free(i);

        while ((b = hashmap_first(m->buttons)))
                button_free(b);

        hashmap_free(m->devices);
        hashmap_free(m->seats);
        hashmap_free(m->sessions);
        hashmap_free(m->sessions_by_leader);
        hashmap_free(m->users);
        hashmap_free(m->inhibitors);
        hashmap_free(m->buttons);
        hashmap_free(m->brightness_writers);

        hashmap_free(m->user_units);
        hashmap_free(m->session_units);

        sd_event_source_unref(m->idle_action_event_source);
        sd_event_source_unref(m->inhibit_timeout_source);
        sd_event_source_unref(m->scheduled_shutdown_timeout_source);
        sd_event_source_unref(m->nologin_timeout_source);
        sd_event_source_unref(m->wall_message_timeout_source);

        sd_event_source_unref(m->console_active_event_source);
        sd_event_source_unref(m->lid_switch_ignore_event_source);

#if ENABLE_UTMP
        sd_event_source_unref(m->utmp_event_source);
#endif

        safe_close(m->console_active_fd);

        sd_device_monitor_unref(m->device_seat_monitor);
        sd_device_monitor_unref(m->device_monitor);
        sd_device_monitor_unref(m->device_vcsa_monitor);
        sd_device_monitor_unref(m->device_button_monitor);

        if (m->unlink_nologin)
                (void) unlink_or_warn("/run/nologin");

        bus_verify_polkit_async_registry_free(m->polkit_registry);

        sd_bus_flush_close_unref(m->bus);
        sd_event_unref(m->event);

        safe_close(m->reserve_vt_fd);

        strv_free(m->kill_only_users);
        strv_free(m->kill_exclude_users);

        free(m->scheduled_shutdown_type);
        free(m->scheduled_shutdown_tty);
        free(m->wall_message);
        free(m->action_job);

        return mfree(m);
}