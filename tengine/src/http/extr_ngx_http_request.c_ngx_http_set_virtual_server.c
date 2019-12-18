#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_12__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_27__ {scalar_t__ verify; } ;
typedef  TYPE_3__ ngx_http_ssl_srv_conf_t ;
struct TYPE_28__ {TYPE_8__* connection; int /*<<< orphan*/  loc_conf; int /*<<< orphan*/  srv_conf; TYPE_7__* http_connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_29__ {TYPE_14__* ctx; } ;
typedef  TYPE_5__ ngx_http_core_srv_conf_t ;
struct TYPE_30__ {int /*<<< orphan*/  error_log; } ;
typedef  TYPE_6__ ngx_http_core_loc_conf_t ;
struct TYPE_31__ {TYPE_1__* addr_conf; TYPE_12__* ssl_servername; scalar_t__ ssl_servername_regex; } ;
typedef  TYPE_7__ ngx_http_connection_t ;
struct TYPE_32__ {int /*<<< orphan*/  log; } ;
struct TYPE_25__ {TYPE_5__* default_server; int /*<<< orphan*/  virtual_names; } ;
struct TYPE_24__ {int /*<<< orphan*/  loc_conf; int /*<<< orphan*/  srv_conf; } ;
struct TYPE_23__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_MISDIRECTED_REQUEST ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_close_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_find_virtual_server (TYPE_8__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_4__*,TYPE_5__**) ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_get_module_srv_conf (TYPE_14__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_regex_exec (TYPE_4__*,scalar_t__,TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_http_ssl_module ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_set_connection_log (TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_set_virtual_server(ngx_http_request_t *r, ngx_str_t *host)
{
    ngx_int_t                  rc;
    ngx_http_connection_t     *hc;
    ngx_http_core_loc_conf_t  *clcf;
    ngx_http_core_srv_conf_t  *cscf;

#if (NGX_SUPPRESS_WARN)
    cscf = NULL;
#endif

    hc = r->http_connection;

#if (NGX_HTTP_SSL && defined SSL_CTRL_SET_TLSEXT_HOSTNAME)

    if (hc->ssl_servername) {
        if (hc->ssl_servername->len == host->len
            && ngx_strncmp(hc->ssl_servername->data,
                           host->data, host->len) == 0)
        {
#if (NGX_PCRE)
            if (hc->ssl_servername_regex
                && ngx_http_regex_exec(r, hc->ssl_servername_regex,
                                          hc->ssl_servername) != NGX_OK)
            {
                ngx_http_close_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
                return NGX_ERROR;
            }
#endif
            return NGX_OK;
        }
    }

#endif

    rc = ngx_http_find_virtual_server(r->connection,
                                      hc->addr_conf->virtual_names,
                                      host, r, &cscf);

    if (rc == NGX_ERROR) {
        ngx_http_close_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return NGX_ERROR;
    }

#if (NGX_HTTP_SSL && defined SSL_CTRL_SET_TLSEXT_HOSTNAME)

    if (hc->ssl_servername) {
        ngx_http_ssl_srv_conf_t  *sscf;

        if (rc == NGX_DECLINED) {
            cscf = hc->addr_conf->default_server;
            rc = NGX_OK;
        }

        sscf = ngx_http_get_module_srv_conf(cscf->ctx, ngx_http_ssl_module);

        if (sscf->verify) {
            ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                          "client attempted to request the server name "
                          "different from the one that was negotiated");
            ngx_http_finalize_request(r, NGX_HTTP_MISDIRECTED_REQUEST);
            return NGX_ERROR;
        }
    }

#endif

    if (rc == NGX_DECLINED) {
        return NGX_OK;
    }

    r->srv_conf = cscf->ctx->srv_conf;
    r->loc_conf = cscf->ctx->loc_conf;

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    ngx_set_connection_log(r->connection, clcf->error_log);

    return NGX_OK;
}