#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_8__ {TYPE_1__* stat; TYPE_3__* large; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_pool_t ;
struct TYPE_9__ {size_t size; struct TYPE_9__* next; int /*<<< orphan*/ * alloc; } ;
typedef  TYPE_3__ ngx_pool_large_t ;
struct TYPE_7__ {int lnum; size_t size; } ;

/* Variables and functions */
 void* ngx_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_free (void*) ; 
 TYPE_3__* ngx_palloc_small (TYPE_2__*,int,int) ; 

__attribute__((used)) static void *
ngx_palloc_large(ngx_pool_t *pool, size_t size)
{
    void              *p;
    ngx_uint_t         n;
    ngx_pool_large_t  *large;

#if (NGX_DEBUG_POOL)
    pool->stat->lnum += 1;
#endif

    p = ngx_alloc(size, pool->log);
    if (p == NULL) {
        return NULL;
    }

    n = 0;

    for (large = pool->large; large; large = large->next) {
        if (large->alloc == NULL) {
            large->alloc = p;
#if (NGX_DEBUG_POOL)
            large->size = size;
            pool->stat->size += size;
#endif
            return p;
        }

        if (n++ > 3) {
            break;
        }
    }

    large = ngx_palloc_small(pool, sizeof(ngx_pool_large_t), 1);
    if (large == NULL) {
        ngx_free(p);
        return NULL;
    }

    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

#if (NGX_DEBUG_POOL)
    large->size = size;
    pool->stat->size += size;
#endif

    return p;
}