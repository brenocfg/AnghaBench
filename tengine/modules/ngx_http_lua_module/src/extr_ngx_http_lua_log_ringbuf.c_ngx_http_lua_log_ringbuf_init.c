#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t size; int /*<<< orphan*/  filter_level; scalar_t__ count; void* data; void* sentinel; void* head; void* tail; } ;
typedef  TYPE_1__ ngx_http_lua_log_ringbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG ; 

void
ngx_http_lua_log_ringbuf_init(ngx_http_lua_log_ringbuf_t *rb, void *buf,
    size_t len)
{
    rb->data = buf;
    rb->size = len;

    rb->tail = rb->data;
    rb->head = rb->data;
    rb->sentinel = rb->data + rb->size;
    rb->count = 0;
    rb->filter_level = NGX_LOG_DEBUG;

    return;
}