#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_13__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_17__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {TYPE_2__* elts; } ;
struct TYPE_14__ {int /*<<< orphan*/  auth_method; TYPE_8__ passwd; TYPE_7__ login; TYPE_1__ args; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  NGX_MAIL_AUTH_CRAM_MD5 ; 
 int /*<<< orphan*/  NGX_MAIL_PARSE_INVALID_COMMAND ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_base64_decoded_length (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_decode_base64 (TYPE_7__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_mail_auth_cram_md5(ngx_mail_session_t *s, ngx_connection_t *c)
{
    u_char     *p, *last;
    ngx_str_t  *arg;

    arg = s->args.elts;

    ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "mail auth cram-md5: \"%V\"", &arg[0]);

    s->login.data = ngx_pnalloc(c->pool, ngx_base64_decoded_length(arg[0].len));
    if (s->login.data == NULL) {
        return NGX_ERROR;
    }

    if (ngx_decode_base64(&s->login, &arg[0]) != NGX_OK) {
        ngx_log_error(NGX_LOG_INFO, c->log, 0,
            "client sent invalid base64 encoding in AUTH CRAM-MD5 command");
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    p = s->login.data;
    last = p + s->login.len;

    while (p < last) {
        if (*p++ == ' ') {
            s->login.len = p - s->login.data - 1;
            s->passwd.len = last - p;
            s->passwd.data = p;
            break;
        }
    }

    if (s->passwd.len != 32) {
        ngx_log_error(NGX_LOG_INFO, c->log, 0,
            "client sent invalid CRAM-MD5 hash in AUTH CRAM-MD5 command");
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "mail auth cram-md5: \"%V\" \"%V\"", &s->login, &s->passwd);

    s->auth_method = NGX_MAIL_AUTH_CRAM_MD5;

    return NGX_DONE;
}