#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_9__ {int /*<<< orphan*/  timer_event_source; void* fdname; void* group; void* user; int /*<<< orphan*/  symlinks; void* smack_ip_out; void* smack_ip_in; void* smack; void* bind_to_device; void* tcp_congestion; int /*<<< orphan*/  service; int /*<<< orphan*/  dynamic_creds; int /*<<< orphan*/ * control_command; int /*<<< orphan*/  exec_command; int /*<<< orphan*/  exec_runtime; int /*<<< orphan*/  peers_by_address; } ;
struct TYPE_8__ {int /*<<< orphan*/ * socket; } ;
typedef  TYPE_1__ SocketPeer ;
typedef  TYPE_2__ Socket ;

/* Variables and functions */
 TYPE_2__* SOCKET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _SOCKET_EXEC_COMMAND_MAX ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dynamic_creds_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_command_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_runtime_unref (int /*<<< orphan*/ ,int) ; 
 void* mfree (void*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* set_steal_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_free_ports (TYPE_2__*) ; 
 int /*<<< orphan*/  socket_unwatch_control_pid (TYPE_2__*) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_ref_unset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void socket_done(Unit *u) {
        Socket *s = SOCKET(u);
        SocketPeer *p;

        assert(s);

        socket_free_ports(s);

        while ((p = set_steal_first(s->peers_by_address)))
                p->socket = NULL;

        s->peers_by_address = set_free(s->peers_by_address);

        s->exec_runtime = exec_runtime_unref(s->exec_runtime, false);
        exec_command_free_array(s->exec_command, _SOCKET_EXEC_COMMAND_MAX);
        s->control_command = NULL;

        dynamic_creds_unref(&s->dynamic_creds);

        socket_unwatch_control_pid(s);

        unit_ref_unset(&s->service);

        s->tcp_congestion = mfree(s->tcp_congestion);
        s->bind_to_device = mfree(s->bind_to_device);

        s->smack = mfree(s->smack);
        s->smack_ip_in = mfree(s->smack_ip_in);
        s->smack_ip_out = mfree(s->smack_ip_out);

        strv_free(s->symlinks);

        s->user = mfree(s->user);
        s->group = mfree(s->group);

        s->fdname = mfree(s->fdname);

        s->timer_event_source = sd_event_source_unref(s->timer_event_source);
}