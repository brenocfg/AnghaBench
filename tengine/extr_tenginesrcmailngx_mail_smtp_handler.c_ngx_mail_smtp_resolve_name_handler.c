#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_10__ {scalar_t__ state; size_t naddrs; TYPE_1__* addrs; int /*<<< orphan*/  name; TYPE_3__* data; } ;
typedef  TYPE_2__ ngx_resolver_ctx_t ;
struct TYPE_11__ {void* host; TYPE_4__* connection; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
struct TYPE_12__ {int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  log; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_9__ {int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_RESOLVE_NXDOMAIN ; 
 scalar_t__ ngx_cmp_sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_smtp_greeting (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_resolve_name_done (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_resolver_strerror (scalar_t__) ; 
 void* smtp_tempunavail ; 
 void* smtp_unavailable ; 

__attribute__((used)) static void
ngx_mail_smtp_resolve_name_handler(ngx_resolver_ctx_t *ctx)
{
    ngx_uint_t           i;
    ngx_connection_t    *c;
    ngx_mail_session_t  *s;

    s = ctx->data;
    c = s->connection;

    if (ctx->state) {
        ngx_log_error(NGX_LOG_ERR, c->log, 0,
                      "\"%V\" could not be resolved (%i: %s)",
                      &ctx->name, ctx->state,
                      ngx_resolver_strerror(ctx->state));

        if (ctx->state == NGX_RESOLVE_NXDOMAIN) {
            s->host = smtp_unavailable;

        } else {
            s->host = smtp_tempunavail;
        }

    } else {

#if (NGX_DEBUG)
        {
        u_char     text[NGX_SOCKADDR_STRLEN];
        ngx_str_t  addr;

        addr.data = text;

        for (i = 0; i < ctx->naddrs; i++) {
            addr.len = ngx_sock_ntop(ctx->addrs[i].sockaddr,
                                     ctx->addrs[i].socklen,
                                     text, NGX_SOCKADDR_STRLEN, 0);

            ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                           "name was resolved to %V", &addr);
        }
        }
#endif

        for (i = 0; i < ctx->naddrs; i++) {
            if (ngx_cmp_sockaddr(ctx->addrs[i].sockaddr, ctx->addrs[i].socklen,
                                 c->sockaddr, c->socklen, 0)
                == NGX_OK)
            {
                goto found;
            }
        }

        s->host = smtp_unavailable;
    }

found:

    ngx_resolve_name_done(ctx);

    ngx_mail_smtp_greeting(s, c);
}