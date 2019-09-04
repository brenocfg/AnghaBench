#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_segment_tree_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {scalar_t__ data; int /*<<< orphan*/  init; } ;
struct TYPE_23__ {TYPE_1__ peer; } ;
typedef  TYPE_4__ ngx_http_upstream_srv_conf_t ;
struct TYPE_24__ {int number; TYPE_6__* peer; } ;
typedef  TYPE_5__ ngx_http_upstream_rr_peers_t ;
struct TYPE_21__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_25__ {int weight; int /*<<< orphan*/  name; TYPE_2__ id; } ;
typedef  TYPE_6__ ngx_http_upstream_rr_peer_t ;
struct TYPE_26__ {int number; int /*<<< orphan*/  down_servers; TYPE_10__* tree; TYPE_8__* servers; TYPE_8__*** real_node; TYPE_3__* d_servers; } ;
typedef  TYPE_7__ ngx_http_upstream_chash_srv_conf_t ;
struct TYPE_27__ {int rnindex; int index; void* hash; TYPE_6__* peer; } ;
typedef  TYPE_8__ ngx_http_upstream_chash_server_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_chash_down_server_t ;
struct TYPE_28__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_9__ ngx_conf_t ;
struct TYPE_22__ {int id; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* build ) (TYPE_10__*,int,int,int) ;} ;

/* Variables and functions */
 int NGX_CHASH_VIRTUAL_NODE_NUMBER ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_atoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* ngx_calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_free (int*) ; 
 TYPE_7__* ngx_http_conf_upstream_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_upstream_chash_cmp ; 
 int /*<<< orphan*/  ngx_http_upstream_consistent_hash_module ; 
 int /*<<< orphan*/  ngx_http_upstream_init_chash_peer ; 
 scalar_t__ ngx_http_upstream_init_round_robin (TYPE_9__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 void* ngx_murmur_hash2 (int /*<<< orphan*/ *,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_qsort (TYPE_8__*,size_t,int,void const*) ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_segment_tree_init (TYPE_10__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_snprintf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int ngx_strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_10__*,int,int,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_init_chash(ngx_conf_t *cf, ngx_http_upstream_srv_conf_t *us)
{
    u_char                               hash_buf[256];
    ngx_int_t                            j, weight;
    ngx_uint_t                           sid, id, hash_len;
    ngx_uint_t                           i, n, *number, rnindex;
    ngx_http_upstream_rr_peer_t         *peer;
    ngx_http_upstream_rr_peers_t        *peers;
    ngx_http_upstream_chash_server_t    *server;
    ngx_http_upstream_chash_srv_conf_t  *ucscf;

    if (ngx_http_upstream_init_round_robin(cf, us) == NGX_ERROR) {
        return NGX_ERROR;
    }

    ucscf = ngx_http_conf_upstream_srv_conf(us,
                                     ngx_http_upstream_consistent_hash_module);
    if (ucscf == NULL) {
        return NGX_ERROR;
    }

    us->peer.init = ngx_http_upstream_init_chash_peer;

    peers = (ngx_http_upstream_rr_peers_t *) us->peer.data;
    if (peers == NULL) {
        return NGX_ERROR;
    }

    n = peers->number;
    ucscf->number = 0;
    ucscf->real_node = ngx_pcalloc(cf->pool, n *
                                   sizeof(ngx_http_upstream_chash_server_t**));
    if (ucscf->real_node == NULL) {
        return NGX_ERROR;
    }
    for (i = 0; i < n; i++) {
        ucscf->number += peers->peer[i].weight * NGX_CHASH_VIRTUAL_NODE_NUMBER;
        ucscf->real_node[i] = ngx_pcalloc(cf->pool,
                                    (peers->peer[i].weight
                                     * NGX_CHASH_VIRTUAL_NODE_NUMBER + 1) *
                                     sizeof(ngx_http_upstream_chash_server_t*));
        if (ucscf->real_node[i] == NULL) {
            return NGX_ERROR;
        }
    }

    ucscf->servers = ngx_pcalloc(cf->pool,
                                 (ucscf->number + 1) *
                                  sizeof(ngx_http_upstream_chash_server_t));

    if (ucscf->servers == NULL) {
        return NGX_ERROR;
    }

    ucscf->d_servers = ngx_pcalloc(cf->pool,
                                (ucscf->number + 1) *
                                sizeof(ngx_http_upstream_chash_down_server_t));

    if (ucscf->d_servers == NULL) {
        return NGX_ERROR;
    }

    ucscf->number = 0;
    for (i = 0; i < n; i++) {

        peer = &peers->peer[i];
        sid = (ngx_uint_t) ngx_atoi(peer->id.data, peer->id.len);

        if (sid == (ngx_uint_t) NGX_ERROR || sid > 65535) {

            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, cf->log, 0, "server id %d", sid);

            ngx_snprintf(hash_buf, 256, "%V%Z", &peer->name);
            hash_len = ngx_strlen(hash_buf);
            sid = ngx_murmur_hash2(hash_buf, hash_len);
        }

        weight = peer->weight * NGX_CHASH_VIRTUAL_NODE_NUMBER;

        if (weight >= 1 << 14) {
            ngx_log_error(NGX_LOG_WARN, cf->log, 0,
                          "weigth[%d] is too large, is must be less than %d",
                          weight / NGX_CHASH_VIRTUAL_NODE_NUMBER,
                          (1 << 14) / NGX_CHASH_VIRTUAL_NODE_NUMBER);
            weight = 1 << 14;
        }

        for (j = 0; j < weight; j++) {
            server = &ucscf->servers[++ucscf->number];
            server->peer = peer;
            server->rnindex = i;

            id = sid * 256 * 16 + j;
            server->hash = ngx_murmur_hash2((u_char *) (&id), 4);
        }
    }

    ngx_qsort(ucscf->servers + 1, ucscf->number,
              sizeof(ngx_http_upstream_chash_server_t),
              (const void *)ngx_http_upstream_chash_cmp);

    number = ngx_calloc(n * sizeof(ngx_uint_t), cf->log);
    if (number == NULL) {
        return NGX_ERROR;
    }

    for (i = 1; i <= ucscf->number; i++) {
        ucscf->servers[i].index = i;
        ucscf->d_servers[i].id = i;
        rnindex = ucscf->servers[i].rnindex;
        ucscf->real_node[rnindex][number[rnindex]] = &ucscf->servers[i];
        number[rnindex]++;
    }

    ngx_free(number);

    ucscf->tree = ngx_pcalloc(cf->pool, sizeof(ngx_segment_tree_t));
    if (ucscf->tree == NULL) {
        return NGX_ERROR;
    }

    ngx_segment_tree_init(ucscf->tree, ucscf->number, cf->pool);
    ucscf->tree->build(ucscf->tree, 1, 1, ucscf->number);

    ngx_queue_init(&ucscf->down_servers);

    return NGX_OK;
}