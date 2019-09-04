#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_4__ {int active; int oneshot; scalar_t__ disabled; } ;
typedef  TYPE_1__ ngx_event_t ;

/* Variables and functions */
 int EV_ADD ; 
 int EV_ENABLE ; 
 int NGX_ONESHOT_EVENT ; 
 int /*<<< orphan*/  ngx_kqueue_set_event (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_kqueue_add_event(ngx_event_t *ev, ngx_int_t event, ngx_uint_t flags)
{
    ngx_int_t          rc;
#if 0
    ngx_event_t       *e;
    ngx_connection_t  *c;
#endif

    ev->active = 1;
    ev->disabled = 0;
    ev->oneshot = (flags & NGX_ONESHOT_EVENT) ? 1 : 0;

#if 0

    if (ev->index < nchanges
        && ((uintptr_t) change_list[ev->index].udata & (uintptr_t) ~1)
            == (uintptr_t) ev)
    {
        if (change_list[ev->index].flags == EV_DISABLE) {

            /*
             * if the EV_DISABLE is still not passed to a kernel
             * we will not pass it
             */

            ngx_log_debug2(NGX_LOG_DEBUG_EVENT, ev->log, 0,
                           "kevent activated: %d: ft:%i",
                           ngx_event_ident(ev->data), event);

            if (ev->index < --nchanges) {
                e = (ngx_event_t *)
                    ((uintptr_t) change_list[nchanges].udata & (uintptr_t) ~1);
                change_list[ev->index] = change_list[nchanges];
                e->index = ev->index;
            }

            return NGX_OK;
        }

        c = ev->data;

        ngx_log_error(NGX_LOG_ALERT, ev->log, 0,
                      "previous event on #%d were not passed in kernel", c->fd);

        return NGX_ERROR;
    }

#endif

    rc = ngx_kqueue_set_event(ev, event, EV_ADD|EV_ENABLE|flags);

    return rc;
}