#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_6__ {struct TYPE_6__* next; TYPE_4__* buf; } ;
typedef  TYPE_1__ ngx_chain_t ;
struct TYPE_7__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 TYPE_1__* ngx_alloc_chain_link (int /*<<< orphan*/ *) ; 
 TYPE_4__* ngx_create_temp_buf (int /*<<< orphan*/ *,size_t) ; 

ngx_chain_t *
ngx_http_tfs_chain_get_free_buf(ngx_pool_t *p,
    ngx_chain_t **free, size_t size)
{
    ngx_chain_t  *cl;

    if (*free) {
        cl = *free;
        if ((size_t) (cl->buf->end - cl->buf->start) >= size) {
            *free = cl->next;
            cl->next = NULL;
            return cl;
        }
    }

    cl = ngx_alloc_chain_link(p);
    if (cl == NULL) {
        return NULL;
    }

    cl->buf = ngx_create_temp_buf(p, size);
    if (cl->buf == NULL) {
        return NULL;
    }

    cl->next = NULL;

    return cl;
}