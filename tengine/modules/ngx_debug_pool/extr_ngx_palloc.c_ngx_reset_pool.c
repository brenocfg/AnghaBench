#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {scalar_t__ failed; int /*<<< orphan*/ * last; TYPE_3__* next; } ;
struct TYPE_8__ {TYPE_4__* large; int /*<<< orphan*/ * chain; struct TYPE_8__* current; TYPE_2__ d; TYPE_1__* stat; } ;
typedef  TYPE_3__ ngx_pool_t ;
struct TYPE_9__ {scalar_t__ alloc; scalar_t__ size; struct TYPE_9__* next; } ;
typedef  TYPE_4__ ngx_pool_large_t ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_free (scalar_t__) ; 

void
ngx_reset_pool(ngx_pool_t *pool)
{
    ngx_pool_t        *p;
    ngx_pool_large_t  *l;

    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
#if (NGX_DEBUG_POOL)
            pool->stat->size -= l->size;
#endif
            ngx_free(l->alloc);
        }
    }

    for (p = pool; p; p = p->d.next) {
        p->d.last = (u_char *) p + sizeof(ngx_pool_t);
        p->d.failed = 0;
    }

    pool->current = pool;
    pool->chain = NULL;
    pool->large = NULL;
}