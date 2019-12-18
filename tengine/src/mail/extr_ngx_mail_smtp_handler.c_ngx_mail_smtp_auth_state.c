#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_1__ ;

/* Type definitions */
struct TYPE_36__ {int /*<<< orphan*/  nelts; } ;
struct TYPE_41__ {scalar_t__ len; } ;
struct TYPE_38__ {int blocked; int mail_state; int quit; scalar_t__ arg_start; TYPE_2__* buffer; int /*<<< orphan*/  state; TYPE_1__ args; TYPE_6__ out; int /*<<< orphan*/  command; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
typedef  int ngx_int_t ;
struct TYPE_39__ {scalar_t__ timedout; TYPE_5__* data; } ;
typedef  TYPE_4__ ngx_event_t ;
struct TYPE_40__ {int timedout; int /*<<< orphan*/  write; int /*<<< orphan*/  log; TYPE_3__* data; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_37__ {scalar_t__ pos; scalar_t__ last; scalar_t__ start; } ;

/* Variables and functions */
 int NGX_AGAIN ; 
#define  NGX_DONE 146 
#define  NGX_ERROR 145 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
#define  NGX_MAIL_PARSE_INVALID_COMMAND 144 
#define  NGX_OK 143 
#define  NGX_SMTP_AUTH 142 
#define  NGX_SMTP_EHLO 141 
#define  NGX_SMTP_HELO 140 
#define  NGX_SMTP_MAIL 139 
#define  NGX_SMTP_NOOP 138 
#define  NGX_SMTP_QUIT 137 
#define  NGX_SMTP_RCPT 136 
#define  NGX_SMTP_RSET 135 
#define  NGX_SMTP_STARTTLS 134 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_mail_auth (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_auth_cram_md5 (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_auth_external (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int ngx_mail_auth_login_password (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_auth_login_username (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int ngx_mail_auth_plain (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_5__*) ; 
 int ngx_mail_read_command (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_mail_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_session_internal_server_error (TYPE_3__*) ; 
 int ngx_mail_smtp_auth (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_smtp_helo (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_smtp_mail (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_smtp_rcpt (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_smtp_rset (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_smtp_starttls (TYPE_3__*,TYPE_5__*) ; 
#define  ngx_smtp_auth_cram_md5 133 
#define  ngx_smtp_auth_external 132 
#define  ngx_smtp_auth_login_password 131 
#define  ngx_smtp_auth_login_username 130 
#define  ngx_smtp_auth_plain 129 
#define  ngx_smtp_start 128 
 int /*<<< orphan*/  ngx_str_set (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smtp_bye ; 
 int /*<<< orphan*/  smtp_invalid_command ; 
 int /*<<< orphan*/  smtp_ok ; 
 int /*<<< orphan*/  smtp_password ; 
 int /*<<< orphan*/  smtp_starttls ; 

void
ngx_mail_smtp_auth_state(ngx_event_t *rev)
{
    ngx_int_t            rc;
    ngx_connection_t    *c;
    ngx_mail_session_t  *s;

    c = rev->data;
    s = c->data;

    ngx_log_debug0(NGX_LOG_DEBUG_MAIL, c->log, 0, "smtp auth state");

    if (rev->timedout) {
        ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT, "client timed out");
        c->timedout = 1;
        ngx_mail_close_connection(c);
        return;
    }

    if (s->out.len) {
        ngx_log_debug0(NGX_LOG_DEBUG_MAIL, c->log, 0, "smtp send handler busy");
        s->blocked = 1;
        return;
    }

    s->blocked = 0;

    rc = ngx_mail_read_command(s, c);

    if (rc == NGX_AGAIN || rc == NGX_ERROR) {
        return;
    }

    ngx_str_set(&s->out, smtp_ok);

    if (rc == NGX_OK) {
        switch (s->mail_state) {

        case ngx_smtp_start:

            switch (s->command) {

            case NGX_SMTP_HELO:
            case NGX_SMTP_EHLO:
                rc = ngx_mail_smtp_helo(s, c);
                break;

            case NGX_SMTP_AUTH:
                rc = ngx_mail_smtp_auth(s, c);
                break;

            case NGX_SMTP_QUIT:
                s->quit = 1;
                ngx_str_set(&s->out, smtp_bye);
                break;

            case NGX_SMTP_MAIL:
                rc = ngx_mail_smtp_mail(s, c);
                break;

            case NGX_SMTP_RCPT:
                rc = ngx_mail_smtp_rcpt(s, c);
                break;

            case NGX_SMTP_RSET:
                rc = ngx_mail_smtp_rset(s, c);
                break;

            case NGX_SMTP_NOOP:
                break;

            case NGX_SMTP_STARTTLS:
                rc = ngx_mail_smtp_starttls(s, c);
                ngx_str_set(&s->out, smtp_starttls);
                break;

            default:
                rc = NGX_MAIL_PARSE_INVALID_COMMAND;
                break;
            }

            break;

        case ngx_smtp_auth_login_username:
            rc = ngx_mail_auth_login_username(s, c, 0);

            ngx_str_set(&s->out, smtp_password);
            s->mail_state = ngx_smtp_auth_login_password;
            break;

        case ngx_smtp_auth_login_password:
            rc = ngx_mail_auth_login_password(s, c);
            break;

        case ngx_smtp_auth_plain:
            rc = ngx_mail_auth_plain(s, c, 0);
            break;

        case ngx_smtp_auth_cram_md5:
            rc = ngx_mail_auth_cram_md5(s, c);
            break;

        case ngx_smtp_auth_external:
            rc = ngx_mail_auth_external(s, c, 0);
            break;
        }
    }

    if (s->buffer->pos < s->buffer->last) {
        s->blocked = 1;
    }

    switch (rc) {

    case NGX_DONE:
        ngx_mail_auth(s, c);
        return;

    case NGX_ERROR:
        ngx_mail_session_internal_server_error(s);
        return;

    case NGX_MAIL_PARSE_INVALID_COMMAND:
        s->mail_state = ngx_smtp_start;
        s->state = 0;
        ngx_str_set(&s->out, smtp_invalid_command);

        /* fall through */

    case NGX_OK:
        s->args.nelts = 0;

        if (s->buffer->pos == s->buffer->last) {
            s->buffer->pos = s->buffer->start;
            s->buffer->last = s->buffer->start;
        }

        if (s->state) {
            s->arg_start = s->buffer->pos;
        }

        ngx_mail_send(c->write);
    }
}