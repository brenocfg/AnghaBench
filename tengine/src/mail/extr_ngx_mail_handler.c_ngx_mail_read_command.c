#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_18__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_19__ {int quit; TYPE_2__* buffer; } ;
typedef  TYPE_4__ ngx_mail_session_t ;
struct TYPE_20__ {TYPE_1__* protocol; } ;
typedef  TYPE_5__ ngx_mail_core_srv_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {scalar_t__ (* recv ) (TYPE_6__*,scalar_t__,scalar_t__) ;int /*<<< orphan*/  log; int /*<<< orphan*/  read; } ;
typedef  TYPE_6__ ngx_connection_t ;
struct TYPE_17__ {scalar_t__ last; scalar_t__ end; scalar_t__ pos; scalar_t__ start; } ;
struct TYPE_16__ {scalar_t__ (* parse_command ) (TYPE_4__*) ;} ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_IMAP_NEXT ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_MAIL_PARSE_INVALID_COMMAND ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_handle_read_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_mail_core_module ; 
 TYPE_5__* ngx_mail_get_module_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_session_internal_server_error (TYPE_4__*) ; 
 scalar_t__ stub1 (TYPE_6__*,scalar_t__,scalar_t__) ; 
 scalar_t__ stub2 (TYPE_4__*) ; 

ngx_int_t
ngx_mail_read_command(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ssize_t                    n;
    ngx_int_t                  rc;
    ngx_str_t                  l;
    ngx_mail_core_srv_conf_t  *cscf;

    n = c->recv(c, s->buffer->last, s->buffer->end - s->buffer->last);

    if (n == NGX_ERROR || n == 0) {
        ngx_mail_close_connection(c);
        return NGX_ERROR;
    }

    if (n > 0) {
        s->buffer->last += n;
    }

    if (n == NGX_AGAIN) {
        if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
            ngx_mail_session_internal_server_error(s);
            return NGX_ERROR;
        }

        if (s->buffer->pos == s->buffer->last) {
            return NGX_AGAIN;
        }
    }

    cscf = ngx_mail_get_module_srv_conf(s, ngx_mail_core_module);

    rc = cscf->protocol->parse_command(s);

    if (rc == NGX_AGAIN) {

        if (s->buffer->last < s->buffer->end) {
            return rc;
        }

        l.len = s->buffer->last - s->buffer->start;
        l.data = s->buffer->start;

        ngx_log_error(NGX_LOG_INFO, c->log, 0,
                      "client sent too long command \"%V\"", &l);

        s->quit = 1;

        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    if (rc == NGX_IMAP_NEXT || rc == NGX_MAIL_PARSE_INVALID_COMMAND) {
        return rc;
    }

    if (rc == NGX_ERROR) {
        ngx_mail_close_connection(c);
        return NGX_ERROR;
    }

    return NGX_OK;
}