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
struct TYPE_8__ {TYPE_1__* stat; TYPE_3__* large; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_pool_t ;
struct TYPE_9__ {size_t size; struct TYPE_9__* next; void* alloc; } ;
typedef  TYPE_3__ ngx_pool_large_t ;
struct TYPE_7__ {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_free (void*) ; 
 void* ngx_memalign (size_t,size_t,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_palloc_small (TYPE_2__*,int,int) ; 

void *
ngx_pmemalign(ngx_pool_t *pool, size_t size, size_t alignment)
{
    void              *p;
    ngx_pool_large_t  *large;

    p = ngx_memalign(alignment, size, pool->log);
    if (p == NULL) {
        return NULL;
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