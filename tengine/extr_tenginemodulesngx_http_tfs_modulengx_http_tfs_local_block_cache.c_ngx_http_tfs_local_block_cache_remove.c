#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_15__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ ngx_slab_pool_t ;
struct TYPE_16__ {scalar_t__ key; struct TYPE_16__* right; struct TYPE_16__* left; int /*<<< orphan*/  color; } ;
typedef  TYPE_3__ ngx_rbtree_node_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {TYPE_2__* shpool; TYPE_1__* sh; } ;
typedef  TYPE_4__ ngx_http_tfs_local_block_cache_ctx_t ;
struct TYPE_18__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  key; } ;
typedef  TYPE_5__ ngx_http_tfs_block_cache_node_t ;
struct TYPE_19__ {int /*<<< orphan*/  block_id; int /*<<< orphan*/  ns_addr; } ;
typedef  TYPE_6__ ngx_http_tfs_block_cache_key_t ;
struct TYPE_20__ {TYPE_3__* sentinel; TYPE_3__* root; } ;
struct TYPE_14__ {TYPE_9__ rbtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_TFS_BLOCK_CACHE_KEY_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ ngx_http_tfs_block_cache_cmp (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_murmur_hash2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_queue_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rbtree_delete (TYPE_9__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_slab_free_locked (TYPE_2__*,TYPE_3__*) ; 

void
ngx_http_tfs_local_block_cache_remove(ngx_http_tfs_local_block_cache_ctx_t *ctx,
    ngx_log_t *log, ngx_http_tfs_block_cache_key_t* key)
{
    ngx_int_t                         rc;
    ngx_uint_t                        hash;
    ngx_slab_pool_t                  *shpool;
    ngx_rbtree_node_t                *node, *sentinel;
    ngx_http_tfs_block_cache_node_t  *bcn;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, log, 0,
                   "remove local block cache, ns addr: %uL, block id: %uD",
                   key->ns_addr, key->block_id);

    shpool = ctx->shpool;
    ngx_shmtx_lock(&shpool->mutex);

    node = ctx->sh->rbtree.root;
    sentinel = ctx->sh->rbtree.sentinel;

    hash = ngx_murmur_hash2((u_char*)key, NGX_HTTP_TFS_BLOCK_CACHE_KEY_SIZE);

    while (node != sentinel) {

        if (hash < node->key) {
            node = node->left;
            continue;
        }

        if (hash > node->key) {
            node = node->right;
            continue;
        }

        /* hash == node->key */
        do {
            bcn = (ngx_http_tfs_block_cache_node_t *) &node->color;
            rc = ngx_http_tfs_block_cache_cmp(key, &bcn->key);
            if (rc == 0) {
                ngx_rbtree_delete(&ctx->sh->rbtree, node);
                ngx_slab_free_locked(ctx->shpool, node);
                ngx_queue_remove(&bcn->queue);
                ngx_shmtx_unlock(&shpool->mutex);
                return;
            }
            node = (rc < 0) ? node->left : node->right;
        } while (node != sentinel && hash == node->key);
        break;
    }
    ngx_shmtx_unlock(&shpool->mutex);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, log, 0,
                   "remove local block cache, "
                   "ns addr: %uL, block id: %uD not found",
                   key->ns_addr, key->block_id);

}