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
struct TYPE_38__ {int blocked; int mail_state; int quit; TYPE_2__* buffer; int /*<<< orphan*/  arg_start; int /*<<< orphan*/  state; TYPE_1__ args; TYPE_6__ out; int /*<<< orphan*/  command; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
typedef  int ngx_int_t ;
struct TYPE_39__ {scalar_t__ timedout; TYPE_5__* data; } ;
typedef  TYPE_4__ ngx_event_t ;
struct TYPE_40__ {int timedout; int /*<<< orphan*/  write; int /*<<< orphan*/  log; TYPE_3__* data; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_37__ {int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int NGX_AGAIN ; 
#define  NGX_DONE 147 
#define  NGX_ERROR 146 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
#define  NGX_MAIL_PARSE_INVALID_COMMAND 145 
#define  NGX_OK 144 
#define  NGX_POP3_APOP 143 
#define  NGX_POP3_AUTH 142 
#define  NGX_POP3_CAPA 141 
#define  NGX_POP3_NOOP 140 
#define  NGX_POP3_PASS 139 
#define  NGX_POP3_QUIT 138 
#define  NGX_POP3_STLS 137 
#define  NGX_POP3_USER 136 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_mail_auth (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_auth_cram_md5 (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_auth_external (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int ngx_mail_auth_login_password (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_auth_login_username (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int ngx_mail_auth_plain (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_5__*) ; 
 int ngx_mail_pop3_apop (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_pop3_auth (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_pop3_capa (TYPE_3__*,TYPE_5__*,int) ; 
 int ngx_mail_pop3_pass (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_pop3_stls (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_pop3_user (TYPE_3__*,TYPE_5__*) ; 
 int ngx_mail_read_command (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_mail_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_session_internal_server_error (TYPE_3__*) ; 
#define  ngx_pop3_auth_cram_md5 135 
#define  ngx_pop3_auth_external 134 
#define  ngx_pop3_auth_login_password 133 
#define  ngx_pop3_auth_login_username 132 
#define  ngx_pop3_auth_plain 131 
#define  ngx_pop3_passwd 130 
#define  ngx_pop3_start 129 
#define  ngx_pop3_user 128 
 int /*<<< orphan*/  ngx_str_set (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop3_invalid_command ; 
 int /*<<< orphan*/  pop3_ok ; 
 int /*<<< orphan*/  pop3_password ; 

void
ngx_mail_pop3_auth_state(ngx_event_t *rev)
{
    ngx_int_t            rc;
    ngx_connection_t    *c;
    ngx_mail_session_t  *s;

    c = rev->data;
    s = c->data;

    ngx_log_debug0(NGX_LOG_DEBUG_MAIL, c->log, 0, "pop3 auth state");

    if (rev->timedout) {
        ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT, "client timed out");
        c->timedout = 1;
        ngx_mail_close_connection(c);
        return;
    }

    if (s->out.len) {
        ngx_log_debug0(NGX_LOG_DEBUG_MAIL, c->log, 0, "pop3 send handler busy");
        s->blocked = 1;
        return;
    }

    s->blocked = 0;

    rc = ngx_mail_read_command(s, c);

    if (rc == NGX_AGAIN || rc == NGX_ERROR) {
        return;
    }

    ngx_str_set(&s->out, pop3_ok);

    if (rc == NGX_OK) {
        switch (s->mail_state) {

        case ngx_pop3_start:

            switch (s->command) {

            case NGX_POP3_USER:
                rc = ngx_mail_pop3_user(s, c);
                break;

            case NGX_POP3_CAPA:
                rc = ngx_mail_pop3_capa(s, c, 1);
                break;

            case NGX_POP3_APOP:
                rc = ngx_mail_pop3_apop(s, c);
                break;

            case NGX_POP3_AUTH:
                rc = ngx_mail_pop3_auth(s, c);
                break;

            case NGX_POP3_QUIT:
                s->quit = 1;
                break;

            case NGX_POP3_NOOP:
                break;

            case NGX_POP3_STLS:
                rc = ngx_mail_pop3_stls(s, c);
                break;

            default:
                rc = NGX_MAIL_PARSE_INVALID_COMMAND;
                break;
            }

            break;

        case ngx_pop3_user:

            switch (s->command) {

            case NGX_POP3_PASS:
                rc = ngx_mail_pop3_pass(s, c);
                break;

            case NGX_POP3_CAPA:
                rc = ngx_mail_pop3_capa(s, c, 0);
                break;

            case NGX_POP3_QUIT:
                s->quit = 1;
                break;

            case NGX_POP3_NOOP:
                break;

            default:
                rc = NGX_MAIL_PARSE_INVALID_COMMAND;
                break;
            }

            break;

        /* suppress warnings */
        case ngx_pop3_passwd:
            break;

        case ngx_pop3_auth_login_username:
            rc = ngx_mail_auth_login_username(s, c, 0);

            ngx_str_set(&s->out, pop3_password);
            s->mail_state = ngx_pop3_auth_login_password;
            break;

        case ngx_pop3_auth_login_password:
            rc = ngx_mail_auth_login_password(s, c);
            break;

        case ngx_pop3_auth_plain:
            rc = ngx_mail_auth_plain(s, c, 0);
            break;

        case ngx_pop3_auth_cram_md5:
            rc = ngx_mail_auth_cram_md5(s, c);
            break;

        case ngx_pop3_auth_external:
            rc = ngx_mail_auth_external(s, c, 0);
            break;
        }
    }

    switch (rc) {

    case NGX_DONE:
        ngx_mail_auth(s, c);
        return;

    case NGX_ERROR:
        ngx_mail_session_internal_server_error(s);
        return;

    case NGX_MAIL_PARSE_INVALID_COMMAND:
        s->mail_state = ngx_pop3_start;
        s->state = 0;

        ngx_str_set(&s->out, pop3_invalid_command);

        /* fall through */

    case NGX_OK:

        s->args.nelts = 0;
        s->buffer->pos = s->buffer->start;
        s->buffer->last = s->buffer->start;

        if (s->state) {
            s->arg_start = s->buffer->start;
        }

        ngx_mail_send(c->write);
    }
}