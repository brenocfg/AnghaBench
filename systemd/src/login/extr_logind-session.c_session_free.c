#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  sessions; TYPE_2__* pending_switch; TYPE_2__* active; } ;
struct TYPE_15__ {TYPE_2__* display; int /*<<< orphan*/  sessions; } ;
struct TYPE_14__ {scalar_t__ fifo_path; scalar_t__ state_file; int /*<<< orphan*/  fifo_fd; int /*<<< orphan*/  fifo_event_source; scalar_t__ id; TYPE_1__* manager; scalar_t__ desktop; scalar_t__ service; scalar_t__ remote_user; scalar_t__ remote_host; scalar_t__ display; scalar_t__ tty; int /*<<< orphan*/  create_message; scalar_t__ scope_job; int /*<<< orphan*/  leader; scalar_t__ scope; TYPE_7__* seat; TYPE_3__* user; int /*<<< orphan*/  devices; int /*<<< orphan*/  timer_event_source; scalar_t__ in_gc_queue; } ;
struct TYPE_13__ {int /*<<< orphan*/  sessions; int /*<<< orphan*/  sessions_by_leader; int /*<<< orphan*/  session_units; int /*<<< orphan*/  session_gc_queue; } ;
typedef  int /*<<< orphan*/  SessionDevice ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  PID_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  gc_queue ; 
 int /*<<< orphan*/ * hashmap_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hashmap_remove_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 scalar_t__ pid_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seat_evict_position (TYPE_7__*,TYPE_2__*) ; 
 int /*<<< orphan*/  session_device_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_drop_controller (TYPE_2__*) ; 
 int /*<<< orphan*/  sessions_by_seat ; 
 int /*<<< orphan*/  sessions_by_user ; 
 int /*<<< orphan*/  user_update_last_session_timer (TYPE_3__*) ; 

Session* session_free(Session *s) {
        SessionDevice *sd;

        if (!s)
                return NULL;

        if (s->in_gc_queue)
                LIST_REMOVE(gc_queue, s->manager->session_gc_queue, s);

        s->timer_event_source = sd_event_source_unref(s->timer_event_source);

        session_drop_controller(s);

        while ((sd = hashmap_first(s->devices)))
                session_device_free(sd);

        hashmap_free(s->devices);

        if (s->user) {
                LIST_REMOVE(sessions_by_user, s->user->sessions, s);

                if (s->user->display == s)
                        s->user->display = NULL;

                user_update_last_session_timer(s->user);
        }

        if (s->seat) {
                if (s->seat->active == s)
                        s->seat->active = NULL;
                if (s->seat->pending_switch == s)
                        s->seat->pending_switch = NULL;

                seat_evict_position(s->seat, s);
                LIST_REMOVE(sessions_by_seat, s->seat->sessions, s);
        }

        if (s->scope) {
                hashmap_remove(s->manager->session_units, s->scope);
                free(s->scope);
        }

        if (pid_is_valid(s->leader))
                (void) hashmap_remove_value(s->manager->sessions_by_leader, PID_TO_PTR(s->leader), s);

        free(s->scope_job);

        sd_bus_message_unref(s->create_message);

        free(s->tty);
        free(s->display);
        free(s->remote_host);
        free(s->remote_user);
        free(s->service);
        free(s->desktop);

        hashmap_remove(s->manager->sessions, s->id);

        sd_event_source_unref(s->fifo_event_source);
        safe_close(s->fifo_fd);

        /* Note that we remove neither the state file nor the fifo path here, since we want both to survive
         * daemon restarts */
        free(s->state_file);
        free(s->fifo_path);

        return mfree(s);
}