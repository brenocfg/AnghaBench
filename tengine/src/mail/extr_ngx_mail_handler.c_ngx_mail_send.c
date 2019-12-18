#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {scalar_t__ blocked; scalar_t__ quit; TYPE_1__ out; } ;
typedef  TYPE_2__ ngx_mail_session_t ;
struct TYPE_15__ {int /*<<< orphan*/  timeout; } ;
typedef  TYPE_3__ ngx_mail_core_srv_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_16__ {scalar_t__ timer_set; scalar_t__ timedout; TYPE_5__* data; } ;
typedef  TYPE_4__ ngx_event_t ;
struct TYPE_17__ {int timedout; scalar_t__ (* send ) (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  write; TYPE_6__* read; int /*<<< orphan*/  log; TYPE_2__* data; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* handler ) (TYPE_6__*) ;} ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_4__*) ; 
 scalar_t__ ngx_handle_write_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_mail_core_module ; 
 TYPE_3__* ngx_mail_get_module_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*) ; 

void
ngx_mail_send(ngx_event_t *wev)
{
    ngx_int_t                  n;
    ngx_connection_t          *c;
    ngx_mail_session_t        *s;
    ngx_mail_core_srv_conf_t  *cscf;

    c = wev->data;
    s = c->data;

    if (wev->timedout) {
        ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT, "client timed out");
        c->timedout = 1;
        ngx_mail_close_connection(c);
        return;
    }

    if (s->out.len == 0) {
        if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
            ngx_mail_close_connection(c);
        }

        return;
    }

    n = c->send(c, s->out.data, s->out.len);

    if (n > 0) {
        s->out.data += n;
        s->out.len -= n;

        if (s->out.len != 0) {
            goto again;
        }

        if (wev->timer_set) {
            ngx_del_timer(wev);
        }

        if (s->quit) {
            ngx_mail_close_connection(c);
            return;
        }

        if (s->blocked) {
            c->read->handler(c->read);
        }

        return;
    }

    if (n == NGX_ERROR) {
        ngx_mail_close_connection(c);
        return;
    }

    /* n == NGX_AGAIN */

again:

    cscf = ngx_mail_get_module_srv_conf(s, ngx_mail_core_module);

    ngx_add_timer(c->write, cscf->timeout);

    if (ngx_handle_write_event(c->write, 0) != NGX_OK) {
        ngx_mail_close_connection(c);
        return;
    }
}