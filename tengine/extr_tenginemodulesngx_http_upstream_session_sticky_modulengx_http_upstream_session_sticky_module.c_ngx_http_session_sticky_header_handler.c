#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {int flag; } ;
typedef  TYPE_1__ ngx_http_upstream_ss_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_srv_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/ * uscf; } ;
typedef  TYPE_2__ ngx_http_ss_loc_conf_t ;
struct TYPE_15__ {TYPE_1__* sscf; } ;
typedef  TYPE_3__ ngx_http_ss_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/ * NGX_CONF_UNSET_PTR ; 
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_SESSION_STICKY_REWRITE ; 
 TYPE_1__* ngx_http_conf_upstream_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_session_sticky_get_cookie (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_session_sticky_module ; 
 TYPE_3__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_session_sticky_header_handler(ngx_http_request_t *r)
{
    ngx_http_ss_ctx_t               *ctx;
    ngx_http_ss_loc_conf_t          *slcf;
    ngx_http_upstream_srv_conf_t    *uscf;
    ngx_http_upstream_ss_srv_conf_t *sscf;

    slcf = ngx_http_get_module_loc_conf(r,
                                    ngx_http_upstream_session_sticky_module);

    if (slcf->uscf == NGX_CONF_UNSET_PTR) {
        return NGX_DECLINED;
    }

    uscf = slcf->uscf;
    sscf = ngx_http_conf_upstream_srv_conf(uscf,
                                    ngx_http_upstream_session_sticky_module);
    if (sscf != NULL &&
        (sscf->flag & NGX_HTTP_SESSION_STICKY_REWRITE)) {
        return NGX_DECLINED;
    }

    ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_ss_ctx_t));
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_http_set_ctx(r, ctx, ngx_http_upstream_session_sticky_module);
    ctx->sscf = sscf;

    return ngx_http_session_sticky_get_cookie(r);
}