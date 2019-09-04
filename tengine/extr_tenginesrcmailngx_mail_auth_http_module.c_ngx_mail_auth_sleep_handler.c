#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  auth_method; scalar_t__ mail_state; scalar_t__ auth_wait; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
struct TYPE_18__ {int /*<<< orphan*/  timeout; TYPE_1__* protocol; } ;
typedef  TYPE_4__ ngx_mail_core_srv_conf_t ;
struct TYPE_19__ {scalar_t__ active; int /*<<< orphan*/  (* handler ) (TYPE_5__*) ;scalar_t__ ready; scalar_t__ timedout; TYPE_6__* data; int /*<<< orphan*/  log; } ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_20__ {scalar_t__ destroyed; int /*<<< orphan*/  write; TYPE_2__* log; TYPE_3__* data; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_16__ {char* action; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* auth_state ) (TYPE_5__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  NGX_MAIL_AUTH_PLAIN ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_read_event (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_mail_auth_http_init (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_mail_core_module ; 
 TYPE_4__* ngx_mail_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static void
ngx_mail_auth_sleep_handler(ngx_event_t *rev)
{
    ngx_connection_t          *c;
    ngx_mail_session_t        *s;
    ngx_mail_core_srv_conf_t  *cscf;

    ngx_log_debug0(NGX_LOG_DEBUG_MAIL, rev->log, 0, "mail auth sleep handler");

    c = rev->data;
    s = c->data;

    if (rev->timedout) {

        rev->timedout = 0;

        if (s->auth_wait) {
            s->auth_wait = 0;
            ngx_mail_auth_http_init(s);
            return;
        }

        cscf = ngx_mail_get_module_srv_conf(s, ngx_mail_core_module);

        rev->handler = cscf->protocol->auth_state;

        s->mail_state = 0;
        s->auth_method = NGX_MAIL_AUTH_PLAIN;

        c->log->action = "in auth state";

        ngx_mail_send(c->write);

        if (c->destroyed) {
            return;
        }

        ngx_add_timer(rev, cscf->timeout);

        if (rev->ready) {
            rev->handler(rev);
            return;
        }

        if (ngx_handle_read_event(rev, 0) != NGX_OK) {
            ngx_mail_close_connection(c);
        }

        return;
    }

    if (rev->active) {
        if (ngx_handle_read_event(rev, 0) != NGX_OK) {
            ngx_mail_close_connection(c);
        }
    }
}