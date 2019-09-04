#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct rlimit {scalar_t__ rlim_cur; } ;
struct TYPE_29__ {int tv_sec; int tv_usec; } ;
struct TYPE_28__ {int tv_sec; int tv_usec; } ;
struct itimerval {TYPE_6__ it_value; TYPE_5__ it_interval; } ;
typedef  size_t ngx_uint_t ;
typedef  void* ngx_socket_t ;
struct TYPE_30__ {scalar_t__ type; TYPE_2__* previous; TYPE_13__* connection; int /*<<< orphan*/  log; int /*<<< orphan*/  fd; } ;
typedef  TYPE_7__ ngx_listening_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_31__ {int closed; int instance; int accept; int /*<<< orphan*/  handler; int /*<<< orphan*/ * log; } ;
typedef  TYPE_8__ ngx_event_t ;
struct TYPE_27__ {scalar_t__ (* init ) (TYPE_11__*,int) ;} ;
struct TYPE_32__ {TYPE_4__ actions; } ;
typedef  TYPE_9__ ngx_event_module_t ;
struct TYPE_20__ {scalar_t__ use; int /*<<< orphan*/  accept_mutex_delay; scalar_t__ accept_mutex; } ;
typedef  TYPE_10__ ngx_event_conf_t ;
struct TYPE_24__ {size_t nelts; TYPE_7__* elts; } ;
struct TYPE_21__ {size_t files_n; int connection_n; size_t free_connection_n; int /*<<< orphan*/  log; TYPE_1__ listening; TYPE_13__* free_connections; TYPE_8__* write_events; TYPE_8__* read_events; TYPE_13__* connections; int /*<<< orphan*/ * files; TYPE_3__** modules; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_11__ ngx_cycle_t ;
struct TYPE_22__ {int worker_processes; scalar_t__ master; } ;
typedef  TYPE_12__ ngx_core_conf_t ;
struct TYPE_23__ {scalar_t__ type; void* fd; TYPE_8__* read; int /*<<< orphan*/ * log; TYPE_7__* listening; TYPE_8__* write; struct TYPE_23__* data; } ;
typedef  TYPE_13__ ngx_connection_t ;
struct TYPE_26__ {scalar_t__ type; scalar_t__ ctx_index; TYPE_9__* ctx; } ;
struct TYPE_25__ {TYPE_13__* connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  NGX_CLOSE_EVENT ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_EVENT_MODULE ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_READ_EVENT ; 
 int NGX_USE_FD_EVENT ; 
 int NGX_USE_IOCP_EVENT ; 
 int NGX_USE_TIMER_EVENT ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  exit (int) ; 
 int getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  ngx_accept_mutex_delay ; 
 scalar_t__ ngx_accept_mutex_held ; 
 scalar_t__ ngx_add_event (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ngx_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_core_module ; 
 scalar_t__ ngx_del_event (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_event_accept ; 
 int /*<<< orphan*/  ngx_event_core_module ; 
 int ngx_event_flags ; 
 TYPE_10__* ngx_event_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_event_recvmsg ; 
 scalar_t__ ngx_event_timer_init (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_13__* ngx_get_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memzero (struct sigaction*,int) ; 
 int /*<<< orphan*/  ngx_posted_accept_events ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 
 int ngx_timer_resolution ; 
 int /*<<< orphan*/  ngx_timer_signal_handler ; 
 int ngx_use_accept_mutex ; 
 int setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_11__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_event_process_init(ngx_cycle_t *cycle)
{
    ngx_uint_t           m, i;
    ngx_event_t         *rev, *wev;
#if (NGX_SSL && NGX_SSL_ASYNC)
    ngx_event_t         *aev;
#endif
    ngx_listening_t     *ls;
    ngx_connection_t    *c, *next, *old;
    ngx_core_conf_t     *ccf;
    ngx_event_conf_t    *ecf;
    ngx_event_module_t  *module;

    ccf = (ngx_core_conf_t *) ngx_get_conf(cycle->conf_ctx, ngx_core_module);
    ecf = ngx_event_get_conf(cycle->conf_ctx, ngx_event_core_module);

    if (ccf->master && ccf->worker_processes > 1 && ecf->accept_mutex) {
        ngx_use_accept_mutex = 1;
        ngx_accept_mutex_held = 0;
        ngx_accept_mutex_delay = ecf->accept_mutex_delay;

    } else {
        ngx_use_accept_mutex = 0;
    }

#if (NGX_WIN32)

    /*
     * disable accept mutex on win32 as it may cause deadlock if
     * grabbed by a process which can't accept connections
     */

    ngx_use_accept_mutex = 0;

#endif

    ngx_queue_init(&ngx_posted_accept_events);
    ngx_queue_init(&ngx_posted_events);

    if (ngx_event_timer_init(cycle->log) == NGX_ERROR) {
        return NGX_ERROR;
    }

    for (m = 0; cycle->modules[m]; m++) {
        if (cycle->modules[m]->type != NGX_EVENT_MODULE) {
            continue;
        }

        if (cycle->modules[m]->ctx_index != ecf->use) {
            continue;
        }

        module = cycle->modules[m]->ctx;

        if (module->actions.init(cycle, ngx_timer_resolution) != NGX_OK) {
            /* fatal */
            exit(2);
        }

        break;
    }

#if !(NGX_WIN32)

    if (ngx_timer_resolution && !(ngx_event_flags & NGX_USE_TIMER_EVENT)) {
        struct sigaction  sa;
        struct itimerval  itv;

        ngx_memzero(&sa, sizeof(struct sigaction));
        sa.sa_handler = ngx_timer_signal_handler;
        sigemptyset(&sa.sa_mask);

        if (sigaction(SIGALRM, &sa, NULL) == -1) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "sigaction(SIGALRM) failed");
            return NGX_ERROR;
        }

        itv.it_interval.tv_sec = ngx_timer_resolution / 1000;
        itv.it_interval.tv_usec = (ngx_timer_resolution % 1000) * 1000;
        itv.it_value.tv_sec = ngx_timer_resolution / 1000;
        itv.it_value.tv_usec = (ngx_timer_resolution % 1000 ) * 1000;

        if (setitimer(ITIMER_REAL, &itv, NULL) == -1) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "setitimer() failed");
        }
    }

    if (ngx_event_flags & NGX_USE_FD_EVENT) {
        struct rlimit  rlmt;

        if (getrlimit(RLIMIT_NOFILE, &rlmt) == -1) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "getrlimit(RLIMIT_NOFILE) failed");
            return NGX_ERROR;
        }

        cycle->files_n = (ngx_uint_t) rlmt.rlim_cur;

        cycle->files = ngx_calloc(sizeof(ngx_connection_t *) * cycle->files_n,
                                  cycle->log);
        if (cycle->files == NULL) {
            return NGX_ERROR;
        }
    }

#else

    if (ngx_timer_resolution && !(ngx_event_flags & NGX_USE_TIMER_EVENT)) {
        ngx_log_error(NGX_LOG_WARN, cycle->log, 0,
                      "the \"timer_resolution\" directive is not supported "
                      "with the configured event method, ignored");
        ngx_timer_resolution = 0;
    }

#endif

    cycle->connections =
        ngx_alloc(sizeof(ngx_connection_t) * cycle->connection_n, cycle->log);
    if (cycle->connections == NULL) {
        return NGX_ERROR;
    }

    c = cycle->connections;

    cycle->read_events = ngx_alloc(sizeof(ngx_event_t) * cycle->connection_n,
                                   cycle->log);
    if (cycle->read_events == NULL) {
        return NGX_ERROR;
    }

    rev = cycle->read_events;
    for (i = 0; i < cycle->connection_n; i++) {
        rev[i].closed = 1;
        rev[i].instance = 1;
    }

    cycle->write_events = ngx_alloc(sizeof(ngx_event_t) * cycle->connection_n,
                                    cycle->log);
    if (cycle->write_events == NULL) {
        return NGX_ERROR;
    }

    wev = cycle->write_events;
    for (i = 0; i < cycle->connection_n; i++) {
        wev[i].closed = 1;
    }

#if (NGX_SSL && NGX_SSL_ASYNC)
    cycle->async_events = ngx_alloc(sizeof(ngx_event_t) * cycle->connection_n,
                                    cycle->log);
    if (cycle->async_events == NULL) {
        return NGX_ERROR;
    }

    aev = cycle->async_events;
    for (i = 0; i < cycle->connection_n; i++) {
        aev[i].closed = 1;
        aev[i].instance = 1;
    }
#endif

    i = cycle->connection_n;
    next = NULL;

    do {
        i--;

        c[i].data = next;
        c[i].read = &cycle->read_events[i];
        c[i].write = &cycle->write_events[i];
        c[i].fd = (ngx_socket_t) -1;
#if (NGX_SSL && NGX_SSL_ASYNC)
        c[i].async = &cycle->async_events[i];
        c[i].async_fd = (ngx_socket_t) -1;
#endif

        next = &c[i];
    } while (i);

    cycle->free_connections = next;
    cycle->free_connection_n = cycle->connection_n;

    /* for each listening socket */

    ls = cycle->listening.elts;
    for (i = 0; i < cycle->listening.nelts; i++) {

#if (NGX_HAVE_REUSEPORT)
        if (ls[i].reuseport && ls[i].worker != ngx_worker) {
            continue;
        }
#endif

        c = ngx_get_connection(ls[i].fd, cycle->log);

        if (c == NULL) {
            return NGX_ERROR;
        }

        c->type = ls[i].type;
        c->log = &ls[i].log;

        c->listening = &ls[i];
        ls[i].connection = c;

        rev = c->read;

        rev->log = c->log;
        rev->accept = 1;

#if (NGX_HAVE_DEFERRED_ACCEPT)
        rev->deferred_accept = ls[i].deferred_accept;
#endif

        if (!(ngx_event_flags & NGX_USE_IOCP_EVENT)) {
            if (ls[i].previous) {

                /*
                 * delete the old accept events that were bound to
                 * the old cycle read events array
                 */

                old = ls[i].previous->connection;

                if (ngx_del_event(old->read, NGX_READ_EVENT, NGX_CLOSE_EVENT)
                    == NGX_ERROR)
                {
                    return NGX_ERROR;
                }

                old->fd = (ngx_socket_t) -1;
            }
        }

#if (NGX_WIN32)

        if (ngx_event_flags & NGX_USE_IOCP_EVENT) {
            ngx_iocp_conf_t  *iocpcf;

            rev->handler = ngx_event_acceptex;

            if (ngx_use_accept_mutex) {
                continue;
            }

            if (ngx_add_event(rev, 0, NGX_IOCP_ACCEPT) == NGX_ERROR) {
                return NGX_ERROR;
            }

            ls[i].log.handler = ngx_acceptex_log_error;

            iocpcf = ngx_event_get_conf(cycle->conf_ctx, ngx_iocp_module);
            if (ngx_event_post_acceptex(&ls[i], iocpcf->post_acceptex)
                == NGX_ERROR)
            {
                return NGX_ERROR;
            }

        } else {
            rev->handler = ngx_event_accept;

            if (ngx_use_accept_mutex) {
                continue;
            }

            if (ngx_add_event(rev, NGX_READ_EVENT, 0) == NGX_ERROR) {
                return NGX_ERROR;
            }
        }

#else

        rev->handler = (c->type == SOCK_STREAM) ? ngx_event_accept
                                                : ngx_event_recvmsg;

#if (NGX_HAVE_REUSEPORT)

        if (ls[i].reuseport) {
            if (ngx_add_event(rev, NGX_READ_EVENT, 0) == NGX_ERROR) {
                return NGX_ERROR;
            }

            continue;
        }

#endif

        if (ngx_use_accept_mutex) {
            continue;
        }

#if (NGX_HAVE_EPOLLEXCLUSIVE)

        if ((ngx_event_flags & NGX_USE_EPOLL_EVENT)
            && ccf->worker_processes > 1)
        {
            if (ngx_add_event(rev, NGX_READ_EVENT, NGX_EXCLUSIVE_EVENT)
                == NGX_ERROR)
            {
                return NGX_ERROR;
            }

            continue;
        }

#endif

        if (ngx_add_event(rev, NGX_READ_EVENT, 0) == NGX_ERROR) {
            return NGX_ERROR;
        }

#endif

    }

    return NGX_OK;
}