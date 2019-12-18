#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void u_char ;
struct TYPE_6__ {void* end; TYPE_3__* next; scalar_t__ failed; void* last; } ;
struct TYPE_7__ {size_t size; TYPE_2__ d; struct TYPE_7__* current; TYPE_1__* stat; int /*<<< orphan*/  log; } ;
typedef  TYPE_3__ ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_pool_data_t ;
struct TYPE_5__ {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ALIGNMENT ; 
 int /*<<< orphan*/  NGX_POOL_ALIGNMENT ; 
 void* ngx_align_ptr (void*,int /*<<< orphan*/ ) ; 
 void* ngx_memalign (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
ngx_palloc_block(ngx_pool_t *pool, size_t size)
{
    u_char      *m;
    size_t       psize;
    ngx_pool_t  *p, *new;

    psize = (size_t) (pool->d.end - (u_char *) pool);

    m = ngx_memalign(NGX_POOL_ALIGNMENT, psize, pool->log);
    if (m == NULL) {
        return NULL;
    }

#if (NGX_DEBUG_POOL)
    pool->size += psize;
    pool->stat->size += psize;
#endif

    new = (ngx_pool_t *) m;

    new->d.end = m + psize;
    new->d.next = NULL;
    new->d.failed = 0;

    m += sizeof(ngx_pool_data_t);
    m = ngx_align_ptr(m, NGX_ALIGNMENT);
    new->d.last = m + size;

    for (p = pool->current; p->d.next; p = p->d.next) {
        if (p->d.failed++ > 4) {
            pool->current = p->d.next;
        }
    }

    p->d.next = new;

    return m;
}