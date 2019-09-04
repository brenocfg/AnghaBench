#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  char u_char ;
typedef  void* time_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_22__ {char* data; int len; } ;
struct TYPE_21__ {scalar_t__ hash; TYPE_6__ value; } ;
typedef  TYPE_5__ ngx_table_elt_t ;
typedef  TYPE_6__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_20__ {int len; scalar_t__ data; } ;
struct TYPE_23__ {int flag; scalar_t__ maxidle; int maxlife; TYPE_4__ cookie; } ;
typedef  TYPE_7__ ngx_http_upstream_ss_srv_conf_t ;
struct TYPE_16__ {char* data; int len; } ;
struct TYPE_24__ {int tries; int frist; void* firstseen; void* lastseen; TYPE_6__ sid; TYPE_12__ s_lastseen; TYPE_7__* sscf; TYPE_12__ s_firstseen; } ;
typedef  TYPE_8__ ngx_http_ss_ctx_t ;
struct TYPE_17__ {size_t nelts; scalar_t__ elts; } ;
struct TYPE_18__ {TYPE_1__ cookies; } ;
struct TYPE_25__ {TYPE_3__* connection; int /*<<< orphan*/  pool; TYPE_2__ headers_in; } ;
typedef  TYPE_9__ ngx_http_request_t ;
struct TYPE_19__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_CONF_UNSET ; 
 int NGX_ERROR ; 
 char NGX_HTTP_SESSION_STICKY_DELIMITER ; 
 int NGX_HTTP_SESSION_STICKY_INDIRECT ; 
 int NGX_HTTP_SESSION_STICKY_INSERT ; 
 int NGX_HTTP_SESSION_STICKY_PREFIX ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int NGX_OK ; 
 int /*<<< orphan*/  is_space (char) ; 
 void* ngx_atotm (char*,int) ; 
 TYPE_8__* ngx_http_get_module_ctx (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_session_sticky_tmtoa (TYPE_9__*,TYPE_12__*,void*) ; 
 int /*<<< orphan*/  ngx_http_upstream_session_sticky_module ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_memcpy (char*,char*,int) ; 
 void* ngx_pnalloc (int /*<<< orphan*/ ,int) ; 
 char* ngx_strnstr (char*,char*,int) ; 
 void* ngx_time () ; 

__attribute__((used)) static ngx_int_t
ngx_http_session_sticky_get_cookie(ngx_http_request_t *r)
{
    time_t                           now;
    u_char                          *p, *v, *vv, *st, *last, *end;
    ngx_int_t                        diff, delimiter, legal;
    ngx_str_t                       *cookie;
    ngx_uint_t                       i;
    ngx_table_elt_t                **cookies;
    ngx_http_ss_ctx_t               *ctx;
    ngx_http_upstream_ss_srv_conf_t *sscf;
    enum {
        pre_key = 0,
        key,
        pre_equal,
        pre_value,
        value
    } state;

    legal = 1;
    ctx = ngx_http_get_module_ctx(r, ngx_http_upstream_session_sticky_module);
    sscf = ctx->sscf;
    ctx->tries = 1;

    p = NULL;
    cookie = NULL;
    now = ngx_time();
    cookies = (ngx_table_elt_t **) r->headers_in.cookies.elts;
    for (i = 0; i < r->headers_in.cookies.nelts; i++) {
        cookie = &cookies[i]->value;
        p = ngx_strnstr(cookie->data, (char *) sscf->cookie.data, cookie->len);
        if (p == NULL) {
            continue;
        }

        if (*(p + sscf->cookie.len) == ' ' || *(p + sscf->cookie.len) == '=') {
            break;
        }
    }

    if (i >= r->headers_in.cookies.nelts) {
        goto not_found;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "session sticky cookie: \"%V\"", &cookies[i]->value);
    st = p;
    v = p + sscf->cookie.len + 1;
    last = cookie->data + cookie->len;

    state = 0;
    while (p < last) {
        switch (state) {
        case pre_key:
            if (*p == ';') {
                goto not_found;

            } else if (!is_space(*p)) {
                state = key;
            }

            break;

        case key:
            if (is_space(*p)) {
                state = pre_equal;

            } else if (*p == '=') {
                state = pre_value;
            }

            break;

        case pre_equal:
            if (*p == '=') {
                state = pre_value;

            } else if (!is_space(*p)) {
                goto not_found;
            }

            break;

        case pre_value:
            if (!is_space(*p)) {
                state = value;
                v = p--;
            }

            break;

        case value:
            if (*p == ';') {
                end = p + 1;
                goto success;
            }

            if (p + 1 == last) {
                end = last;
                p++;
                goto success;
            }

            break;

        default:
                break;
        }

        p++;
    }

not_found:

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "session sticky [firstseen]");
    ctx->frist = 1;
    ctx->sid.len = 0;
    ctx->sid.data = NULL;
    ctx->firstseen = now;
    ctx->lastseen = now;

    ngx_http_session_sticky_tmtoa(r, &ctx->s_lastseen, ctx->lastseen);
    ngx_http_session_sticky_tmtoa(r, &ctx->s_firstseen, ctx->firstseen);

    if (ctx->s_lastseen.data == NULL || ctx->s_firstseen.data == NULL) {
        return NGX_ERROR;
    }

    return NGX_OK;

success:

    if (sscf->flag & NGX_HTTP_SESSION_STICKY_PREFIX) {

        for (vv = v; vv < p; vv++) {
            if (*vv == '~') {
                end = vv + 1;
                break;
            }
        }
        if (vv >= p) {
            goto not_found;
        }
        st = v;

    } else {
        vv = p;
    }

    if ((sscf->flag & NGX_HTTP_SESSION_STICKY_INSERT)
        && sscf->maxidle != NGX_CONF_UNSET)
    {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "session_sticky mode [insert]");

        delimiter = 0;
        for (p = v; p < vv; p++) {
            if (*p == NGX_HTTP_SESSION_STICKY_DELIMITER) {
                delimiter++;
                if (delimiter == 1) {
                    ctx->sid.len = p - v;
                    ctx->sid.data = ngx_pnalloc(r->pool, ctx->sid.len);
                    if (ctx->sid.data == NULL) {
                        return NGX_ERROR;
                    }
                    ngx_memcpy(ctx->sid.data, v, ctx->sid.len);
                    v = p + 1;

                } else if(delimiter == 2) {
                    ctx->s_lastseen.len = p - v;
                    ctx->s_lastseen.data = ngx_pnalloc(r->pool,
                                                       ctx->s_lastseen.len);
                    if (ctx->s_lastseen.data == NULL) {
                        return NGX_ERROR;
                    }
                    ngx_memcpy(ctx->s_lastseen.data, v, ctx->s_lastseen.len);
                    v = p + 1;
                    break;

                } else {
                    legal = 0;
                    goto finish;
                }
            }
        }

        if (p >= vv || v >= vv) {
            legal = 0;
            goto finish;

        }

        ctx->s_firstseen.len = vv - v;
        ctx->s_firstseen.data = ngx_pnalloc(r->pool, ctx->s_firstseen.len);
        if (ctx->s_firstseen.data == NULL) {
            return NGX_ERROR;
        }
        ngx_memcpy(ctx->s_firstseen.data, v, ctx->s_firstseen.len);

        ctx->firstseen = ngx_atotm(ctx->s_firstseen.data, ctx->s_firstseen.len);
        ctx->lastseen = ngx_atotm(ctx->s_lastseen.data, ctx->s_lastseen.len);

        if (ctx->firstseen == NGX_ERROR || ctx->lastseen == NGX_ERROR) {
            legal = 0;
            goto finish;
        }

        if (ctx->sid.len != 0) {
            diff = (ngx_int_t) (now - ctx->lastseen);
            if (diff > ctx->sscf->maxidle || diff < -86400) {
                legal = 0;
                goto finish;
            }

            diff = (ngx_int_t) (now - ctx->firstseen);
            if (diff > ctx->sscf->maxlife || diff < -86400) {
                legal = 0;
                goto finish;
            }
        }

        ngx_http_session_sticky_tmtoa(r, &ctx->s_lastseen, now);

    } else {
        ctx->sid.len = vv - v;
        ctx->sid.data = ngx_pnalloc(r->pool, ctx->sid.len);
        if (ctx->sid.data == NULL) {
            return NGX_ERROR;
        }
        ngx_memcpy(ctx->sid.data, v, ctx->sid.len);
    }

finish:

    if (sscf->flag
        & (NGX_HTTP_SESSION_STICKY_PREFIX | NGX_HTTP_SESSION_STICKY_INDIRECT))
    {
        cookie->len -= (end - st);

        if (cookie->len == 0) {
            cookies[i]->hash = 0;
            return NGX_OK;
        }

        while (end < last) {
            *st++ = *end++;
        }
    }

    if (legal == 0) {
        goto not_found;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "session sticky sid [%V]", &ctx->sid);
    return NGX_OK;
}