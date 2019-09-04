#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ ngx_chain_t ;

/* Variables and functions */
 TYPE_1__* ngx_alloc_chain_link (int /*<<< orphan*/ *) ; 

ngx_chain_t *
ngx_http_tfs_alloc_chains(ngx_pool_t *pool, size_t count)
{
    ngx_uint_t               i;
    ngx_chain_t             *cl, **ll;

    ll = &cl;

    for (i = 0; i < count; i++) {
        *ll = ngx_alloc_chain_link(pool);
        if (*ll == NULL) {
            return NULL;
        }

        ll = &(*ll)->next;
    }

    (*ll) = NULL;

    return cl;
}