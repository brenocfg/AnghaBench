#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {scalar_t__ failed; int /*<<< orphan*/ * next; int /*<<< orphan*/ * end; int /*<<< orphan*/ * last; } ;
struct TYPE_6__ {size_t max; int /*<<< orphan*/ * log; int /*<<< orphan*/ * cleanup; int /*<<< orphan*/ * large; int /*<<< orphan*/ * chain; struct TYPE_6__* current; TYPE_1__ d; } ;
typedef  TYPE_2__ ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;

/* Variables and functions */
 size_t NGX_MAX_ALLOC_FROM_POOL ; 
 int /*<<< orphan*/  NGX_POOL_ALIGNMENT ; 
 TYPE_2__* ngx_memalign (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

ngx_pool_t *
ngx_create_pool(size_t size, ngx_log_t *log)
{
    ngx_pool_t  *p;

    p = ngx_memalign(NGX_POOL_ALIGNMENT, size, log);
    if (p == NULL) {
        return NULL;
    }

    p->d.last = (u_char *) p + sizeof(ngx_pool_t);
    p->d.end = (u_char *) p + size;
    p->d.next = NULL;
    p->d.failed = 0;

    size = size - sizeof(ngx_pool_t);
    p->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

    p->current = p;
    p->chain = NULL;
    p->large = NULL;
    p->cleanup = NULL;
    p->log = log;

    return p;
}