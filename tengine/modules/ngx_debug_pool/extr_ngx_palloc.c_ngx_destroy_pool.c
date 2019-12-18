#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* next; scalar_t__ last; scalar_t__ end; } ;
struct TYPE_12__ {TYPE_2__ d; TYPE_1__* stat; scalar_t__ size; TYPE_4__* large; int /*<<< orphan*/  log; int /*<<< orphan*/  data; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;struct TYPE_12__* next; struct TYPE_12__* cleanup; } ;
typedef  TYPE_3__ ngx_pool_t ;
struct TYPE_13__ {TYPE_3__* alloc; scalar_t__ size; struct TYPE_13__* next; } ;
typedef  TYPE_4__ ngx_pool_large_t ;
typedef  TYPE_3__ ngx_pool_cleanup_t ;
struct TYPE_10__ {int cnum; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_ALLOC ; 
 int /*<<< orphan*/  ngx_free (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
ngx_destroy_pool(ngx_pool_t *pool)
{
    ngx_pool_t          *p, *n;
    ngx_pool_large_t    *l;
    ngx_pool_cleanup_t  *c;

    for (c = pool->cleanup; c; c = c->next) {
        if (c->handler) {
            ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                           "run cleanup: %p", c);
            c->handler(c->data);
        }
    }

#if (NGX_DEBUG)

    /*
     * we could allocate the pool->log from this pool
     * so we cannot use this log while free()ing the pool
     */

    for (l = pool->large; l; l = l->next) {
        ngx_log_debug1(NGX_LOG_DEBUG_ALLOC, pool->log, 0, "free: %p", l->alloc);
    }

    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        ngx_log_debug2(NGX_LOG_DEBUG_ALLOC, pool->log, 0,
                       "free: %p, unused: %uz", p, p->d.end - p->d.last);

        if (n == NULL) {
            break;
        }
    }

#endif

    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
#if (NGX_DEBUG_POOL)
            pool->stat->size -= l->size;
#endif
            ngx_free(l->alloc);
        }
    }

#if (NGX_DEBUG_POOL)
    pool->stat->size -= pool->size;
    pool->stat->cnum -= 1;
#endif

    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        ngx_free(p);

        if (n == NULL) {
            break;
        }
    }
}