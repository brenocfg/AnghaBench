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
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {scalar_t__ (* init_upstream ) (TYPE_3__*,TYPE_2__*) ;int /*<<< orphan*/  init; } ;
struct TYPE_18__ {TYPE_1__ peer; TYPE_5__** srv_conf; int /*<<< orphan*/ * servers; } ;
typedef  TYPE_2__ ngx_http_upstream_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_server_t ;
typedef  scalar_t__ (* ngx_http_upstream_init_pt ) (TYPE_3__*,TYPE_2__*) ;
struct TYPE_20__ {int /*<<< orphan*/  init; } ;
typedef  TYPE_5__ ngx_http_dyups_upstream_srv_conf_t ;
struct TYPE_21__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  pool; TYPE_2__* upstream; } ;
typedef  TYPE_6__ ngx_http_dyups_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
struct TYPE_19__ {char* name; int /*<<< orphan*/  ctx; int /*<<< orphan*/  log; int /*<<< orphan*/  cmd_type; void* module_type; int /*<<< orphan*/  pool; int /*<<< orphan*/ * args; int /*<<< orphan*/ * cycle; } ;
typedef  TYPE_3__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;
struct TYPE_15__ {size_t ctx_index; } ;

/* Variables and functions */
 scalar_t__ NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_MAIN_CONF ; 
 void* NGX_HTTP_MODULE ; 
 int /*<<< orphan*/  NGX_HTTP_UPS_CONF ; 
 scalar_t__ NGX_OK ; 
 void* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_14__* ngx_cycle ; 
 scalar_t__ ngx_dyups_parse_upstream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_dyups_init_peer ; 
 TYPE_11__ ngx_http_dyups_module ; 
 scalar_t__ ngx_http_upstream_init_round_robin (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_dyups_add_server(ngx_http_dyups_srv_conf_t *duscf, ngx_buf_t *buf)
{
    ngx_conf_t                           cf;
    ngx_http_upstream_init_pt            init;
    ngx_http_upstream_srv_conf_t        *uscf;
    ngx_http_dyups_upstream_srv_conf_t  *dscf;

    uscf = duscf->upstream;

    if (uscf->servers == NULL) {
        uscf->servers = ngx_array_create(duscf->pool, 4,
                                         sizeof(ngx_http_upstream_server_t));
        if (uscf->servers == NULL) {
            return NGX_ERROR;
        }
    }

    ngx_memzero(&cf, sizeof(ngx_conf_t));
    cf.name = "dyups_init_module_conf";
    cf.pool = duscf->pool;
    cf.module_type = NGX_HTTP_MODULE;
    cf.cmd_type = NGX_HTTP_UPS_CONF;
    cf.log = ngx_cycle->log;
    cf.ctx = duscf->ctx;
    cf.cycle = (ngx_cycle_t *) ngx_cycle;
    cf.args = ngx_array_create(duscf->pool, 10, sizeof(ngx_str_t));
    if (cf.args == NULL) {
        return NGX_ERROR;
    }

    if (ngx_dyups_parse_upstream(&cf, buf) != NGX_CONF_OK) {
        return NGX_ERROR;
    }

    ngx_memzero(&cf, sizeof(ngx_conf_t));
    cf.name = "dyups_init_upstream";
    cf.pool = duscf->pool;
    cf.module_type = NGX_HTTP_MODULE;
    cf.cmd_type = NGX_HTTP_MAIN_CONF;
    cf.log = ngx_cycle->log;
    cf.ctx = duscf->ctx;

    init = uscf->peer.init_upstream ? uscf->peer.init_upstream:
        ngx_http_upstream_init_round_robin;

    if (init(&cf, uscf) != NGX_OK) {
        return NGX_ERROR;
    }

#if (T_NGX_HTTP_UPSTREAM_RANDOM)
    {

    ngx_http_upstream_rr_peers_t        *peers, *backup;

    /* add init_number initialization */

    peers = uscf->peer.data;
    peers->init_number = ngx_random() % peers->number;
    backup = peers->next;

    if (backup) {
        backup->init_number = ngx_random() % backup->number;
    }

    }
#endif

    dscf = uscf->srv_conf[ngx_http_dyups_module.ctx_index];
    dscf->init = uscf->peer.init;

    uscf->peer.init = ngx_http_dyups_init_peer;

    return NGX_OK;
}