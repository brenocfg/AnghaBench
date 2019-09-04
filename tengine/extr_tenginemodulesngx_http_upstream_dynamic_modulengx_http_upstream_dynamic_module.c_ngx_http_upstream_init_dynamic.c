#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_16__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  init; } ;
struct TYPE_17__ {TYPE_2__ peer; TYPE_1__* servers; } ;
typedef  TYPE_4__ ngx_http_upstream_srv_conf_t ;
struct TYPE_18__ {TYPE_3__ host; } ;
typedef  TYPE_5__ ngx_http_upstream_server_t ;
struct TYPE_19__ {scalar_t__ (* original_init_upstream ) (TYPE_7__*,TYPE_4__*) ;int enabled; int /*<<< orphan*/  original_init_peer; } ;
typedef  TYPE_6__ ngx_http_upstream_dynamic_srv_conf_t ;
struct TYPE_20__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_7__ ngx_conf_t ;
struct TYPE_14__ {size_t nelts; TYPE_5__* elts; } ;

/* Variables and functions */
 scalar_t__ INADDR_NONE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 TYPE_6__* ngx_http_conf_upstream_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_dynamic_module ; 
 int /*<<< orphan*/  ngx_http_upstream_init_dynamic_peer ; 
 scalar_t__ ngx_inet_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (TYPE_7__*,TYPE_4__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_init_dynamic(ngx_conf_t *cf,
    ngx_http_upstream_srv_conf_t *us)
{
    ngx_uint_t                             i;
    ngx_http_upstream_dynamic_srv_conf_t  *dcf;
    ngx_http_upstream_server_t            *server;
    ngx_str_t                              host;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, cf->log, 0,
                   "init dynamic resolve");

    dcf = ngx_http_conf_upstream_srv_conf(us,
                                          ngx_http_upstream_dynamic_module);

    if (dcf->original_init_upstream(cf, us) != NGX_OK) {
        return NGX_ERROR;
    }

    if (us->servers) {
        server = us->servers->elts;

        for (i = 0; i < us->servers->nelts; i++) {
            host = server[i].host;
            if (ngx_inet_addr(host.data, host.len) == INADDR_NONE) {
                break;
            }
        }

        if (i == us->servers->nelts) {
            dcf->enabled = 0;

            return NGX_OK;
        }
    }

    dcf->original_init_peer = us->peer.init;

    us->peer.init = ngx_http_upstream_init_dynamic_peer;

    dcf->enabled = 1;

    return NGX_OK;
}