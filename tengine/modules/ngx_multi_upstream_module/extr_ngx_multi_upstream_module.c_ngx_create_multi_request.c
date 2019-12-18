#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/ * pool; void* data; } ;
typedef  TYPE_1__ ngx_multi_request_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_create_pool (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 TYPE_1__* ngx_pcalloc (int /*<<< orphan*/ *,int) ; 

ngx_multi_request_t*
ngx_create_multi_request(ngx_connection_t *c, void *data)
{
    ngx_multi_request_t     *multi_r;
    ngx_pool_t              *pool;

    pool = ngx_create_pool(4096, c->log);
    if (pool == NULL) {
        return NULL;
    }

    multi_r = ngx_pcalloc(pool, sizeof(ngx_multi_request_t));
    if (multi_r == NULL) {
        ngx_destroy_pool(pool);
        return NULL;
    }

    multi_r->data = data;
    multi_r->pool = pool;

    return multi_r;
}