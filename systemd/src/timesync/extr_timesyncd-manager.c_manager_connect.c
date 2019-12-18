#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {int ai_flags; int /*<<< orphan*/  ai_socktype; } ;
struct TYPE_14__ {scalar_t__ type; int /*<<< orphan*/  string; int /*<<< orphan*/ * names_next; } ;
struct TYPE_13__ {int exhausted_servers; scalar_t__ poll_interval_usec; scalar_t__ poll_interval_max_usec; TYPE_3__* current_server_name; int /*<<< orphan*/  resolve_query; int /*<<< orphan*/  resolve; int /*<<< orphan*/  event_retry; int /*<<< orphan*/  event; int /*<<< orphan*/ * fallback_servers; int /*<<< orphan*/ * system_servers; int /*<<< orphan*/ * link_servers; TYPE_1__* current_server_address; int /*<<< orphan*/  ratelimit; } ;
struct TYPE_12__ {scalar_t__ addresses_next; } ;
typedef  int /*<<< orphan*/  ServerName ;
typedef  TYPE_2__ Manager ;

/* Variables and functions */
 int AI_ADDRCONFIG ; 
 int AI_NUMERICSERV ; 
 scalar_t__ RETRY_USEC ; 
 scalar_t__ SERVER_LINK ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  clock_boottime_or_monotonic () ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 int log_error_errno (int,char*) ; 
 int manager_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  manager_disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  manager_resolve_handler ; 
 int /*<<< orphan*/  manager_retry_connect ; 
 int /*<<< orphan*/  manager_set_server_address (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  manager_set_server_name (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ratelimit_below (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  res_init () ; 
 int resolve_getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct addrinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int sd_event_add_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_name_flush_addresses (TYPE_3__*) ; 

int manager_connect(Manager *m) {
        int r;

        assert(m);

        manager_disconnect(m);

        m->event_retry = sd_event_source_unref(m->event_retry);
        if (!ratelimit_below(&m->ratelimit)) {
                log_debug("Delaying attempts to contact servers.");

                r = sd_event_add_time(m->event, &m->event_retry, clock_boottime_or_monotonic(), now(clock_boottime_or_monotonic()) + RETRY_USEC, 0, manager_retry_connect, m);
                if (r < 0)
                        return log_error_errno(r, "Failed to create retry timer: %m");

                return 0;
        }

        /* If we already are operating on some address, switch to the
         * next one. */
        if (m->current_server_address && m->current_server_address->addresses_next)
                manager_set_server_address(m, m->current_server_address->addresses_next);
        else {
                struct addrinfo hints = {
                        .ai_flags = AI_NUMERICSERV|AI_ADDRCONFIG,
                        .ai_socktype = SOCK_DGRAM,
                };

                /* Hmm, we are through all addresses, let's look for the next host instead */
                if (m->current_server_name && m->current_server_name->names_next)
                        manager_set_server_name(m, m->current_server_name->names_next);
                else {
                        ServerName *f;
                        bool restart = true;

                        /* Our current server name list is exhausted,
                         * let's find the next one to iterate. First
                         * we try the system list, then the link list.
                         * After having processed the link list we
                         * jump back to the system list. However, if
                         * both lists are empty, we change to the
                         * fallback list. */
                        if (!m->current_server_name || m->current_server_name->type == SERVER_LINK) {
                                f = m->system_servers;
                                if (!f)
                                        f = m->link_servers;
                        } else {
                                f = m->link_servers;
                                if (!f)
                                        f = m->system_servers;
                                else
                                        restart = false;
                        }

                        if (!f)
                                f = m->fallback_servers;

                        if (!f) {
                                manager_set_server_name(m, NULL);
                                log_debug("No server found.");
                                return 0;
                        }

                        if (restart && !m->exhausted_servers && m->poll_interval_usec) {
                                log_debug("Waiting after exhausting servers.");
                                r = sd_event_add_time(m->event, &m->event_retry, clock_boottime_or_monotonic(), now(clock_boottime_or_monotonic()) + m->poll_interval_usec, 0, manager_retry_connect, m);
                                if (r < 0)
                                        return log_error_errno(r, "Failed to create retry timer: %m");

                                m->exhausted_servers = true;

                                /* Increase the polling interval */
                                if (m->poll_interval_usec < m->poll_interval_max_usec)
                                        m->poll_interval_usec *= 2;

                                return 0;
                        }

                        m->exhausted_servers = false;

                        manager_set_server_name(m, f);
                }

                /* Tell the resolver to reread /etc/resolv.conf, in
                 * case it changed. */
                res_init();

                /* Flush out any previously resolved addresses */
                server_name_flush_addresses(m->current_server_name);

                log_debug("Resolving %s...", m->current_server_name->string);

                r = resolve_getaddrinfo(m->resolve, &m->resolve_query, m->current_server_name->string, "123", &hints, manager_resolve_handler, NULL, m);
                if (r < 0)
                        return log_error_errno(r, "Failed to create resolver: %m");

                return 1;
        }

        r = manager_begin(m);
        if (r < 0)
                return r;

        return 1;
}