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
struct TYPE_6__ {struct TYPE_6__* next; TYPE_1__* buf; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_5__ {scalar_t__ file_pos; int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;

/* Variables and functions */

void
ngx_http_tfs_free_chains(ngx_chain_t **free, ngx_chain_t **out)
{
    ngx_chain_t              *cl;

    cl = *out;

    while(cl) {
        cl->buf->pos = cl->buf->start;
        cl->buf->last = cl->buf->start;
        cl->buf->file_pos = 0;

        cl->next = *free;
        *free = cl;
    }
}