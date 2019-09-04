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
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_rbtree_key_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {scalar_t__ fail_time; scalar_t__ inactive; TYPE_6__* shpool; TYPE_1__* sh; } ;
typedef  TYPE_2__ ngx_http_file_cache_t ;
struct TYPE_20__ {int /*<<< orphan*/  key; } ;
struct TYPE_17__ {int uses; int exists; int /*<<< orphan*/  queue; scalar_t__ expire; scalar_t__ fs_size; TYPE_7__ node; int /*<<< orphan*/ * key; } ;
typedef  TYPE_3__ ngx_http_file_cache_node_t ;
struct TYPE_18__ {scalar_t__ fs_size; int /*<<< orphan*/ * key; } ;
typedef  TYPE_4__ ngx_http_cache_t ;
struct TYPE_19__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  log_ctx; } ;
struct TYPE_15__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  size; int /*<<< orphan*/  rbtree; int /*<<< orphan*/  count; } ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_CACHE_KEY_LEN ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_13__* ngx_cycle ; 
 TYPE_3__* ngx_http_file_cache_lookup (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_file_cache_set_watermark (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rbtree_insert (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_slab_calloc_locked (TYPE_6__*,int) ; 
 scalar_t__ ngx_time () ; 

__attribute__((used)) static ngx_int_t
ngx_http_file_cache_add(ngx_http_file_cache_t *cache, ngx_http_cache_t *c)
{
    ngx_http_file_cache_node_t  *fcn;

    ngx_shmtx_lock(&cache->shpool->mutex);

    fcn = ngx_http_file_cache_lookup(cache, c->key);

    if (fcn == NULL) {

        fcn = ngx_slab_calloc_locked(cache->shpool,
                                     sizeof(ngx_http_file_cache_node_t));
        if (fcn == NULL) {
            ngx_http_file_cache_set_watermark(cache);

            if (cache->fail_time != ngx_time()) {
                cache->fail_time = ngx_time();
                ngx_log_error(NGX_LOG_ALERT, ngx_cycle->log, 0,
                           "could not allocate node%s", cache->shpool->log_ctx);
            }

            ngx_shmtx_unlock(&cache->shpool->mutex);
            return NGX_ERROR;
        }

        cache->sh->count++;

        ngx_memcpy((u_char *) &fcn->node.key, c->key, sizeof(ngx_rbtree_key_t));

        ngx_memcpy(fcn->key, &c->key[sizeof(ngx_rbtree_key_t)],
                   NGX_HTTP_CACHE_KEY_LEN - sizeof(ngx_rbtree_key_t));

        ngx_rbtree_insert(&cache->sh->rbtree, &fcn->node);

        fcn->uses = 1;
        fcn->exists = 1;
        fcn->fs_size = c->fs_size;

        cache->sh->size += c->fs_size;

    } else {
        ngx_queue_remove(&fcn->queue);
    }

    fcn->expire = ngx_time() + cache->inactive;

    ngx_queue_insert_head(&cache->sh->queue, &fcn->queue);

    ngx_shmtx_unlock(&cache->shpool->mutex);

    return NGX_OK;
}