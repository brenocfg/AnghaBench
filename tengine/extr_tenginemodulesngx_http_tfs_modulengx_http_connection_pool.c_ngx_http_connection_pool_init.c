#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_queue_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_4__ {int bucket_count; int max_cached; int /*<<< orphan*/  free_peer; int /*<<< orphan*/  get_peer; int /*<<< orphan*/ * free; int /*<<< orphan*/ * cache; } ;
typedef  TYPE_1__ ngx_http_connection_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_2__ ngx_http_connection_pool_elt_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_connection_pool_free ; 
 int /*<<< orphan*/  ngx_http_connection_pool_get ; 
 void* ngx_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ngx_http_connection_pool_t *
ngx_http_connection_pool_init(ngx_pool_t *pool, ngx_uint_t max_cached,
    ngx_uint_t bucket_count)
{
    ngx_uint_t                      j, k;
    ngx_http_connection_pool_t     *conn_pool;
    ngx_http_connection_pool_elt_t *cached;

    conn_pool = ngx_pcalloc(pool, sizeof(ngx_http_connection_pool_t));
    if (conn_pool == NULL) {
        return NULL;
    }

    conn_pool->bucket_count = bucket_count;
    conn_pool->max_cached = max_cached;

    conn_pool->cache = ngx_pcalloc(pool, sizeof(ngx_queue_t) * bucket_count);
    if (conn_pool->cache == NULL) {
        return NULL;
    }

    conn_pool->free = ngx_pcalloc(pool, sizeof(ngx_queue_t) * bucket_count);
    if (conn_pool->free == NULL) {
        return NULL;
    }

    for (j = 0; j < bucket_count; j++) {
        ngx_queue_init(&conn_pool->cache[j]);
        ngx_queue_init(&conn_pool->free[j]);
        cached = ngx_pcalloc(pool,
                           sizeof(ngx_http_connection_pool_elt_t) * max_cached);
        if (cached == NULL) {
            return NULL;
        }

        for (k = 0; k < max_cached; k++) {
            ngx_queue_insert_head(&conn_pool->free[j], &cached[k].queue);
        }
    }

    conn_pool->get_peer = ngx_http_connection_pool_get;
    conn_pool->free_peer = ngx_http_connection_pool_free;
    return conn_pool;
}