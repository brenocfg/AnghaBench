#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_16__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_11__ {int nelts; TYPE_4__* elts; } ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_14__ {int /*<<< orphan*/  auth_method; TYPE_9__ smtp_to; TYPE_3__ cmd; TYPE_2__ args; int /*<<< orphan*/  out; TYPE_1__ smtp_from; } ;
typedef  TYPE_5__ ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  NGX_MAIL_AUTH_NONE ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smtp_bad_sequence ; 
 int /*<<< orphan*/  smtp_invalid_argument ; 

__attribute__((used)) static ngx_int_t
ngx_mail_smtp_rcpt(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_str_t  *arg, cmd;

    if (s->smtp_from.len == 0) {
        ngx_str_set(&s->out, smtp_bad_sequence);
        return NGX_OK;
    }

    if (s->args.nelts == 0) {
        ngx_str_set(&s->out, smtp_invalid_argument);
        return NGX_OK;
    }

    arg = s->args.elts;
    arg += s->args.nelts - 1;

    cmd.len = arg->data + arg->len - s->cmd.data;
    cmd.data = s->cmd.data;

    s->smtp_to.len = cmd.len;

    s->smtp_to.data = ngx_pnalloc(c->pool, cmd.len);
    if (s->smtp_to.data == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(s->smtp_to.data, cmd.data, cmd.len);

    ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "smtp rcpt to:\"%V\"", &s->smtp_to);

    s->auth_method = NGX_MAIL_AUTH_NONE;

    return NGX_DONE;
}