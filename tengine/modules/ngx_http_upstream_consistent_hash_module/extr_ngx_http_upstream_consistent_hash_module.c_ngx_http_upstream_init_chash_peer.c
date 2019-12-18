#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_srv_conf_t ;
struct TYPE_19__ {TYPE_2__* values; TYPE_1__* lengths; } ;
typedef  TYPE_6__ ngx_http_upstream_chash_srv_conf_t ;
struct TYPE_20__ {int /*<<< orphan*/  hash; TYPE_6__* ucscf; } ;
typedef  TYPE_7__ ngx_http_upstream_chash_peer_data_t ;
struct TYPE_21__ {TYPE_4__* upstream; int /*<<< orphan*/  pool; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_16__ {int /*<<< orphan*/  save_session; int /*<<< orphan*/  set_session; TYPE_7__* data; int /*<<< orphan*/  free; int /*<<< orphan*/  get; } ;
struct TYPE_17__ {TYPE_3__ peer; } ;
struct TYPE_15__ {int /*<<< orphan*/  elts; } ;
struct TYPE_14__ {int /*<<< orphan*/  elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_6__* ngx_http_conf_upstream_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_script_run (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_chash_save_peer_session ; 
 int /*<<< orphan*/  ngx_http_upstream_chash_set_peer_session ; 
 int /*<<< orphan*/  ngx_http_upstream_consistent_hash_module ; 
 int /*<<< orphan*/  ngx_http_upstream_free_chash_peer ; 
 int /*<<< orphan*/  ngx_http_upstream_get_chash_peer ; 
 int /*<<< orphan*/  ngx_murmur_hash2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_init_chash_peer(ngx_http_request_t *r,
    ngx_http_upstream_srv_conf_t *us)
{
    ngx_str_t                            hash_value;
    ngx_http_upstream_chash_srv_conf_t  *ucscf;
    ngx_http_upstream_chash_peer_data_t *uchpd;

    ucscf = ngx_http_conf_upstream_srv_conf(us,
                                     ngx_http_upstream_consistent_hash_module);
    if (ucscf == NULL) {
        return NGX_ERROR;
    }

    uchpd = ngx_pcalloc(r->pool, sizeof(ngx_http_upstream_chash_peer_data_t));
    if (uchpd == NULL) {
        return NGX_ERROR;
    }

    uchpd->ucscf = ucscf;
    if (ngx_http_script_run(r, &hash_value,
                ucscf->lengths->elts, 0, ucscf->values->elts) == NULL) {
        return NGX_ERROR;
    }

    uchpd->hash = ngx_murmur_hash2(hash_value.data, hash_value.len);

    r->upstream->peer.get = ngx_http_upstream_get_chash_peer;
    r->upstream->peer.free = ngx_http_upstream_free_chash_peer;
    r->upstream->peer.data = uchpd;

#if (NGX_HTTP_SSL)
    r->upstream->peer.set_session = ngx_http_upstream_chash_set_peer_session;
    r->upstream->peer.save_session = ngx_http_upstream_chash_save_peer_session;
#endif

    return NGX_OK;
}